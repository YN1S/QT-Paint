#include "shapes_strategy.h"
#include "shapes/shapes_types.h"
#include "strategy/action_strategy.h"

ShapesStrategy::ShapesStrategy(Paint* context, const ShapeType type)
    : ActionStrategy(context), _type(type), _currentShape{nullptr}, _isDrawning{false}
{}

void ShapesStrategy::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        _startPoint = event->pos();
        _isDrawning = true;
        _currentShape = shapeFactory.at(_type)();
    }
    else if (event->button() == Qt::RightButton)
    {
        cancel();
    }
}

void ShapesStrategy::mouseMoveEvent(QMouseEvent* event)
{
    if(_isDrawning)
    {
        _endPoint = event->pos();
        _currentShape->resize(QRect(_startPoint, _endPoint));
        _context->update();
    }
}

void ShapesStrategy::paintEvent(QPaintEvent *event)
{
    // Если нужно рисовать, добавь код для отрисовки формы
    // _currentShape->draw(painter);
}

void ShapesStrategy::mouseReleaseEvent(QMouseEvent* event)
{
    if(_isDrawning)
    {
        _endPoint = event->pos();
        _context->addShape(std::move(_currentShape));
        _isDrawning = false;
    }
}

void ShapesStrategy::keyPressEvent(QKeyEvent* event)
{
    if(_isDrawning && event->key() == Qt::Key_Escape)
    {
        cancel();
    }
}

void ShapesStrategy::drawTemporary(QPainter* painter)
{
    if (_isDrawning) {_currentShape->draw(painter);}
}

void ShapesStrategy::cancel()
{
    _isDrawning = false;
    _currentShape = nullptr;
    _context->update();
}
