#pragma once

#include <cstddef>

class RowView
{
private:
    char* data_;
    std::size_t size_;

public:
    RowView(char* data, std::size_t size);
    char operator[](std::size_t index) const;
    const char* begin() const;
    const char* end() const;
    std::size_t size() const;
};