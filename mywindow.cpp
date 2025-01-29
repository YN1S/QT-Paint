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

    toolbar->addWidget(rectangleButton);
    toolbar->addWidget(triangleButton);
    toolbar->addWidget(ellipseButton);

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