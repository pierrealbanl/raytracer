#ifndef LIGHT_MANAGER_HPP
#define LIGHT_MANAGER_HPP

#include "ILight.hpp"
#include "../primitives/PrimitiveManager.hpp"

#include <map>
#include <memory>

class LightManager {
public:
    LightManager() = default;
    ~LightManager() = default;

    void insertLight(const std::string &name, std::unique_ptr<ILight> light);

    /**
     * Iterates through all lights in the scene and applies their effects: ambient light,
     * directional light, and shadow computation.
     * For each directional light, a shadow ray is cast from the hit point toward the light.
     * If the shadow ray hits an object, we skip to the next light without adding its intensity,
     * otherwise we add the directional light's intensity to the final result.
     *
     * The shadow ray goes from camHitPoint toward the light, and if an object lies on this path
     * it is blocked:
     *
     *     Light
     *        ▲
     *        │
     *        │ shadow ray blocked
     *        │
     *   ─────●───── blocking object ──▶ shadow
     *        │
     *        │ shadow ray
     *        │
     *   ─────●───── camHitPoint
     */
    Vec3 applyLighting(const Vec3 &camHitPoint, const Vec3 &normal, const Vec3 &colorRGB,
        PrimitiveManager &objectManager) const;
private:
    std::map<std::string, std::unique_ptr<ILight>> _lights;
};

#endif
