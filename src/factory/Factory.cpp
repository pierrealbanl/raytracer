#include "Factory.hpp"

Factory::Factory() {
    _mapObject["sphere"] = [](PrimitiveParams params) { return std::make_unique<Sphere>(std::move(params)); };
    _mapObject["plane"] = [](PrimitiveParams params) { return std::make_unique<Plane>(std::move(params)); };

    _mapLight["ambient"] = [](LightParams params) { return std::make_unique<AmbientLight>(params); };
    _mapLight["directional"] = [](LightParams params) { return std::make_unique<DirectionalLight>(params); };
}

std::unique_ptr<IPrimitive> Factory::createPrimitive(const std::string &key, PrimitiveParams params) {
    const auto it = _mapObject.find(key);

    if (it == _mapObject.end())
        return nullptr;
    return it->second(std::move(params));
}

std::unique_ptr<ILight> Factory::createLight(const std::string &key, const LightParams &params) {
    const auto it = _mapLight.find(key);

    if (it == _mapLight.end())
        return nullptr;
    return it->second(params);
}
