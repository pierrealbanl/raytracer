#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include "../ILight.hpp"

class AmbientLight : public ILight {
public:
    AmbientLight(const LightParams &params);
    ~AmbientLight() override = default;

    Vec3 getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
        std::optional<Vec3> lightDir) const override;
    std::optional<Vec3> getLightDirection(const Vec3 &camHitPoint) const override;
private:
    LightParams _params;
};

#endif
