#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../../lib/math/Point3.hpp"
#include "../../lib/math/Vec3.hpp"
#include "../../lib/math/Ray.hpp"

class Camera {
public:
    Camera(double width, double height, const Point3& position, double fov);
    ~Camera() = default;

    double getImageX() const;
    double getImageY() const;

    // Creates a ray starting from the camera and passing through the center of pixel (col, row)
    Ray createRay(int col, int row) const;
private:
    // Defines the image width in pixels.
    double _imageX;

    // Computes the image height based on the aspect ratio.
    double _imageY;

    /**
     * Distance between the camera and the viewport (see definition below)
     *
     * Camera            Window (viewport)      3D Scene
     * •───────────────────┼────────────────────•  sphere
     * │  ◀ focalLength ▶  │
     *                     │  each cell
     *                     │  = one pixel
     *                     │
     *                ┌──┬──┬──┐
     *                ├──┼──┼──┤
     *                ├──┼──┼──┤
     *                └──┴──┴──┘
     */
    double _focalLength;

    /**
     * Camera field of view in radians (converted from degrees).
     * The larger the FOV, the wider the camera sees.
     *
     * The formula is: 72° * π / 180 = 1.257 rad
     */
    double _fov_rad;

    /**
     * A viewport is a virtual rectangle placed in front of the camera,
     * onto which image pixels are projected to generate rays.
     * It is the 3D window through which the camera looks at the scene.
     *
     * Camera            Window (viewport)      3D Scene
     * •───────────────────┼────────────────────•  sphere
     * │                   │
     *                     │  each cell
     *                     │  = one pixel
     *                     │
     *                ┌──┬──┬──┐  ▲
     *                ├──┼──┼──┤  │ viewportY
     *                ├──┼──┼──┤  │
     *                └──┴──┴──┘  ▼
     *               ◀ viewportX ▶
     */
    double _viewportY;
    double _viewportX;

    /**
     * Camera position in the 3D scene.
     * Default at the origin (0, 0, 0).
     *
     *    Y
     *    │
     *    │
     *    • (0,0,0) = camera
     *    └────────▶ X
     *   /
     *  Z
     */
    Point3 _cameraPos;

    /**
     * _u and _v represent the total width and height of the viewport in 3D units.
     *
     *                          _u = total width
     *                              (e.g. 2.5)
     *                         ◀───────────────────────▶
     *                      ▲  ┌──┬──┬──┬──┬──┬──┬──┬──┐  ▲
     *                      │  ├──┼──┼──┼──┼──┼──┼──┼──┤  │ _deltaV = height of one pixel in 3D units
     *                      │  ├──┼──┼──┼──┼──┼──┼──┼──┤  ▼
     * _v = total height    │  ├──┼──┼──┼──┼──┼──┼──┼──┤
     *    (e.g. 1.5)        │  ├──┼──┼──┼──┼──┼──┼──┼──┤
     *                      ▼  └──┴──┴──┴──┴──┴──┴──┴──┘
     *                         ◀──▶ _deltaU = width of one pixel in 3D units
     */
    Vec3 _u;
    Vec3 _v;
    Vec3 _deltaU;
    Vec3 _deltaV;

    // Computes the upper-left corner of the viewport.
    Point3 _viewportUpperLeft;

    /**
     * Computes the center of the first pixel (top-left).
     *
     *    ┌─────────────┐
     *    │             │  _deltaV = height of one pixel in 3D units
     *    │      •      │  ← _pixCenter (pixel center)
     *    │             │
     *    └─────────────┘
     *    ◀─────────────▶ _deltaU = width of one pixel in 3D units
     */
    Point3 _pixCenter;
};

#endif
