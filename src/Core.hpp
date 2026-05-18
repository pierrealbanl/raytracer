#ifndef CORE_HPP
#define CORE_HPP

#include "camera/Camera.hpp"
#include "factory/Factory.hpp"
#include "primitives/PrimitiveManager.hpp"
#include "light/LightManager.hpp"
#include "material/FlatColor.hpp"

#include <memory>

class Core {
public:
    Core();
    ~Core() = default;

    PrimitiveManager *getPrimitiveManager() const;
    LightManager *getLightManager() const;
    Factory *getFactory() const;
    Camera *getCamera() const;

    void setCamera(std::unique_ptr<Camera> camera);
private:
    std::unique_ptr<PrimitiveManager> _primitiveManager;
    std::unique_ptr<LightManager> _lightManager;
    std::unique_ptr<Factory> _factory;
    std::unique_ptr<Camera> _camera;
};

#endif
