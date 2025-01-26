#ifndef DRAWINGWIDGET_H
#define DRAWINGWIDGET_H

#include <QWidget>
#include <QList>
#include <QPointF>
#include <QRectF>

enum ShapeType {
    Rectangle,
    Triangle,
    Ellipse,
    Connection,
    Move,
    Delete
};

struct Shape {
    ShapeType type;
    QRectF boundingBox;
    QPointF center() const {
        return boundingBox.center();
    }
};

struct ConnectionLine {
    QPointF start;
    QPointF end;
};

class DrawingWidget : public QWidget {
    Q_OBJECT

public:
    explicit DrawingWidget(QWidget *parent = nullptr);
    void setShapeType(ShapeType type);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    ShapeType currentShape;               // Текущий тип фигуры
    QPoint startPoint;                    // Начальная точка рисования
    QPoint endPoint;                      // Конечная точка рисования
    bool isDrawing;                       // Флаг процесса рисования
    QList<Shape> shapes;                  // Список фигур

    QPointF connectionStart;              // Начало связи
    bool isConnecting;                    // Флаг рисования связи
    QList<ConnectionLine> connections;    // Список связей

    Shape *selectedShape = nullptr;       // Указатель на перемещаемую фигуру
    QPoint lastMousePos;                  // Последняя позиция мыши
    bool isMoving = false;                // Флаг перемещения фигуры
};

#endif // DRAWINGWIDGET_H
