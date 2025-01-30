#include "action_strategy.h"
#include "paint.h"

ActionStrategy::ActionStrategy(Paint* context) : _context(context)
{

}


DefaultShape* ActionStrategy::findShape(const QPoint& pos) const
{   
    for (const auto& shape : _context->shapes())
    {
        if (shape->contains(pos)) {return shape.get();}
    }
    return nullptr;
}
