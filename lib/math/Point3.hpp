#ifndef POINT3_HPP
#define POINT3_HPP

#include "Vec3.hpp"

class Point3 {
public:
    double x;
    double y;
    double z;

    Point3();
    Point3(double x, double y, double z);
    ~Point3() = default;

    /**
     * These operations are utility functions for coordinates.
     * They allow performing various operations between two coordinates
     * and return a new coordinate.
     */
    Point3 operator+(const Vec3 &u) const;
    Point3 operator+(double n) const;
    Point3 operator-(const Vec3 &u) const;
    Vec3 operator-(const Point3 &coord) const;
};

#endif
