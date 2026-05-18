#ifndef AOBJECT_HPP
#define AOBJECT_HPP

#include "IPrimitive.hpp"
#include "../../lib/math/Matrix4.hpp"

/**
 * => World space is the global scene space where everything exists together (camera, lights, objects).
 * => Local space is each object's own space, always centered at the origin (0, 0, 0).
 *
 * Intersection formulas are written in local space; it's the ray that is converted, not the object.
 */
class APrimitive : public IPrimitive {
public:
    APrimitive();
    ~APrimitive() override = default;

    // Stores the transformation and precomputes its inverse to avoid recalculating it for every ray
    void setTransform(const Matrix4 &m) override;

    Vec3 getColor() const override;

    /**
     * Converts the ray from world space to local space via the inverse of the matrix
     * (undoes the object's transformation), then delegates the intersection test to localHit() defined in
     * each primitive.
     *
     * world space:                local space:
     * camera (0, 0, -5)           camera (-60, 0, -5)
     *    \                           \
     *     \  ray                      \  converted ray
     *      ▼                           ▼
     *   sphere (60, 0, 0)          sphere (0, 0, 0)
     *
     * Returns the distance t between the camera and the intersection point, or -1 if no intersection.
     */
    double hit(const Ray &r) override;

    /**
     * Converts the ray from world space to local space via the inverse of the matrix
     * (undoes the object's transformation), then delegates to the concrete primitive (sphere, plane...)
     * which computes the normal in its own space.
     *
     * world space:                local space:
     * camera (0, 0, -5)           camera (-60, 0, -5)
     *    \                           \
     *     \  ray                      \  converted ray
     *      ▼                           ▼
     *   sphere (60, 0, 0)          sphere (0, 0, 0)
     *
     * Once the localNormal is determined, we need to transform it back to worldSpace to get a worldNormal
     * via the transpose of the inverse.
     * For this we use the perpendicularity condition formula: N · T = 0
     * T is a tangent to the surface, so after transformation by the matrix:
     * => T_world = M * T_local
     * We look for a matrix X such that:
     * => (X * N_local) · (M * T_local) = 0
     *    └───────────┘   └───────────┘
     *       N_world         T_world
     * In matrix notation, the dot product u · v = uᵀv.
     * A small math note: the transpose of a column vector u, uᵀ transforms it into a row vector:
     *     [x]
     * u = [y] ──▶ uᵀ = [x  y  z]
     *     [z]
     * => (X * N_local)ᵀ * (M * T_local) = 0
     * => N_localᵀ * Xᵀ * (M * T_local) = 0
     * For this to be true for all T_local, we need:
     * N_localᵀ * Xᵀ * M = 0
     * Which implies that Xᵀ * M = I, where I is the identity matrix, therefore:
     * Xᵀ = M⁻¹
     * X = (M⁻¹)ᵀ
     * So the matrix that correctly transforms normals is (M⁻¹)ᵀ, which gives:
     * => N_world = (M⁻¹)ᵀ * N_local
     *
     * In code, the transpose translates to swapping indices: m[col][row]
     * instead of m[row][col].
     */
    Vec3 getNormalAt(const Ray &r, double t) override;
private:
    Matrix4 _m;
    Matrix4 _invM;
};

#endif
