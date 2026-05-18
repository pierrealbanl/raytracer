#include "Point3.hpp"

Point3::Point3() : x(0), y(0), z(0) {}

Point3::Point3(const double x, const double y, const double z) : x(x), y(y), z(z) {}

Point3 Point3::operator+(const Vec3 &u) const {
    return {x + u.t[0], y + u.t[1], z + u.t[2]};
}

Point3 Point3::operator+(const double n) const {
    return {x + n, y + n, z + n};
}

Point3 Point3::operator-(const Vec3 &u) const {
    return {x - u.t[0], y - u.t[1], z - u.t[2]};
}

Vec3 Point3::operator-(const Point3 &coord) const {
    return {x - coord.x, y - coord.y, z - coord.z};
}
