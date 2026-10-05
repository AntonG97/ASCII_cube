#include "FrameBuffer.h"

#include <algorithm>
#include <limits>
#include <stdexcept>

FrameBuffer::FrameBuffer(std::size_t width, std::size_t height) :
    width_(width),
    height_(height),
    pixels_(width * height),
    depth_(width * height)
{
    if (width_ == 0 || height_ == 0)
    {
        throw std::invalid_argument("Framebuffer dimensions must be positive");
    }
    clear();
}

void FrameBuffer::clear()
{
    std::fill(pixels_.begin(), pixels_.end(), ' ');
    std::fill(depth_.begin(), depth_.end(), std::numeric_limits<double>::infinity());
}

void FrameBuffer::setPixel(std::size_t x, std::size_t y, double depth, char pixel)
{
    if (x >= width_ || y >= height_)
    {
        return;
    }

    const std::size_t index = y * width_ + x;
    if (depth < depth_[index])
    {
        depth_[index] = depth;
        pixels_[index] = pixel;
    }
}

RowView FrameBuffer::operator[](std::size_t y)
{
    if (y >= height_)
    {
        throw std::out_of_range("Framebuffer row is out of range");
    }
    return RowView(pixels_.data() + y * width_, width_);
}

std::size_t FrameBuffer::width() const
{
    return width_;
}

std::size_t FrameBuffer::height() const
{
    return height_;
}

FrameBuffer::Iterator FrameBuffer::begin()
{
    return FrameBuffer::Iterator(pixels_.data(), width_);
}

FrameBuffer::Iterator FrameBuffer::end()
{
    return FrameBuffer::Iterator(pixels_.data() + pixels_.size(), width_);
}