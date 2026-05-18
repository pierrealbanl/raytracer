#include "Core.hpp"
#include "Parser.hpp"
#include "../lib/color/Color.hpp"

#include <iostream>
#include <memory>

Vec3 calculatePixelColor(const Ray &r, PrimitiveManager &objectManager, const LightManager &lightManager) {
    const double hitDistance = objectManager.findClosestHit(r);

    if (hitDistance > 0.0) {
        if (objectManager.getHitObject()) {
            const Point3 hitPoint3 = r.at(hitDistance);
            const Vec3 camHitPoint(hitPoint3.x, hitPoint3.y, hitPoint3.z);
            const Vec3 normal = objectManager.getHitObject()->getNormalAt(r, hitDistance);
            const Vec3 colorRGB = objectManager.getHitObject()->getColor();
            return lightManager.applyLighting(camHitPoint, normal, colorRGB, objectManager);
        }
    }
    return {0.0, 0.0, 0.0};
}

/**
 * The .ppm format is structured in three distinct parts:
 *
 * - The first line indicates the file encoding type, usually P3,
 * which simply means the PPM image is stored in plain text, pixel by pixel,
 * with RGB values written as text.
 *
 * - The second line specifies the image dimensions, namely its width
 * and height.
 *
 * - The third line contains the maximum value of the color components,
 * set here to 255.
 *
 * Example of a .ppm file:
 * P3
 * 256 256
 * 255
 * <RGB> <RGB> <RGB> …
 */
int main(const int argc, char *argv[]) {
    const std::unique_ptr<Core> core = std::make_unique<Core>();

    if (Parser::parsing(argc, argv, core.get()) == 84)
        return 84;
    const Camera *camera = core->getCamera();

    std::cout << "P3\n" << camera->getImageX() << ' ' << camera->getImageY() << "\n255\n";
    for (int row = 0; row < camera->getImageY(); row++) {
        for (int col = 0; col < camera->getImageX(); col++) {
            Ray ray = camera->createRay(col, row);
            Vec3 pixelColor = calculatePixelColor(ray, *core->getPrimitiveManager(), *core->getLightManager());
            writeColor(std::cout, pixelColor);
        }
    }
}