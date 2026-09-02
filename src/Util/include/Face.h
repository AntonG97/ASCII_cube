#pragma once
#include "Vec3.h"

struct Face
{
    const Vec3& const a_;
    const Vec3& const b_;
    const Vec3& const c_;

    Face(const Vec3& a, const Vec3& b, const Vec3 c) : a_(a), b_(b), c_(c) {}
    Face(const Face& rhs) = delete;
    Face& operator=(const Face& rhs) = delete;
};