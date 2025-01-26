#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QToolBar>
#include <QAction>
#include <QMainWindow>

enum ShapeType {
    Rectangle,
    Triangle,
    Ellipse
};

class DrawingWidget : public QWidget {
public:
    DrawingWidget(QWidget *parent = nullptr) : QWidget(parent) {}

    void setShapeType(ShapeType type) { currentShape = type; }

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            startPoint = event->pos();
            isDrawing = true;
        }
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if (isDrawing) {
            endPoint = event->pos();
            update();
        }
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton && isDrawing) {
            endPoint = event->pos();
            addShape(startPoint, endPoint);
            isDrawing = false;
            update();
        } else if(event->button() == Qt::RightButton) {
            isDrawing = false;
            update();
        }
    }

    void keyPressEvent(QKeyEvent *event) override{
        if (event->key() == Qt::Key_Escape && isDrawing) {
            isDrawing = false;
            update();
        }
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.fillRect(rect(), Qt::white);

        painter.setPen(Qt::black);

        for (const QPolygon &triangle : triangles) {
            painter.drawPolygon(triangle);
        }
        for (const QRect &rect : rectangles) {
            painter.drawRect(rect);
        }
        for (const QRectF &ellipse : ellipses) {
            painter.drawEllipse(ellipse);
        }

        // Отрисовка текущей фигуры
        if (isDrawing) {
            painter.setPen(Qt::DashLine);

            if (currentShape == Triangle) {
                QPolygon currentTriangle = createTriangle(startPoint, endPoint);
                painter.drawPolygon(currentTriangle);
            } else if (currentShape == Rectangle) {
                QRect currentRect = QRect(startPoint, endPoint).normalized();
                painter.drawRect(currentRect);
            } else if (currentShape == Ellipse) {
                QRectF currentEllipse = QRectF(startPoint, endPoint).normalized();
                painter.drawEllipse(currentEllipse);
            }
        }
    }

private:
    QPoint startPoint;
    QPoint endPoint;
    bool isDrawing = false;
    ShapeType currentShape = Triangle;

    QList<QPolygon> triangles;
    QList<QRect> rectangles;
    QList<QRectF> ellipses;

    void addShape(const QPoint &start, const QPoint &end) {
        if (currentShape == Triangle) {
            triangles.append(createTriangle(start, end));
        } else if (currentShape == Rectangle) {
            rectangles.append(QRect(start, end).normalized());
        } else if (currentShape == Ellipse) {
            ellipses.append(QRectF(start, end).normalized());
        }
    }

    QPolygon createTriangle(const QPoint &start, const QPoint &end) const {
        QPoint top((start.x() + end.x()) / 2, start.y());
        QPoint bottomLeft(start.x(), end.y());
        QPoint bottomRight(end.x(), end.y());
        return QPolygon({top, bottomRight, bottomLeft});
    }
};

class MainWindow : public QMainWindow {
public:
    MainWindow() {
        auto *drawingWidget = new DrawingWidget(this);
        setCentralWidget(drawingWidget);

        QToolBar *toolbar = addToolBar("Shapes");

        QAction *rectangleAction = toolbar->addAction("Прямоугольник");
        QAction *triangleAction = toolbar->addAction("Треугольник");
        QAction *ellipseAction = toolbar->addAction("Эллипс");

        connect(rectangleAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Rectangle);
        });
        connect(triangleAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Triangle);
        });
        connect(ellipseAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Ellipse);
        });
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(800, 600);
    window.show();
    return app.exec();
}
