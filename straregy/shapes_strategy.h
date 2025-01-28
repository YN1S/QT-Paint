#pragma once

#include "action_strategy.h"
#include "drawingwidget.h"
#include "shapes/shapes_types.h"

class ShapesStrategy : public ActionStrategy
{
public:
    ShapesStrategy();
    virtual ~ShapesStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent* event) override;

protected:
    void cancel() override;
private:
    ShapesTypes _type;

    std::unique_ptr<Shape> _currentShape;
    QPoint _startPoint;
    QPoint _endPoint;
    bool _isDrawning;
};