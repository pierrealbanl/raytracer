#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "../primitives/IPrimitive.hpp"
#include "../primitives/sphere/Sphere.hpp"
#include "../primitives/plane/Plane.hpp"
#include "../light/ILight.hpp"
#include "../light/ambient/AmbientLight.hpp"
#include "../light/directional/DirectionalLight.hpp"

#include <map>
#include <functional>

class Factory {
public:
    Factory();
    std::unique_ptr<IPrimitive> createPrimitive(const std::string &key, PrimitiveParams params);
    std::unique_ptr<ILight> createLight(const std::string &key, const LightParams &params);
private:
    std::map<std::string, std::function<std::unique_ptr<IPrimitive>(PrimitiveParams)>> _mapObject;
    std::map<std::string, std::function<std::unique_ptr<ILight>(LightParams)>> _mapLight;
};

#endif
