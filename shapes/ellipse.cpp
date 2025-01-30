#include "ellipse.h"

Ellipse::Ellipse(const QRect& rect)
    : DefaultShape(ShapeType::rectangle), _rect{rect}
{}

void Ellipse::draw(QPainter* painter)
{
    painter->drawEllipse(_rect);
}

bool Ellipse::contains(const QPoint& point) const
{
    return _rect.contains(point);
}

void Ellipse::resize(const QRect& newBounds)
{
    _rect = newBounds;
}

void Ellipse::move(const QPoint& delta)
{
    _rect.translate(delta);
}

QPoint Ellipse::center() const
{
    return _rect.center();
}

QRect Ellipse::boundingRect() const
{
    return _rect;
}