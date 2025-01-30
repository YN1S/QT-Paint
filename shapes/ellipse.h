#pragma once

#include "default_shape.h"

class Ellipse: public DefaultShape
{
public:
    Ellipse(const QRect& rect = {});
    ~Ellipse() = default;

    void draw(QPainter* painter) override;
    bool contains(const QPoint& point) const override;
    void resize(const QRect& newBounds) override;
    void move(const QPoint& delta) override;
    QPoint center() const override;
    QRect boundingRect() const override;

    QJsonObject toJson() const override; 

private:
    QRect _rect;
};