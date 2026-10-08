#include "Renderer.h"
#include "Shape.h"

Renderer::Renderer(Shape& shape, IDisplay& display, int scale) :
    shape_(shape),
    transformation_(shape.getVertices()),
    rasterizer_(display, scale)
{
}

void Renderer::render()
{
    transformation_.transform(shape_.getVertices());
    rasterizer_.render(shape_.getFaces());
}