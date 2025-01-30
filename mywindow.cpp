#include <QFileDialog>

#include "mywindow.h"
#include "paint.h"

MyWindow::MyWindow()/*(QMainWindow *parent) : QMainWindow(parent)*/
{
    QToolBar* toolbar = createLayout();
    _paint = new Paint;

    addToolBar(toolbar);
    setCentralWidget(_paint);
    resize(800, 600);
}

QToolBar* MyWindow::createLayout()
{
    // Создаём тулбар в конструкторе
    QToolBar *toolbar = new QToolBar;

    // Добавляем действия в тулбар
    QPushButton* rectangleButton = createStrategyButton("Прямоугольник", StrategyButton::rectangle);
    QPushButton* triangleButton = createStrategyButton("Треугольник", StrategyButton::triangle);
    QPushButton* ellipseButton = createStrategyButton("Эллипс", StrategyButton::ellipse);
    QPushButton* moveButton = createStrategyButton("Переместить", StrategyButton::move);
    QPushButton* connectButton = createStrategyButton("Связь", StrategyButton::connect);
    QPushButton* deleteButton = createStrategyButton("Удалить", StrategyButton::erase);

    QPushButton* saveButton = new QPushButton("Сохранить");
    QPushButton* loadButton = new QPushButton("Загрузить");

    // Подключаем слоты для этих кнопок
    connect(saveButton, &QPushButton::clicked, this, &MyWindow::saveFile);
    connect(loadButton, &QPushButton::clicked, this, &MyWindow::loadFile);

    toolbar->addWidget(rectangleButton);
    toolbar->addWidget(triangleButton);
    toolbar->addWidget(ellipseButton);
    toolbar->addSeparator();
    toolbar->addWidget(connectButton);
    toolbar->addSeparator();
    toolbar->addWidget(moveButton);
    toolbar->addWidget(deleteButton);
    toolbar->addSeparator();
    toolbar->addWidget(saveButton);
    toolbar->addWidget(loadButton);


    return toolbar;
}

void MyWindow::strategyButtonPressed()
{
    StrategyButton button = _buttonMap.at(sender());
    auto strategy = _strategyFactory.at(button)();

    _paint->setStrategy(std::move(strategy)); // Меняем стратегию в рабочем пространстве

}

QPushButton* MyWindow::createStrategyButton(const QString& title, const StrategyButton type)
{
    QPushButton* button{new QPushButton(title)};
    button->setCheckable(true);

    connect(button, &QPushButton::clicked, this, &MyWindow::strategyButtonPressed);
    connect(button, &QPushButton::clicked, this, &MyWindow::buttonHighlighter);
    _buttonMap[button] = type;
    

    return button;
}

void MyWindow::buttonHighlighter()
{
    // Выключаем подсветку всех кнопок
    for (auto buttonPair: _buttonMap)
    {
        QPushButton* buttonPtr = qobject_cast<QPushButton*>(buttonPair.first);
        buttonPtr->setChecked(false);
    }

    // Включаем у кнопки-sender
    QPushButton* senderBut = qobject_cast<QPushButton*>(sender());
    senderBut->setChecked(true);
}

void MyWindow::saveFile()
{
    // Открываем диалоговое окно для выбора файла для сохранения
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "JSON Files (*.json);;All Files (*)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        _paint->saveToFile(file);
    }
}

void MyWindow::loadFile()
{
    // Открываем диалоговое окно для выбора файла для загрузки
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить файл", "", "JSON Files (*.json);;All Files (*)");

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        _paint->loadFromFile(file);
    }
}