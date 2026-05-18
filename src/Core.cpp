#include "Core.hpp"

Core::Core()
    : _primitiveManager(std::make_unique<PrimitiveManager>()),
      _lightManager(std::make_unique<LightManager>()),
      _factory(std::make_unique<Factory>()),
      _camera(nullptr) {}

PrimitiveManager *Core::getPrimitiveManager() const {
    return _primitiveManager.get();
}

LightManager *Core::getLightManager() const {
    return _lightManager.get();
}

Factory *Core::getFactory() const {
    return _factory.get();
}

Camera *Core::getCamera() const {
    return _camera.get();
}

void Core::setCamera(std::unique_ptr<Camera> camera) {
    _camera = std::move(camera);
}
