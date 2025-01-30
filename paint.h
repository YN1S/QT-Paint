#pragma once

#include <memory>
#include <vector>
#include <QFrame>
#include <QPoint>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

#include "strategy/action_strategy.h"
#include "shapes/default_shape.h"

struct ConnectionLine {
    QPointF start;
    QPointF end;
};

class Paint : public QFrame
{
    Q_OBJECT
public:
    Paint(QFrame* parent = nullptr);

    void setStrategy(std::unique_ptr<ActionStrategy> strategy);
    void addShape(std::unique_ptr<DefaultShape> shape);
    void addConnection(ConnectionLine connection);
    void removeShape(DefaultShape* shapeToRemove);
    void removeConnection(DefaultShape* shapeWithBounds);
    void moveConnection(DefaultShape* shapeWithBounds, QPointF delta);
    void revertConnections(DefaultShape* shapeWithBounds);


    const std::vector<std::unique_ptr<DefaultShape>>& shapes() const;
    const QList<ConnectionLine>& connections() const;

    void loadFromFile(QFile& file);
    void saveToFile(QFile& file) const;

  protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void paintEvent(QPaintEvent* event) override;

private:
    std::unique_ptr<ActionStrategy> _strategy;

    std::vector<std::unique_ptr<DefaultShape>> _shapes;
    QList<ConnectionLine> _connections;
};

