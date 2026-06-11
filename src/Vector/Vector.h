#pragma once

struct Vector
{
    public:
        Vector(double x, double y, double z);
        double dotProduct(const Vector& other) const;
        Vector crossProduct(const Vector& other) const;
        void scale(double scale);
        void move(int row, int col);
        void project();
        bool isEqual(const Vector& other) const;
        void setX(double);
        void setY(double);
        void setZ(double);
    private:
        double _x;
        double _y;
        double _z;
    };