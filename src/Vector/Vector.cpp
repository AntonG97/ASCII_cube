#include "Vector.h"
#include <math.h>
#include <cassert>

Vector::Vector(double x, double y, double z) : _x(x), _y(y), _z(z) 
{
    assert(_z > 0 && "z-coordinate requires z > 0");
}
double Vector::dotProduct(const Vector& other) const
{
    return _x*other._x + _y*other._y + _z*other._z;
}
Vector Vector::crossProduct(const Vector& other) const
{
    double X = _y*other._z - _z*other._y;
    double Y = _z*other._x - _x*other._y;
    double Z = _x*other._y - _y*other._x;
    return Vector(X,Y,Z);
}
void Vector::scale(double scale)
{
    _x *= scale;
    _y *= scale;
}
void Vector::move(int row, int col)
{
    int aspect_ratio = col / row;
    _x = round(_x*aspect_ratio + (double)(col/2));
    _y = round(_y + (double)(row/2));
}
void Vector::project()
{
    double focalLenght = 1.0f;
    _x = (_x*focalLenght) / _z;
    _y = (_y*focalLenght) / _z;
}
bool Vector::isEqual(const Vector& other) const
{
    if(_x == other._x && _y == other._y && _z == other._z)
        return true;

    return false;
}