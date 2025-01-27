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
        QAction *saveAction = toolbar->addAction("Сохранить");
        QAction *loadAction = toolbar->addAction("Загрузить");


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
        connect(saveAction, &QAction::triggered, [this]() {
            QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "JSON Files (*.json)");
            if (!fileName.isEmpty()) {
                drawingWidget->saveToFile(fileName);
            }
        });

        connect(loadAction, &QAction::triggered, [this]() {
            QString fileName = QFileDialog::getOpenFileName(this, "Загрузить файл", "", "JSON Files (*.json)");
            if (!fileName.isEmpty()) {
                drawingWidget->loadFromFile(fileName);
            }
        });
    }

private:
    DrawingWidget *drawingWidget;
};
#endif // MAINWINDOW_H
