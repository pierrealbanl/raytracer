#ifndef VEC3_HPP
#define VEC3_HPP

/**
 * Inserts a runtime check:
 * - If true, the program continues normally
 * - If false, the program stops with an error message
 */
#include <cassert>
#include <cmath>
#include <ostream>

class Vec3 {
public:
    double t[3]; // array of three numbers x, y, z

    // Initializes a null vector
    Vec3();

    // Initializes a vector with values
    Vec3(double x, double y, double z);
    ~Vec3() = default;

    // Negates the values of the array
    Vec3 operator-() const;

    // Allows reading the value at index i
    double operator[](int i) const;

    // Allows modifying the value at index i
    double &operator[](int i);

    // Add vector v to the current vector
    Vec3 &operator+=(const Vec3& u);

    /**
     * In mathematics, there is no single obvious way to multiply two vectors.
     * However, you can multiply a vector by a number: each component of the vector,
     * namely x, y, and z, is then multiplied by that number.
     * So here, n is multiplied by x, y, and z.
     */
    Vec3 &operator*=(double n);

    /**
     * In mathematics, dividing by a number is equivalent to multiplying by its reciprocal.
     *
     * Example:
     * (6, 9, 12) / 3
     * = (6 * 1/3, 9 * 1/3, 12 * 1/3)
     * = (2, 3, 4)
     */
    Vec3 &operator/=(double n);

    /**
     * In mathematics, to calculate the length of a vector,
     * you use the following formula:
     * square root of the sum of squares, i.e. sqrt(x² + y² + z²).
     */
    double vecLengthSquared() const;
    double vecLength() const;

    /**
     * Takes two vectors and returns a number: the dot product.
     * dot(u, v) = ux * vx + uy * vy + uz * vz
     */
    double dot(const Vec3 &u) const;

    /**
     * Takes two vectors and returns a new vector: the cross product.
     * cross(u, v) = (uy * vz - uz * vy, uz * vx - ux * vz, ux * vy - uy * vx)
     */
    Vec3 cross(const Vec3 &u) const;

    /**
     * Takes a vector and normalizes it: the direction stays the same, but the
     * result will have a length of 1.
     * To do this, each component x, y, and z is divided by the vector's length.
     *
     * We normalize so that calculations (dot product, offset) are independent of the
     * input vector's length. Used notably for surface normals and
     * light directions.
     */
    Vec3 unitVector() const;

    /**
     * These operations are utility functions for vectors.
     * They allow performing various operations between two vectors
     * and return a new vector.
     */
    std::ostream& operator<<(std::ostream &out) const;
    Vec3 operator+(const Vec3 &u) const;
    Vec3 operator-(const Vec3 &u) const;
    Vec3 operator-(double n) const;
    Vec3 operator*(const Vec3 &u) const;
    Vec3 operator*(double n) const;
    Vec3 operator/(double n) const;
};

#endif
