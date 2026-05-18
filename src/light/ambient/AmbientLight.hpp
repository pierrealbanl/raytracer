#ifndef AMBIENT_LIGHT_HPP
#define AMBIENT_LIGHT_HPP

#include "../ALight.hpp"

class AmbientLight : public ALight {
public:
    AmbientLight(const LightParams &params);
    ~AmbientLight() override = default;

    Vec3 getIntensity(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
        std::optional<Vec3> lightDir) const override;
private:
    LightParams _params;
};

#endif
