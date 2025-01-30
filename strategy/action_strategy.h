#pragma once

#include <QWidget>
#include <QMouseEvent>

class Paint;
class DefaultShape;

enum class StrategyType
{
    Shapes,
    Connection,
    Move,
    Delete
};

class ActionStrategy
{
public:

    ActionStrategy(Paint* context);
    virtual ~ActionStrategy() = default;

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void drawTemporary(QPainter* painter) = 0;

    virtual void cancel() = 0;
    DefaultShape* findShape(const QPoint& pos) const;

protected:
    Paint* _context;
};
