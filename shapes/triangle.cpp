#include "triangle.h"

Triangle::Triangle(const QPolygon& polygon)
    : DefaultShape(ShapeType::triangle), _polygon(polygon)
{}

void Triangle::draw(QPainter* painter)
{
    painter->drawPolygon(_polygon); 
}

bool Triangle::contains(const QPoint& point) const
{
    return _polygon.containsPoint(point, Qt::OddEvenFill);
}

void Triangle::resize(const QRect& newBounds)
{
    // Убедимся, что полигон имеет три точки
    if (_polygon.size() < 3) {
        _polygon = QPolygon(3); // Создаем полигон с тремя точками
    }

    QPoint center = newBounds.center();
    int width = newBounds.width();
    int height = newBounds.height();

    // Обновляем вершины
    _polygon[0] = QPoint(center.x(), center.y() - height / 2);
    _polygon[1] = QPoint(center.x() - width / 2, center.y() + height / 2);
    _polygon[2] = QPoint(center.x() + width / 2, center.y() + height / 2);
}


void Triangle::move(const QPoint& delta)
{
    _polygon.translate(delta);
}

QPoint Triangle::center() const
{
     return _polygon.boundingRect().center();
}

QRect Triangle::boundingRect() const
{
     return _polygon.boundingRect(); 
}

QJsonObject Triangle::toJson() const
{
    QJsonObject obj;
    obj["type"] = "Triangle";

    // Заполняем координаты для вершин треугольника
    obj["x1"] = _polygon[0].x();
    obj["y1"] = _polygon[0].y();
    obj["x2"] = _polygon[1].x();
    obj["y2"] = _polygon[1].y();
    obj["x3"] = _polygon[2].x();
    obj["y3"] = _polygon[2].y();

    return obj;
}
