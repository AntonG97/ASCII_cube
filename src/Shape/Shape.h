#pragma once

#include <cmath>
#include "Vector.h"

class Rotation
{
    public:
        Rotation() : 
        _x(0.0f),
        _y(0.0f),
        _z(0.0f),
        rMatrice_{} {}
        void virtual rotate() = 0;
        virtual ~Rotation() = default;
    
    
    protected:
        void updateRotationMatrice(
            const double incrAngleX = 0.013,
            const double incrAngleY = 0.025,
            const double incrAngleZ = 0.026
        );
        const double rotateX() const;
        const double rotateY() const;
        const double rotateZ() const;

        //Each Object of Trigonometic contains an angle and cos&sin values
        struct Trigonometic
        {
            public:
                Trigonometic(double angle) : 
                    _angle(angle),
                    _cos(std::cos(angle)),
                    _sin(std::sin(angle))
                    {
                        //Constructor body
                    }
                Trigonometic& operator+=(const double rhs);
                double getSin() const   {return _sin;}
                double getCos() const   {return _cos;}
                double getAngle() const {return _angle;}
            private:
                double _angle;      
                double _cos;
                double _sin;
        };
          
        private:
            void matriceMult();

            Trigonometic _x;
            Trigonometic _y;
            Trigonometic _z;
            
            //Rotation matrice
            double rMatrice_[3][3];
};

class Shape
{
    public: 
        virtual void project() = 0;
        virtual void print() = 0;
        virtual ~Shape() = default;
};
