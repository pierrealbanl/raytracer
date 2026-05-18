#include "Sphere.hpp"

Sphere::Sphere(PrimitiveParams params)
: _params(std::move(params)) {}

Vec3 Sphere::getColor() const {
    return _params.colorRGB->getColor();
}

Vec3 Sphere::localNormalAt(const Ray &localRay, const double t) {
    const Vec3 normal = localRay.at(t) - _params.origin;
    return normal.unitVector();
}

double Sphere::localHit(const Ray &localRay) {
    const Vec3 oc = localRay.getOrigin() - _params.origin;
    const double a = localRay.getDirection().dot(localRay.getDirection());
    const double b = 2.0 * localRay.getDirection().dot(oc);
    const double c = oc.dot(oc) - *_params.radius * *_params.radius;
    const double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0;
    return (-b - std::sqrt(discriminant)) / (2.0 * a);
}
