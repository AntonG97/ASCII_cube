#pragma once

#include "FrameBuffer.h"
#include "Transformation.h"
#include "IDisplay.h"
#include "Shape.h"

class Renderer
{
private:
    Shape& shape_;
    Transformation transformation_;
    IDisplay& display_;
    FrameBuffer buffer_;

    void fillFace(const Face& face, char pixel);

public:
    Renderer(Shape& shape, IDisplay& display);
    void render();
};