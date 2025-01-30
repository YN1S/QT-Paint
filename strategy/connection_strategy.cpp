#include "connection_strategy.h"
#include "shapes/default_shape.h"

ConnectionStrategy::ConnectionStrategy(Paint* context)
    : ActionStrategy(context), _isConnection(false)
{

}

void ConnectionStrategy::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        if (!_isConnection) 
        {
            // Начало связи
            _startShape = findShape(event->pos());
            if (_startShape) 
            {
                _connectionStart = _startShape->center();
                _isConnection = true;
                _context->setMouseTracking(true);
            }
        } 
        else 
        {
            // Завершаем связь
            auto endShape = findShape(event->pos());
            if (endShape && endShape != _startShape) 
            {
                _context->addConnection({_connectionStart, endShape->center()});
            }
            // Сброс состояния после завершения
            cancel();
        }
    }

    if (event->button() == Qt::RightButton) 
    {
    cancel();
    }
}
void ConnectionStrategy::mouseMoveEvent(QMouseEvent* event)
{
    if (_isConnection)
    {
        _connectionEnd = event->pos();  // Обновляем конечную точку связи
        _context->update();  // Запрашиваем перерисовку
    }
}
void ConnectionStrategy::mouseReleaseEvent(QMouseEvent* event)
{
    
}
void ConnectionStrategy::drawTemporary(QPainter* painter)
{
    if (_isConnection)
    {
        painter->setPen(QPen(Qt::DashLine));  // Устанавливаем стиль линии (например, пунктирная линия)
        painter->drawLine(_connectionStart, _connectionEnd);  // Рисуем линию от начальной до текущей точки
    }
}

void ConnectionStrategy::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        cancel();
    }
}

void ConnectionStrategy::cancel() {
    _isConnection = false;
    _startShape = nullptr;
    _context->update();
}