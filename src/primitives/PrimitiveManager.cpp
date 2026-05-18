#include "PrimitiveManager.hpp"

void PrimitiveManager::insertObject(const std::string &name, std::unique_ptr<IPrimitive> object) {
    _objects[name] = std::move(object);
}

double PrimitiveManager::findClosestHit(const Ray& r) {
    double hit = -1;
    _hitObject = nullptr;

    for (const auto& [key, value] : _objects) {
        const double t = value->hit(r);
        if (t > 0.001 && (hit < 0 || t < hit)) {
            hit = t;
            _hitObject = value.get();
        }
    }
    return hit;
}

IPrimitive *PrimitiveManager::getHitObject() const {
    return _hitObject;
}

