#include "Plane.hpp"

Plane::Plane(PrimitiveParams params)
: _params(std::move(params)) {}

Vec3 Plane::getColor() const {
    return _params.colorRGB->getColor();
}

Vec3 Plane::localNormalAt(const Ray &localRay, const double t) {
    (void)localRay;
    (void)t;
    return _params.normal.value();
}

double Plane::localHit(const Ray &localRay) {
    const Vec3 normal = _params.normal.value();
    const double denom = normal.dot(localRay.getDirection());

    if (std::abs(denom) < 1e-6)
        return -1.0;
    const Vec3 oc = localRay.getOrigin() - _params.origin;
    const double t = -oc.dot(normal) / denom;
    if (t > 0)
        return t;
    return -1.0;
}
