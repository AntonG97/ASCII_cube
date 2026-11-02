#pragma once

#include <cstddef>
#include <vector>

#include "RowView.h"

class FrameBuffer
{
private:
    const std::size_t width_;
    const std::size_t height_;
    std::vector<char> pixels_;

public:
    class Iterator
    {
    private:
        char* data_;
        std::size_t rowWidth_;

    public:
        Iterator(char* data, std::size_t rowWidth);
        RowView operator*() const;
        Iterator& operator++();
        bool operator!=(const Iterator& rhs) const;
        bool operator==(const Iterator& rhs) const;
    };

    FrameBuffer(const std::size_t width, const std::size_t height);
    void clear();
    void setPixel(const std::size_t x, const std::size_t y, char pixel);
    RowView operator[](const std::size_t y);
    std::size_t width() const;
    std::size_t height() const;
    Iterator begin();
    Iterator end();
};