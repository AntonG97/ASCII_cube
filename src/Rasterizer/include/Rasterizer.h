#pragma once

#include "FrameBuffer.h"
#include "Transformation.h"
#include "IDisplay.h"
#include "Shape.h"

class Rasterizer
{
private:
    Shape& shape_;
    Transformation transformation_;
    IDisplay& display_;
    FrameBuffer buffer_;

    void fillFace(const Face& face, char pixel);

public:
    Rasterizer(Shape& shape, IDisplay& display);
    void render();
};