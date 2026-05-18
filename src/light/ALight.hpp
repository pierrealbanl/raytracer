#ifndef ALIGHT_HPP
#define ALIGHT_HPP

#include "ILight.hpp"

class ALight : public ILight {
public:
    ALight() = default;
    ~ALight() override = default;

    Vec3 getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
        std::optional<Vec3> lightDir) const override;
    std::optional<Vec3> getLightDirection(const Vec3 &camHitPoint) const override;
};

#endif
