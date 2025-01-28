#include "straregy/shapes_strategy.h"

ShapesStrategy::ShapesStrategy() 
    :  _currentShape{nullptr}, _isDrawning{false}
{}

void ShapesStrategy::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        _startPoint
    }
}

void ShapesStrategy::mouseMoveEvent(QMouseEvent* event)
{

}

void ShapesStrategy::mouseReleaseEvent(QMouseEvent* event)
{

}

void ShapesStrategy::keyPressEvent(QKeyEvent* event)
{
    
}

void ShapesStrategy::cancel()
{
    _isDrawning = false;
    _currentShape = nullptr;
}