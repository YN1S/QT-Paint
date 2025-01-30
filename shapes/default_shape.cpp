#include "default_shape.h"
#include "ellipse.h"
#include "rectangle.h"
#include "triangle.h"

DefaultShape::DefaultShape(ShapeType type)
    : _type(type) {}

std::unique_ptr<DefaultShape> DefaultShape::fromJson(const QJsonObject& obj)
{
    QString type = obj["type"].toString();
    if (type == "Rectangle") {
        QPoint pos(obj["x"].toInt(), obj["y"].toInt());
        QSize size(obj["width"].toInt(), obj["height"].toInt());
        QRect rect(pos, size);  // Создаем QRect
        return std::make_unique<Rectangle>(rect);  // Передаем в конструктор Rectangle
    }
    if (type == "Ellipse") 
    {
        QPoint pos(obj["x"].toInt(), obj["y"].toInt());
        QSize size(obj["width"].toInt(), obj["height"].toInt());
        QRect rect(pos, size);  // Создаем QRect
        return std::make_unique<Ellipse>(rect);  // Передаем в конструктор Ellipse
    }
    if (type == "Triangle") 
    {
        int x1 = obj["x1"].toInt();
        int y1 = obj["y1"].toInt();
        int x2 = obj["x2"].toInt();
        int y2 = obj["y2"].toInt();
        int x3 = obj["x3"].toInt();
        int y3 = obj["y3"].toInt();

        QPolygon polygon;  // Используем QRect
        polygon << QPoint(x1, y1) << QPoint(x2, y2) << QPoint(x3, y3);
        return std::make_unique<Triangle>(polygon);  // Передаем в конструктор Triangle
    }

    return nullptr;
}