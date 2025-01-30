#pragma once

#include "default_shape.h"

class Triangle: public DefaultShape
{
public:
    Triangle(const QPolygon& rect = {});
    ~Triangle() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) const override;
    void resize(const QRect& newBounds) override;
    void move(const QPoint& delta) override;
    QPoint center() const override;
    QRect boundingRect() const override;

    QJsonObject toJson() const override; 
private:
    QPolygon _polygon;
};