#include "triangle.h"

Triangle::Triangle(const QRect& rect)
    : DefaultShape(ShapeType::rectangle), _rect{rect}
{}

void Triangle::draw(QPainter* painter)
{
    QPointF points[3];
    points[0] = QPointF(_rect.left() + _rect.width() / 2.0, _rect.top());   // Верхняя вершина
    points[1] = QPointF(_rect.left(), _rect.bottom());                      // Левая нижняя вершина
    points[2] = QPointF(_rect.right(), _rect.bottom());                     // Правая нижняя вершина

    painter->drawPolygon(points, 3);
}

bool Triangle::contains(const QPoint& point) const
{
    return _rect.contains(point);
}

void Triangle::resize(const QRect& newBounds)
{
    _rect = newBounds;
}

void Triangle::move(const QPoint& delta)
{
    _rect.translate(delta);
}

QPoint Triangle::center() const
{
    return _rect.center();
}

QRect Triangle::boundingRect() const
{
    return _rect;
}