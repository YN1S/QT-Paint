#pragma once

#include <memory>
#include <vector>
#include <QFrame>
#include <QPoint>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QJsonDocument>
#include <QMessageBox>

#include "strategy/action_strategy.h"
#include "shapes/default_shape.h"


class Paint : public QFrame
{
    Q_OBJECT
public:
    Paint(QFrame* parent = nullptr);

    void setStrategy(std::unique_ptr<ActionStrategy> strategy);
    void addShape(std::unique_ptr<DefaultShape> shape);

    const std::vector<std::unique_ptr<DefaultShape>>& shapes() const;

  protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

private:
    std::unique_ptr<ActionStrategy> _strategy;

    std::vector<std::unique_ptr<DefaultShape>> _shapes;
};

