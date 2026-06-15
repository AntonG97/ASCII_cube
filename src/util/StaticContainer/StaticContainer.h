#include "stddef.h"

template<typename T, size_t N>
class StaticVector
{
private:
    T _arr[N];
    size_t _size = 0;

public:
    void push_back(const T& v);
    T& operator[](size_t i);
};

