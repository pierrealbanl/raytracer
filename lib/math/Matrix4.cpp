#include "Matrix4.hpp"

Matrix4::Matrix4() {
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++) {
            if (row == col)
                m[row][col] = 1.0;
            else
                m[row][col] = 0.0;
        }
}

Point3 Matrix4::applyPoint(const Point3 &p) const {
    return {
        m[0][0] * p.x + m[0][1] * p.y + m[0][2] * p.z + m[0][3],
        m[1][0] * p.x + m[1][1] * p.y + m[1][2] * p.z + m[1][3],
        m[2][0] * p.x + m[2][1] * p.y + m[2][2] * p.z + m[2][3]
    };
}

Vec3 Matrix4::applyVec(const Vec3 &v) const {
    return {
        m[0][0] * v.t[0] + m[0][1] * v.t[1] + m[0][2] * v.t[2],
        m[1][0] * v.t[0] + m[1][1] * v.t[1] + m[1][2] * v.t[2],
        m[2][0] * v.t[0] + m[2][1] * v.t[1] + m[2][2] * v.t[2]
    };
}

/**
 * Computes the determinant of a 3×3 matrix, used by inverse() to compute cofactors.
 * The determinant is a number that indicates whether a matrix is invertible (!= 0) or not (= 0).
 *
 *          col0  col1  col2
 *        ┌─────┬─────┬─────┐
 *   row0 │  a  │  b  │  c  │
 *        ├─────┼─────┼─────┤
 *   row1 │  d  │  e  │  f  │ ──▶ a(ei - fh) - b(di - fg) + c(dh - eg)
 *        ├─────┼─────┼─────┤
 *   row2 │  g  │  h  │  i  │
 *        └─────┴─────┴─────┘
 */
static double det3(
    const double a, const double b, const double c,
    const double d, const double e, const double f,
    const double g, const double h, const double i)
{
    return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

Matrix4 Matrix4::inverse() const {
    double adj[4][4];
    double det4 = 0;
    Matrix4 result;

    adj[0][0] = +det3(m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
    adj[0][1] = -det3(m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
    adj[0][2] = +det3(m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
    adj[0][3] = -det3(m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

    adj[1][0] = -det3(m[0][1], m[0][2], m[0][3], m[2][1], m[2][2], m[2][3], m[3][1], m[3][2], m[3][3]);
    adj[1][1] = +det3(m[0][0], m[0][2], m[0][3], m[2][0], m[2][2], m[2][3], m[3][0], m[3][2], m[3][3]);
    adj[1][2] = -det3(m[0][0], m[0][1], m[0][3], m[2][0], m[2][1], m[2][3], m[3][0], m[3][1], m[3][3]);
    adj[1][3] = +det3(m[0][0], m[0][1], m[0][2], m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]);

    adj[2][0] = +det3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[3][1], m[3][2], m[3][3]);
    adj[2][1] = -det3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[3][0], m[3][2], m[3][3]);
    adj[2][2] = +det3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[3][0], m[3][1], m[3][3]);
    adj[2][3] = -det3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[3][0], m[3][1], m[3][2]);

    adj[3][0] = -det3(m[0][1], m[0][2], m[0][3], m[1][1], m[1][2], m[1][3], m[2][1], m[2][2], m[2][3]);
    adj[3][1] = +det3(m[0][0], m[0][2], m[0][3], m[1][0], m[1][2], m[1][3], m[2][0], m[2][2], m[2][3]);
    adj[3][2] = -det3(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[2][0], m[2][1], m[2][3]);
    adj[3][3] = +det3(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);

    det4 = m[0][0] * adj[0][0] + m[0][1] * adj[0][1] + m[0][2] * adj[0][2] + m[0][3] * adj[0][3];
    if (det4 == 0.0)
        return result;
    for (int row = 0; row < 4; row++)
        for (int col = 0; col < 4; col++)
            result.m[row][col] = adj[col][row] / det4;
    return result;
}

Matrix4 Matrix4::translation(const double tx, const double ty, const double tz) {
    Matrix4 t;

    t.m[0][3] = tx;
    t.m[1][3] = ty;
    t.m[2][3] = tz;
    return t;
}
