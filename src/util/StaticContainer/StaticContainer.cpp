#include "StaticContainer.h"

template<typename T, size_t N>
void StaticVector<T, N>::push_back(const T& v)
{
    if(size < N)
    {
        _arr[size++] = v;
    }
}

template<typename T, size_t N>
T& StaticVector<T, N>::operator[](size_t i)
{
    if(i < N) 
    {
        return _arr[i]; 
    }
}

