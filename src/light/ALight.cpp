#include "ALight.hpp"

std::optional<Vec3> ALight::getLightDirection(const Vec3 &camHitPoint) const {
    (void)camHitPoint;
    return std::nullopt;
}

Vec3 ALight::getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
    const std::optional<Vec3> lightDir) const {
    (void)camHitPoint;
    (void)normal;
    (void)colorRGB;
    (void)lightDir;
    return {0.0, 0.0, 0.0};
}
