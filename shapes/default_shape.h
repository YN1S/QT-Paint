#pragma once

#include <QPainter>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QPolygon>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>

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

protected:
    ShapeType _type;
};