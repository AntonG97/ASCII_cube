#pragma once

#include "FrameBuffer.h"

class Shape;
class Face;
class IDisplay;
class Rasterizer
{
private:
    IDisplay& display_;
    FrameBuffer buffer_;

    void fillFace(const Face& face, char pixel);

public:
    Rasterizer(IDisplay& display);
    void render(const std::vector<Face>& faces);
};