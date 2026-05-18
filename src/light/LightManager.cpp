#include "LightManager.hpp"

void LightManager::insertLight(const std::string &name, std::unique_ptr<ILight> light) {
    _lights[name] = std::move(light);
}

Vec3 LightManager::applyLighting(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
    PrimitiveManager &objectManager) const {
    Vec3 result(0.0, 0.0, 0.0);

    for (const auto &[key, value] : _lights) {
        std::optional<Vec3> lightDir = value->getLightDirection(camHitPoint);

        if (lightDir.has_value()) {
            Point3 hitPoint3(camHitPoint.t[0], camHitPoint.t[1], camHitPoint.t[2]);
            Ray shadowRay(hitPoint3, *lightDir);
            if (objectManager.findClosestHit(shadowRay) > 0.0)
                continue;
        }
        result = result + value->getIntensity(camHitPoint, normal, colorRGB, lightDir);
    }
    return result;
}
