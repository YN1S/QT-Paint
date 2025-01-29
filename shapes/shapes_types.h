#pragma once

#include "shapes/default_shape.h"
#include <map>
#include <functional>
#include <memory>

// Forward declaration для класса Shape
class DefaultShape;

enum class ShapeType
{
    ellipse,
    rectangle,
    triangle
};

extern const std::map<ShapeType, std::function<std::unique_ptr<DefaultShape>(void)>> shapeFactory;