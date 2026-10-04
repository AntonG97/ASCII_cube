#pragma once

#include <cstddef>

#include "RowView.h"

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