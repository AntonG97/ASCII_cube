#pragma once

#include <cstddef>

#include "RowView.h"

class IDisplay
{
public:
    virtual ~IDisplay() = default;
    virtual void drawPixel(std::size_t x, std::size_t y, char pixel) = 0;
    virtual void drawBuffer(const RowView& row) = 0;
    virtual void clear() = 0;
    virtual std::size_t getWidth() const = 0;
    virtual std::size_t getHeight() const = 0;
};