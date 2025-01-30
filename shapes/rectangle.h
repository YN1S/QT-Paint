#pragma once

#include "default_shape.h"

class Rectangle: public DefaultShape
{
public:
    Rectangle(const QRect& rect = {});
    virtual ~Rectangle() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) const override;
    void resize(const QRect& newBounds) override;
    void move(const QPoint& delta) override;
    QPoint center() const override;
    QRect boundingRect() const override;

private:
    QRect _rect;
};