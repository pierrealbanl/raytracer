#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include "Vec3.hpp"
#include "Point3.hpp"

#include <cmath>

class Matrix4 {
public:
    double m[4][4]{}; // m[row][col]

    /**
     * Initializes an identity matrix: a grid of numbers that, when applied
     * to a point, changes absolutely nothing. Applying the identity matrix
     * to a point is equivalent to multiplying each coordinate by 1. Since the diagonal is initialized to 1,
     * if x = 10 then it gives 10 × 1 = 10. The point comes out unchanged.
     *
     * The translation() and rotation() functions start from this base
     * and only overwrite the cells that need to change.
     *
     *          col0  col1  col2  col3
     *        ┌─────┬─────┬─────┬─────┐
     *   row0 │  1  │  0  │  0  │  0  │ x
     *        ├─────┼─────┼─────┼─────┤
     *   row1 │  0  │  1  │  0  │  0  │ y
     *        ├─────┼─────┼─────┼─────┤
     *   row2 │  0  │  0  │  1  │  0  │ z
     *        ├─────┼─────┼─────┼─────┤
     *   row3 │  0  │  0  │  0  │  1  │ 1
     *        └─────┴─────┴─────┴─────┘
     */
    Matrix4();

    // Applies the matrix to a point (a position in space, translation applies)
    Point3 applyPoint(const Point3 &p) const;

    // Applies the matrix to a vector (a direction, translation is ignored)
    Vec3 applyVec(const Vec3 &v) const;

    /**
     * Returns the inverse matrix via the formula: A⁻¹ = (1 / det(A)) × adj(A) i.e.
     * inverse matrix = (1 / determinant of A) × adjugate matrix of A
     * If the determinant equals 0, the matrix is not invertible.
     * For the determinant calculation, see det3().
     *
     * Each cofactor c[row][col] is computed by removing row and col
     * from the 4×4 matrix, then computing the determinant of the remaining 3×3 sub-matrix.
     * A + or - sign is applied depending on position: if row + col is even then it's +, otherwise it's -.
     *
     * Example for c[1][2] (we remove row1 and col2):
     *
     *         col0  col1  col2  col3
     *        ┌─────┬─────┬─────┬─────┐
     *   row0 │ 0,0 │ 0,1 │  X  │ 0,3 │
     *        ├─────┼─────┼─────┼─────┤
     *   row1 │  X  │  X  │  X  │  X  │ ◀── removed
     *        ├─────┼─────┼─────┼─────┤
     *   row2 │ 2,0 │ 2,1 │  X  │ 2,3 │
     *        ├─────┼─────┼─────┼─────┤
     *   row3 │ 3,0 │ 3,1 │  X  │ 3,3 │
     *        └─────┴─────┴─────┴─────┘
     *                       ▲
     *                    removed
     */
    Matrix4 inverse() const;

    // Overwrites the 3 cells of the last column with values tx, ty, tz
    static Matrix4 translation(double tx, double ty, double tz);
};

#endif
