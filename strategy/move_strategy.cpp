#include "move_strategy.h"
#include <QMouseEvent>
#include "shapes/default_shape.h"

MoveStrategy::MoveStrategy(Paint* context)
    : ActionStrategy(context), _isMove(false){}

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
}

void MoveStrategy::mouseMoveEvent(QMouseEvent* event) {
    if (_isMove) 
    {
        QPointF delta = event->pos() - _endPoint;
        _selectedShape->move(delta.toPoint()); // Перемещаем фигуру
        _endPoint = event->pos();
        _context->moveConnection(_selectedShape, delta);
        _context->update(); // Обновляем отрисовку (связи обновятся автоматически)
    }
}

void MoveStrategy::mouseReleaseEvent(QMouseEvent* event) 
{
    if (_isMove && event->button() == Qt::LeftButton) 
    {
        _isMove = false;
        _context->setCursor(Qt::ArrowCursor);
    }
}

void MoveStrategy::keyPressEvent(QKeyEvent* event) {

}

void MoveStrategy::drawTemporary(QPainter* painter)
{

}

void MoveStrategy::cancel() 
{

}