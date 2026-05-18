#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include "../../lib/math/Vec3.hpp"
#include "../../lib/math/Ray.hpp"
#include "../material/IMaterial.hpp"
#include "../../lib/math/Matrix4.hpp"

#include <optional>
#include <memory>

struct PrimitiveParams {
    Point3 origin; // An arbitrary point in space
    std::unique_ptr<IMaterial> colorRGB;
    std::optional<double> radius;
    std::optional<Vec3> normal;
};

class IPrimitive {
public:
    virtual ~IPrimitive() = default;
    virtual void setTransform(const Matrix4 &mat) = 0;
    virtual Vec3 getColor() const = 0;
    virtual double hit(const Ray &r) = 0;
    virtual Vec3 getNormalAt(const Ray &ray, double t) = 0;
    virtual double localHit(const Ray &localRay) = 0;
    virtual Vec3 localNormalAt(const Ray &localRay, double t) = 0;
};

#endif
