#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include "drawingwidget.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        drawingWidget = new DrawingWidget(this);
        setCentralWidget(drawingWidget);

        QToolBar *toolbar = addToolBar("Инструменты");

        QAction *rectangleAction = toolbar->addAction("Прямоугольник");
        QAction *triangleAction = toolbar->addAction("Треугольник");
        QAction *ellipseAction = toolbar->addAction("Эллипс");
        QAction *connectionAction = toolbar->addAction("Связь");
        QAction *moveAction = toolbar->addAction("Переместить");
        QAction *deleteAction = toolbar->addAction("Удалить");

        connect(deleteAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Delete);
        });
        connect(rectangleAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Rectangle);
        });
        connect(triangleAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Triangle);
        });
        connect(ellipseAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Ellipse);
        });
        connect(connectionAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Connection);
        });
        connect(moveAction, &QAction::triggered, [=]() {
            drawingWidget->setShapeType(Move);
        });
    }

private:
    DrawingWidget *drawingWidget;
};
#endif // MAINWINDOW_H
