#pragma once
#include <array>
#include "stdlib.h"
#include "Vec3.h"
#include "Angle.h"

template<std::size_t V>
struct RotationMatrice
{
private:
    double m_[3][3]; 
    const std::array<Vec3,V> originalCp_;
public:
    constexpr RotationMatrice(const std::array<Vec3,V>& original);
    double& operator[](std::size_t index);
    double operator[](std::size_t index) const;
    void rotateVectors(
        std::array<Vec3,V>& vectors,
        const Angle& x,
        const Angle& y,
        const Angle& z);
private:
    void calculateAngle(
        const Angle& x,
        const Angle& y,
        const Angle& z);
};

template<std::size_t V>
constexpr RotationMatrice<V>::RotationMatrice(const std::array<Vec3,V>& original) :
    m_({}),
    originalCp_(original)
    {

    }

template<std::size_t V>
void RotationMatrice<V>::rotateVectors(
        std::array<Vec3,V>& vectors,
        const Angle& x,
        const Angle& y,
        const Angle& z)
{

}