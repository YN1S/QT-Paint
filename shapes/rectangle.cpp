#include "rectangle.h"

Rectangle::Rectangle(const QRect& rect)
    : DefaultShape(ShapeType::rectangle), _rect{rect}
{}

void Rectangle::draw(QPainter* painter)
{
    painter->drawRect(_rect);
}

bool Rectangle::contains(const QPoint& point) const
{
    return _rect.contains(point);
}

void Rectangle::resize(const QRect& newBounds)
{
    _rect = newBounds;
}

void Rectangle::move(const QPoint& delta)
{
    _rect.translate(delta);
}

QPoint Rectangle::center() const
{
    return _rect.center();
}

QRect Rectangle::boundingRect() const
{
    return _rect;
}