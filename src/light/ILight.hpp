#ifndef ILIGHT_HPP
#define ILIGHT_HPP

#include "../../lib/math/Vec3.hpp"

#include <optional>

struct LightParams {
    double intensity; // Light strength
    std::optional<Vec3> direction; // Vector indicating where the light points
};

class ILight {
public:
    virtual ~ILight() = default;
    virtual Vec3 getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
        std::optional<Vec3> lightDir) const = 0;
    virtual std::optional<Vec3> getLightDirection(const Vec3 &camHitPoint) const = 0;
};

#endif
