#include "AmbientLight.hpp"

AmbientLight::AmbientLight(const LightParams &params) : _params(params) {}

Vec3 AmbientLight::getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
    const std::optional<Vec3> lightDir) const {
    (void)camHitPoint;
    (void)normal;
    (void)lightDir;
    return colorRGB * _params.intensity;
}
