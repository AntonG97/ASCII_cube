#include "RowView.h"

RowView::RowView(char* data, std::size_t size) :
    data_(data),
    size_(size)
{
}

char RowView::operator[](std::size_t index) const
{
    return data_[index];
}

const char* RowView::begin() const
{
    return data_;
}

const char* RowView::end() const
{
    return data_ + size_;
}

std::size_t RowView::size() const
{
    return size_;
}