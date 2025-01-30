#pragma once

#include "action_strategy.h"
#include "paint.h"

class MoveStrategy : public ActionStrategy
{
public:
    MoveStrategy(Paint* context);
    virtual ~MoveStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void drawTemporary(QPainter* painter) override;

protected:
    void cancel() override;
    DefaultShape* findShape(const QPoint& pos) const;
private:
    ShapeType _type;

    DefaultShape* _selectedShape;
    QRect _startPosition;
    QPoint _startPoint;
    QPoint _endPoint;
    bool _isMove;
    bool _isRMBPressed;
};