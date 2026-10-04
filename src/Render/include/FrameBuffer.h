#pragma once

#include <cstddef>
#include <vector>

#include "Iterator.h"
#include "RowView.h"

class FrameBuffer
{
private:
    std::size_t width_;
    std::size_t height_;
    std::vector<char> pixels_;
    std::vector<double> depth_;

public:
    FrameBuffer(std::size_t width, std::size_t height);
    void clear();
    void setPixel(std::size_t x, std::size_t y, double depth, char pixel);
    RowView operator[](std::size_t y);
    std::size_t width() const;
    std::size_t height() const;
    Iterator begin();
    Iterator end();
};