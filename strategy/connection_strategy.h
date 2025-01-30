#pragma once

#include "action_strategy.h"
#include "paint.h"

class ConnectionStrategy : public ActionStrategy
{
public:
    ConnectionStrategy(Paint* context);
    virtual ~ConnectionStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void drawTemporary(QPainter* painter) override;
protected:
    void cancel() override;
private:
    bool _isConnection;
    DefaultShape* _startShape;
    QPoint _connectionStart;
    QPoint _connectionEnd;
};