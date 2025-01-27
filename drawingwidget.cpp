#include "drawingwidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QMessageBox>

DrawingWidget::DrawingWidget(QWidget *parent) : QWidget(parent), currentShape(Rectangle), isDrawing(false), isConnecting(false) {}

void DrawingWidget::setShapeType(ShapeType type) {
    currentShape = type;
}

void DrawingWidget::saveToFile(const QString &fileName)
{
    QJsonArray shapesArray;

    for (const Shape &shape : shapes) {
        QJsonObject shapeObject;
        shapeObject["type"] = shape.type;
        shapeObject["x"] = shape.boundingBox.x();
        shapeObject["y"] = shape.boundingBox.y();
        shapeObject["width"] = shape.boundingBox.width();
        shapeObject["height"] = shape.boundingBox.height();
        shapesArray.append(shapeObject);
    }

    QJsonArray connectionsArray;

    for (const ConnectionLine &connection : connections) {
        QJsonObject connectionObject;
        connectionObject["startX"] = connection.start.x();
        connectionObject["startY"] = connection.start.y();
        connectionObject["endX"] = connection.end.x();
        connectionObject["endY"] = connection.end.y();
        connectionsArray.append(connectionObject);
    }

    QJsonObject rootObject;
    rootObject["shapes"] = shapesArray;
    rootObject["connections"] = connectionsArray;

    QJsonDocument doc(rootObject);

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    file.write(doc.toJson());
    file.close();
}

void DrawingWidget::loadFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для чтения.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат файла.");
        return;
    }

    QJsonObject rootObject = doc.object();

    shapes.clear();
    connections.clear();

    QJsonArray shapesArray = rootObject["shapes"].toArray();
    for (const QJsonValue &value : shapesArray) {
        QJsonObject shapeObject = value.toObject();
        ShapeType type = static_cast<ShapeType>(shapeObject["type"].toInt());
        qreal x = shapeObject["x"].toDouble();
        qreal y = shapeObject["y"].toDouble();
        qreal width = shapeObject["width"].toDouble();
        qreal height = shapeObject["height"].toDouble();
        shapes.append({type, QRectF(x, y, width, height)});
    }

    QJsonArray connectionsArray = rootObject["connections"].toArray();
    for (const QJsonValue &value : connectionsArray) {
        QJsonObject connectionObject = value.toObject();
        QPointF start(connectionObject["startX"].toDouble(), connectionObject["startY"].toDouble());
        QPointF end(connectionObject["endX"].toDouble(), connectionObject["endY"].toDouble());
        connections.append({start, end});
    }

    update();
}




void DrawingWidget::mousePressEvent(QMouseEvent *event) {
    if (currentShape == Delete) {
        if (event->button() == Qt::LeftButton) {
            QPointF clickedPoint = event->pos();

            for (int i = 0; i < shapes.size(); ++i) {
                if (shapes[i].boundingBox.contains(clickedPoint)) {

                    for (int j = connections.size() - 1; j >= 0; --j) {
                        if (connections[j].start == shapes[i].center() ||
                            connections[j].end == shapes[i].center()) {
                            connections.removeAt(j);
                        }
                    }

                    shapes.removeAt(i);
                    update();
                    return;
                }
            }
        }
    }

    if (currentShape == Move) {
        if (event->button() == Qt::LeftButton) {
            QPointF clickedPoint = event->pos();
            for (Shape &shape : shapes) {
                if (shape.boundingBox.contains(clickedPoint)) {
                    selectedShape = &shape;
                    lastMousePos = event->pos();
                    isMoving = true;

                    return;
                }
            }
        } else if (event->button() == Qt::RightButton) {
            selectedShape = nullptr;
            isMoving = false;
            setCursor(Qt::ArrowCursor);
        }
    } else if (currentShape == Connection) {
        if (event->button() == Qt::LeftButton) {
            QPointF clickedPoint = event->pos();
            for (const Shape &shape : shapes) {
                if (shape.boundingBox.contains(clickedPoint)) {
                    if (!isConnecting) {
                        connectionStart = shape.center();
                        isConnecting = true;
                    } else if (isConnecting && shape.center() != connectionStart) {
                        connections.append({connectionStart, shape.center()});
                        isConnecting = false;
                        update();
                    }
                    return;
                }
            }
            isConnecting = false;
        } else if (event->button() == Qt::RightButton) {
            isConnecting = false;
        }
    } else if (event->button() == Qt::LeftButton) {
        startPoint = event->pos();
        isDrawing = true;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    if (isMoving && selectedShape) {
        QPoint offset = event->pos() - lastMousePos;
        selectedShape->boundingBox.translate(offset);

        for (ConnectionLine &connection : connections) {
            if (connection.start == selectedShape->center() - offset) {
                connection.start += offset;
            }
            if (connection.end == selectedShape->center() - offset) {
                connection.end += offset;
            }
        }

        lastMousePos = event->pos();
        update();
    } else if (isDrawing && currentShape != Connection) {
        endPoint = event->pos();
        update();
    }
}

void DrawingWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isMoving && event->button() == Qt::LeftButton)
    {
        selectedShape = nullptr;
        isMoving = false;
        setCursor(Qt::OpenHandCursor);
    }
    else if (event->button() == Qt::RightButton)
    {
        isDrawing = false;
        update();
    }
    else if (isDrawing && event->button() == Qt::LeftButton) {
        endPoint = event->pos();
        QRectF boundingBox(startPoint, endPoint);
        switch (currentShape) {
        case Rectangle:
            shapes.append({Rectangle, boundingBox.normalized()});
            break;
        case Triangle:
            shapes.append({Triangle, boundingBox.normalized()});
            break;
        case Ellipse:
            shapes.append({Ellipse, boundingBox.normalized()});
            break;
        default:
            break;
        }
        isDrawing = false;
        update();
    }
}

void DrawingWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), Qt::white);

    painter.setPen(Qt::black);
    for (const Shape &shape : shapes) {
        switch (shape.type) {
        case Rectangle:
            painter.drawRect(shape.boundingBox);
            break;
        case Triangle: {
            QPolygon triangle;
            triangle << QPoint(shape.boundingBox.center().x(), shape.boundingBox.top())
                     << shape.boundingBox.bottomRight().toPoint()
                     << shape.boundingBox.bottomLeft().toPoint();
            painter.drawPolygon(triangle);
            break;
        }
        case Ellipse:
            painter.drawEllipse(shape.boundingBox);
            break;
        default:
            break;
        }
    }

    painter.setPen(Qt::black);
    for (const ConnectionLine &connection : connections) {
        painter.drawLine(connection.start, connection.end);
    }

    if (isConnecting) {
        painter.setPen(Qt::DashLine);
        painter.drawLine(connectionStart, mapFromGlobal(QCursor::pos()));
    }

    if (isDrawing && currentShape != Connection) {
        painter.setPen(Qt::DashLine);
        QRectF boundingBox(startPoint, endPoint);
        switch (currentShape) {
        case Rectangle:
            painter.drawRect(boundingBox.normalized());
            break;
        case Triangle: {
            QPolygon triangle;
            triangle << QPoint(boundingBox.center().x(), boundingBox.top())
                     << boundingBox.bottomRight().toPoint()
                     << boundingBox.bottomLeft().toPoint();
            painter.drawPolygon(triangle);
            break;
        }
        case Ellipse:
            painter.drawEllipse(boundingBox.normalized());
            break;
        default:
            break;
        }
    }
}
