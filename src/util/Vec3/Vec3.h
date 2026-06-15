#pragma once

struct Vec3
{
    public:
        Vec3(double x, double y, double z);
        double dotProduct(const Vec3& other) const;
        Vec3 crossProduct(const Vec3& other) const;
        void scale(double scale);
        void move(int row, int col);
        void project();
        bool isEqual(const Vec3& other) const;
        void setX(double);
        void setY(double);
        void setZ(double);
    private:
        double _x;
        double _y;
        double _z;
    };