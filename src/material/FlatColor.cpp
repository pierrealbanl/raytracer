#include "FlatColor.hpp"

FlatColor::FlatColor(const Vec3& color) : _color(color) {}

Vec3 FlatColor::getColor() const {
    return _color;
}
