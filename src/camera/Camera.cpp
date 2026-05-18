#include "Camera.hpp"

#include <numbers>

Camera::Camera(const double width, const double height, const Point3 &position, const double fov)
: _imageX(width), _imageY(height), _fov_rad(fov * std::numbers::pi / 180.0), _cameraPos(position) {
    _focalLength = 1;
    _viewportY = 2.0 * _focalLength * std::tan(_fov_rad / 2.0);
    _viewportX = _viewportY * _imageX / _imageY;

    _u = Vec3(_viewportX, 0, 0);
    _v = Vec3(0, 0, -_viewportY);
    _deltaU = _u / _imageX;
    _deltaV = _v / _imageY;
    _viewportUpperLeft = _cameraPos + Vec3(0.0, _focalLength, 0.0) - _u / 2 - _v / 2;
    _pixCenter = _viewportUpperLeft + (_deltaU + _deltaV) * 0.5;
}

double Camera::getImageX() const {
    return _imageX;
}

double Camera::getImageY() const {
    return _imageY;
}

Ray Camera::createRay(const int col, const int row) const {
    const Point3 pixCenter = _pixCenter + (_deltaU * col) + (_deltaV * row);
    const Vec3 rayDirection = pixCenter - _cameraPos;

    return Ray(_cameraPos, rayDirection);
}
