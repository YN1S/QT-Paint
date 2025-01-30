#pragma once

#include "default_shape.h"

class Triangle: public DefaultShape
{
public:
    Triangle(const QRect& rect = {});
    virtual ~Triangle() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) const override;
    void resize(const QRect& newBounds) override;
    void move(const QPoint& delta) override;
    QPoint center() const override;
    QRect boundingRect() const override;

private:
    QRect _rect;
};