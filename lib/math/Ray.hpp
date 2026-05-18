#ifndef RAY_HPP
#define RAY_HPP

#include "Point3.hpp"
#include "Vec3.hpp"

class Ray {
public:
    Ray();
    Ray(const Point3 &origin, const Vec3 &direction);

    Point3 getOrigin() const;
    Vec3 getDirection() const;

    /**
     * A ray in ray tracing is a half-line that starts from a point and
     * advances in a direction.
     *
     * The formula is: P(t) = A + t * b
     * => A is the ray's origin, the starting point
     * => b is the ray's direction, a vector
     * => t is a number that says "how far we advance" in that direction
     * => P(t) is the point obtained on the ray
     *
     * When t = 0, we are at the starting point A.
     * When t increases, we advance in direction b.
     *
     *    t = 0      t = 1      t = 2      t = 3
     *    •──────────•──────────•──────────•──────────▶
     *    A        A+b        A+2b       A+3b
     * (camera)
     */
    Point3 at(double t) const;
    ~Ray() = default;
private:
    Point3 _origin;
    Vec3 _direction;
};

#endif
