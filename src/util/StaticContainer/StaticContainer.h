#pragma once
#include "stddef.h"

//Use StaticVector as a container. The idea is to use a user defined container
//and not from Vector header. The program will run on both an all purpose computer
//and embedded systems

template<typename T, size_t N>
class StaticContainer 
{
private:
    T _arr[N];
    size_t _size = 0;

public:
    void push_back(const T& v);
    T& operator[](size_t i);
};

#include "StaticContainer.tpp"