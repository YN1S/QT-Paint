#pragma once

#include <QWidget>
#include <QMouseEvent>

enum class StrategyType
{
    Shapes,
    Connection,
    Move,
    Delete
};

class ActionStrategy
{
    Q_OBJECT
protected:
    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void keyPressEvent(QKeyEvent* event) = 0;
    virtual void paintEvent(QPaintEvent *event) = 0;

    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void cancel();
};