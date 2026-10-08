#pragma once

#include "Rasterizer.h"

class Renderer
{
private:
    Transformation transformation_;
    Rasterizer rasterizer_;

public:
    Renderer(Shape& shape, IDisplay& display);
    void render();
};