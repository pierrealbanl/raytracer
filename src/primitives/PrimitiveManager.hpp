#ifndef OBJECT_MANAGER_HPP
#define OBJECT_MANAGER_HPP

#include "IPrimitive.hpp"

#include <map>

class PrimitiveManager {
public:
    PrimitiveManager() = default;
    ~PrimitiveManager() = default;

    void insertObject(const std::string &name, std::unique_ptr<IPrimitive> object);

    /**
     * Iterates through all objects in the scene and returns the distance t between the ray's origin and
     * the closest intersection point (the first object hit), or -1 if no intersection.
     * Used for camera rays (which object to display) and shadow rays (which object blocks the light).
     *
     * t > 0.001 avoids self-intersection: an object cannot cast a shadow on itself.
     */
    double findClosestHit(const Ray &r);

    IPrimitive *getHitObject() const;
private:
    std::map<std::string, std::unique_ptr<IPrimitive>> _objects;
    IPrimitive *_hitObject = nullptr; // Store the hit object
};

#endif