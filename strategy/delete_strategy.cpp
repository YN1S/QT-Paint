#include "delete_strategy.h"
#include "shapes/default_shape.h"
#include "strategy/action_strategy.h"
#include "paint.h"

DeleteStrategy::DeleteStrategy(Paint *context)
    : ActionStrategy(context)
{

}

void DeleteStrategy::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        DefaultShape* shapeToDelete = findShape(event->pos());

        if (shapeToDelete) {
            // Удаляем все связи, связанные с фигурой
            _context->removeConnection(shapeToDelete);            

            // Удаляем фигуру из списка
            _context->removeShape(shapeToDelete);

            _context->update();
        }
    }
}

void DeleteStrategy::mouseMoveEvent(QMouseEvent *event)
{

}

void DeleteStrategy::mouseReleaseEvent(QMouseEvent *event)
{

}

void DeleteStrategy::keyPressEvent(QKeyEvent *event)
{

}

void DeleteStrategy::drawTemporary(QPainter *painter)
{

}

void DeleteStrategy::cancel()
{

}
