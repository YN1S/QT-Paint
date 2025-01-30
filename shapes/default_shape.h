#pragma once

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QPolygon>
#include <QString>
#include <QJsonObject>

#include "shapes_types.h"

enum class ShapeType;

class DefaultShape
{
public:
    DefaultShape(ShapeType type);
    virtual ~DefaultShape() = default;

    virtual void draw(QPainter* painter) = 0;
    virtual bool contains(const QPoint& point) const = 0; 
    virtual void resize(const QRect& newBounds) = 0; 
    virtual void move(const QPoint& delta) = 0; 
    virtual QPoint center() const = 0; 
    virtual QRect boundingRect() const = 0;

    virtual QJsonObject toJson() const = 0;
    static std::unique_ptr<DefaultShape> fromJson(const QJsonObject &obj);
protected:
    ShapeType _type;
};
