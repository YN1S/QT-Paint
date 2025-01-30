#pragma once

#include "action_strategy.h"
#include "paint.h"
#include "shapes/shapes_types.h"
#include "shapes/default_shape.h"

class DefaultShape;

class ShapesStrategy : public ActionStrategy
{
public:
    ShapesStrategy(Paint* context, const ShapeType type);
    virtual ~ShapesStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void drawTemporary(QPainter* painter) override;

protected:
    void cancel() override;
private:
    ShapeType _type;

    std::unique_ptr<DefaultShape> _currentShape;
    QPoint _startPoint;
    QPoint _endPoint;
    bool _isDrawning;
};
