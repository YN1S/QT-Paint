#include "move_strategy.h"
#include <QMouseEvent>
#include "shapes/default_shape.h"

MoveStrategy::MoveStrategy(Paint* context)
    : ActionStrategy(context), _isMove(false), _isRMBPressed(false){}

void MoveStrategy::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton)
    {
        _selectedShape = findShape(event->pos());
        if (_selectedShape) // Если фигура нашлась - начинаем перетаскивание
        {
            _startPosition = _selectedShape->boundingRect(); // Запоминаем начальную позицию
            _endPoint = event->pos();
            _isMove = true;
            _context->setCursor(Qt::ClosedHandCursor);
        }
    }
    else if (event->button() == Qt::RightButton && _isRMBPressed) 
    {
        cancel();
    } 
}

void MoveStrategy::mouseMoveEvent(QMouseEvent* event) {
    if (_isMove) 
    {   
        _isRMBPressed = true;
        QPointF delta = event->pos() - _endPoint;
        _selectedShape->move(delta.toPoint());
        _endPoint = event->pos();
        _context->update();
    }
}

void MoveStrategy::mouseReleaseEvent(QMouseEvent* event) {
    if (_isMove && event->button() == Qt::LeftButton) {
        _isMove = false;
        _context->setCursor(Qt::ArrowCursor);
        _isRMBPressed = false;
    }
}

void MoveStrategy::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        cancel();
    }
}

void MoveStrategy::drawTemporary(QPainter* painter)
{

}

void MoveStrategy::cancel() {
    _selectedShape->resize(_startPosition);
    _isMove = false;
    _isRMBPressed = false;
    _selectedShape = nullptr;
    _context->setCursor(Qt::ArrowCursor);
    _context->update();
}

DefaultShape* MoveStrategy::findShape(const QPoint& pos) const
{   
    for (const auto& shape : _context->shapes())
    {
        if (shape->contains(pos)) {return shape.get();} // Возвращаем фигуру, если курсор внутри нее
    }
    return nullptr; // Курсор не на фигуре
}