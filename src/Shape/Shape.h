#pragma once

#include <cmath>
#include "Vector.h"

class Rotation
{
    public:
        Rotation() : 
        xAng_(0.0), 
        yAng_(0.0), 
        zAng_(0.0),
        xTrig_(xAng_.getAngle()),
        yTrig_(yAng_.getAngle()),
        zTrig_(zAng_.getAngle()),
        rMatrice_{} {}
        void virtual rotate() = 0;
        virtual ~Rotation() = default;
    
    
    protected:
        void updateRotationMatrice(
            const double incrAngleX = 0.013,
            const double incrAngleY = 0.025,
            const double incrAngleZ = 0.026
        );

    private:
        struct Angle
        {
            public:
                Angle(double ang) : angle_(ang) {}
                Angle& operator+=(double rhs);
                double getAngle() const {return angle_;}
            private:
                double angle_;
        };

        struct Trig
        {
            public:
                Trig(double angle) : 
                    cos_(cos(angle)), 
                    sin_(sin(angle)) {} 
                Trig& operator+=(const double rhs);
                double getCos() const {return cos_;}
                double getSin() const {return sin_;}
                private:
                double cos_;
                double sin_;
            };
            
            void matriceMult();

            /* Angles defined in radians */
            Angle xAng_;
            Angle yAng_;
            Angle zAng_;

            /* Trigonometic functions */
            Trig xTrig_;
            Trig yTrig_;
            Trig zTrig_;

            /* Rotation matrice */
            double rMatrice_[3][3];

};

class Shape
{
    public: 
        virtual void project() = 0;
        virtual void print() = 0;
        virtual ~Shape() = default;
};
