#ifndef PLANE_HPP
#define PLANE_HPP

#include "../APrimitive.hpp"

class Plane : public APrimitive {
public:
    Plane(PrimitiveParams params);
    ~Plane() override = default;

    Vec3 getColor() const override;

    /**
     * Method that determines if a ray intersects a plane. For this, we need to go back to mathematical concepts.
     * As explained in the ray header, a ray is defined by: P(t) = origin + t * direction
     *
     * A plane is defined by a point (center) and a normal (normal). The plane equation is:
     * (P - center) · normal = 0 (any point P on the plane is perpendicular to the normal)
     * The center being defined at the origin (0,0,0) has no effect here, just a mathematical convention.
     *
     * We look for t such that P(t) is on the plane:
     * => (P(t) - center) · normal = 0
     * => (origin + t * direction - center) · normal = 0
     * => (t * direction + (origin - center)) · normal = 0
     *                     └───────────────┘
     *                           = oc
     *                           (for readability)
     * => (t * direction + oc) · normal = 0
     * We expand the dot product:
     * => t * (direction · normal) + oc · normal = 0
     *        └──────────────────┘
     *               = denom
     * => t * denom + oc · normal = 0
     *    └───────┘   └─────────┘
     *     a  *  t  +      b      = 0
     * So t is the unknown, and a, b are constants computable from the
     * ray and plane data. This gives a first-degree equation: at + b = 0
     *
     * If the absolute value of denom ≈ 0 → the ray is parallel to the plane → no intersection
     * Otherwise we isolate t: t = -oc · normal / denom
     * If t > 0 => intersection in front of the ray => return t
     * Otherwise => intersection behind the ray => return -1.0
     */
    double localHit(const Ray &localRay) override;

    /**
     * Method that returns the normal at a point on the plane, i.e. the vector perpendicular to the
     * surface at that point.
     */
    Vec3 localNormalAt(const Ray &localRay, double t) override;
private:
    PrimitiveParams _params;
};

#endif
