#include "paint.h"


Paint::Paint(QFrame *parent)
{
    setObjectName("paint");
    setFocusPolicy(Qt::WheelFocus);
}

void Paint::setStrategy(std::unique_ptr<ActionStrategy> strategy)
{
    _strategy = std::move(strategy);
}

void Paint::addShape(std::unique_ptr<DefaultShape> shape)
{
    _shapes.push_back(std::move(shape));
}

void Paint::mousePressEvent(QMouseEvent *event)
{
    if (_strategy) {_strategy->mousePressEvent(event);}
}

void Paint::mouseMoveEvent(QMouseEvent *event)
{
    if (_strategy) _strategy->mouseMoveEvent(event);
}

void Paint::mouseReleaseEvent(QMouseEvent *event)
{
    if (_strategy) _strategy->mouseReleaseEvent(event);
}

void Paint::keyPressEvent(QKeyEvent *event)
{
    if (_strategy) _strategy->keyPressEvent(event);
}

void Paint::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);
    painter.setPen(Qt::black);

    for (auto& DefaultShape: _shapes)
    {
        DefaultShape->draw(&painter);
    }

    if (_strategy)
    {
        _strategy->drawTemporary(&painter);
    }
}
