#include "Shape.h"

enum class ShapeType : uint8_t{Cube,Triangle};

namespace ShapeFactory
{
    template<uint16_t V, uint16_t T>
    Shape<V,F> createShape(ShapeType t);
};



