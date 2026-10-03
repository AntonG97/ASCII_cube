#pragma once

struct Angle
{
    double angle_;
    Angle& operator+=(const Angle& rhs);
    Angle& operator+=(double);
    explicit operator double() const;  
       double sin() const;
       double cos() const;
};