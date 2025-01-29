#pragma once

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>

#include "paint.h"
#include "strategy/action_strategy.h"
#include "strategy/shapes_strategy.h"

enum class StrategyButton
{
    ellipse,
    rectangle,
    triangle,
    connect,
    move,
    erase
};


class MyWindow : public QMainWindow
{
    Q_OBJECT
public:
    MyWindow();
    QToolBar* createLayout();

private:
    Paint* _paint;

    std::map<QObject*, StrategyButton> _buttonMap;
    std::map<StrategyButton, std::function<std::unique_ptr<ActionStrategy>(void)>> _strategyFactory
    {
        // {StrategyButton::ellipse, [this](){return std::make_unique<ShapesStrategy>(_paint, ShapeType::ellipse);}},
        {StrategyButton::rectangle, [this](){ return std::make_unique<ShapesStrategy>(_paint, ShapeType::rectangle); }}
        // {StrategyButton::triangle, [this](){return std::make_unique<ShapesStrategy>(_paint, ShapeType::triangle);}}
    }; 

    void strategyButtonPressed();
    QPushButton* createStrategyButton(const QString& title, const StrategyButton type);
    void buttonHighlighter();
};

