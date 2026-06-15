#include "Vec3.h"
#include <math.h>
#include <cassert>

Vec3::Vec3(double x, double y, double z) : _x(x), _y(y), _z(z) 
{
    assert(_z != 0 && "z-coordinate requires z > 0");
}
double Vec3::dotProduct(const Vec3& other) const
{
    return _x*other._x + _y*other._y + _z*other._z;
}
Vec3 Vec3::crossProduct(const Vec3& other) const
{
    double X = _y*other._z - _z*other._y;
    double Y = _z*other._x - _x*other._y;
    double Z = _x*other._y - _y*other._x;
    return Vec3(X,Y,Z);
}
void Vec3::scale(double scale)
{
    _x *= scale;
    _y *= scale;
}
void Vec3::move(int row, int col)
{
    int aspect_ratio = col / row;
    _x = round(_x*aspect_ratio + (double)(col/2));
    _y = round(_y + (double)(row/2));
}
void Vec3::project()
{
    double focalLenght = 1.0f;
    _x = (_x*focalLenght) / _z;
    _y = (_y*focalLenght) / _z;
}
bool Vec3::isEqual(const Vec3& other) const
{
    if(_x == other._x && _y == other._y && _z == other._z)
        return true;

    return false;
}
void Vec3::setX(double val) {_x = val; }
void Vec3::setY(double val) {_y = val; }
void Vec3::setZ(double val) {_z = val; }