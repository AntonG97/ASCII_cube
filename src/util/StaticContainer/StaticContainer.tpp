#include "StaticContainer.h"

template<typename T, size_t N>
void StaticContainer<T, N>::push_back(const T& v)
{
    if(size < N)
    {
        _arr[size++] = v;
    }
}

template<typename T, size_t N>
T& StaticContainer<T, N>::operator[](size_t i)
{
    if(i < N) 
    {
        return _arr[i]; 
    }
}