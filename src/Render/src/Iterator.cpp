#include "Iterator.h"

Iterator::Iterator(char* data, std::size_t rowWidth) :
    data_(data),
    rowWidth_(rowWidth)
{
}

RowView Iterator::operator*() const
{
    return RowView(data_, rowWidth_);
}

Iterator& Iterator::operator++()
{
    data_ += rowWidth_;
    return *this;
}

bool Iterator::operator!=(const Iterator& rhs) const
{
    return data_ != rhs.data_;
}

bool Iterator::operator==(const Iterator& rhs) const
{
    return data_ == rhs.data_;
}