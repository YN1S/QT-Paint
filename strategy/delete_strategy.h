#pragma once

#include "action_strategy.h"

class DeleteStrategy : public ActionStrategy
{
public:
    DeleteStrategy(Paint* context);
    virtual ~DeleteStrategy() = default;

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void drawTemporary(QPainter* painter) override;

protected:
    void cancel() override;
};