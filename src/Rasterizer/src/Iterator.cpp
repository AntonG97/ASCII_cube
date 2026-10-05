#include "FrameBuffer.h"

FrameBuffer::Iterator::Iterator(char* data, std::size_t rowWidth) :
    data_(data),
    rowWidth_(rowWidth)
{
}

RowView FrameBuffer::Iterator::operator*() const
{
    return RowView(data_, rowWidth_);
}

FrameBuffer::Iterator& FrameBuffer::Iterator::operator++()
{
    data_ += rowWidth_;
    return *this;
}

bool FrameBuffer::Iterator::operator!=(const Iterator& rhs) const
{
    return data_ != rhs.data_;
}

bool FrameBuffer::Iterator::operator==(const Iterator& rhs) const
{
    return data_ == rhs.data_;
}