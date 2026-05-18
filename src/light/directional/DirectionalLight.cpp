#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(const LightParams &params) : _params(params) {}

std::optional<Vec3> DirectionalLight::getLightDirection(const Vec3 &camHitPoint) const {
    (void)camHitPoint;
    return (-*_params.direction).unitVector();
}

Vec3 DirectionalLight::getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
    const std::optional<Vec3> lightDir) const {
    (void)camHitPoint;
    const double cosTheta = std::max(0.0, normal.dot(*lightDir));
    return colorRGB * cosTheta * _params.intensity;
}
