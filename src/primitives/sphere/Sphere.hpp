#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "../APrimitive.hpp"

class Sphere : public APrimitive {
public:
    Sphere(PrimitiveParams params);
    ~Sphere() override = default;

    Vec3 getColor() const override;

    /**
     * Method that determines if a ray intersects a sphere. For this, we need to go back to
     * mathematical concepts. As explained in the ray header, a ray is defined by:
     * P(t) = origin + t * direction
     *
     * A sphere is defined by a point (center) and a radius (radius). The sphere equation is:
     * |P - center|² = radius² (any point P on the sphere is at distance radius from the center)
     * The center being defined at the origin (0,0,0) has no effect here, just a mathematical convention.
     *
     * We look for t such that P(t) is on the sphere:
     * => |P(t) - center|² = radius²
     * => |origin + t * direction - center|² = radius²
     * => |t * direction + (origin - center)|² = radius²
     *                     └───────────────┘
     *                           = oc
     *                           (for readability)
     * => |t * direction + oc|² = radius²
     * We use |u|² = u · u:
     * => (t * direction + oc) · (t * direction + oc) = radius²
     *    └──────────────────┘   └──────────────────┘
     *           a + b                   a + b
     * Where (a + b)² = a² + 2ab + b²
     * Note: (a + b)² is a scalar identity, but a and b are vectors here.
     * So we use the dot product (·) to obtain a scalar.
     * => t² * (direction · direction) + 2 * t * (direction · oc) + (oc · oc) = radius²
     * => t² * (direction · direction) + t * 2 * (direction · oc) + (oc · oc - radius²) = 0
     *         └─────────────────────┘       └──────────────────┘   └─────────────────┘
     *                    a                           b                      c
     * So t is the unknown, and a, b, c are constants computable from the
     * ray and sphere data. This gives a second-degree polynomial: at² + bt + c = 0
     *
     * The discriminant b² - 4ac determines the result:
     * < 0  => no intersection → return -1.0
     * >= 0 => return the t of the closest hit point (root (-b - √discriminant) / 2a)
     */
    double localHit(const Ray &localRay) override;

    /**
     * Method that returns the normal at a point on the sphere, i.e. the vector perpendicular to the
     * surface at that point.
     *
     * For a sphere, it is the vector going from the center to the hit point. As explained in the
     * ray header, a ray is defined by: P(t) = origin + t * direction
     * Since t is already known from localHit, we use it to compute P(t) then the normal at that point
     *
     * So P(t) is computed via localRay.at(t) which is the method that solves the formula.
     * We subtract the center from the hit point to get a vector that starts at the center and points toward
     * the hit point: P(t) - center
     * The center being defined at the origin (0,0,0) has no effect here, just a mathematical convention.
     * Then we normalize the normal, which is necessary for lighting calculations.
     */
    Vec3 localNormalAt(const Ray &localRay, double t) override;
private:
    PrimitiveParams _params;
};

#endif
