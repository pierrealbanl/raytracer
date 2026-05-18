#ifndef FLAT_COLOR_HPP
#define FLAT_COLOR_HPP

#include "IMaterial.hpp"

class FlatColor : public IMaterial {
public:
    FlatColor(const Vec3& color);
    ~FlatColor() override = default;

    Vec3 getColor() const override;
private:
    Vec3 _color;
};

#endif
