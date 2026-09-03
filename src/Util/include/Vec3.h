#pragma once
struct Vec3
{
    // Coordinates
    double x_{};
    double y_{};
    double z_{};

    // Constructor
    Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {}
    Vec3(const Vec3& rhs);
    Vec3& operator=(const Vec3& rhs);

    // Methods
    constexpr double dot(const Vec3& rhs) const;
    constexpr Vec3 cross(const Vec3& rhs) const;
    
    constexpr bool operator==(const Vec3& rhs) const;
    constexpr bool operator!=(const Vec3& rhs) const;

    constexpr Vec3 operator+(const Vec3& rhs) const;
    constexpr Vec3 operator-(const Vec3& rhs) const;
    constexpr Vec3 operator*(double scalar) const;
    constexpr Vec3 operator/(double scalar) const;

    Vec3& operator+=(const Vec3& rhs);
    Vec3& operator-=(const Vec3& rhs);
    Vec3& operator*=(const Vec3& rhs);
    Vec3& operator/=(const Vec3& rhs);
};
        
        