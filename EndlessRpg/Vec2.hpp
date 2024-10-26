#pragma once
#include <math.h>

class Vec2
{
public:
    double x;
    double y;

    Vec2();
    Vec2(double x, double y);

    bool operator == (const Vec2 & v2) const;

    bool operator != (const Vec2 & v2) const;
    Vec2 operator + (const Vec2 & v2) const;
    Vec2 operator - (const Vec2 & v2) const;
    Vec2 operator * (const double val) const;
    Vec2 operator / (const double val) const;

    void operator += (const Vec2 & v2);
    void operator -= (const Vec2 & v2);
    void operator *= (const double val);
    void operator /= (const double val);

    double dist(const Vec2 & v2) const; 

    double getX() const;
    double getY() const;
    void setX(const double num);
    void setY(const double num);
};