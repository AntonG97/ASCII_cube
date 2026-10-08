#pragma once

#include "Rasterizer.h"
#include "Transformation.h"

class Shape;
class Renderer
{
private:
    Shape& shape_;
    Transformation transformation_;
    Rasterizer rasterizer_;

public:
    Renderer(Shape& shape, IDisplay& display, int scale);
    void render();
};