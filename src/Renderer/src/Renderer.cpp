#include "Renderer.h"

Renderer::Renderer(Shape& shape, IDisplay& display) :
    transformation_(shape.getVertices()),
    rasterizer_(shape, display, transformation_)
{
}

void Renderer::render()
{
    rasterizer_.render();
}