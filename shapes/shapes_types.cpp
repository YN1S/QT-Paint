#include "rectangle.h"
#include "ellipse.h"
#include "triangle.h"

#include "shapes/default_shape.h"
#include "shapes/shapes_types.h"

const std::map<ShapeType, std::function<std::unique_ptr<DefaultShape>(void)>> shapeFactory =
{    
    {ShapeType::ellipse, [](){ return std::make_unique<Ellipse>(); }},
    {ShapeType::rectangle, [](){ return std::make_unique<Rectangle>(); }},
    {ShapeType::triangle, [](){ return std::make_unique<Triangle>(); }}
};