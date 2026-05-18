#ifndef IMATERIAL_HPP
#define IMATERIAL_HPP

#include "../../lib/math/Vec3.hpp"

class IMaterial {
public:
    virtual ~IMaterial() = default;
    virtual Vec3 getColor() const = 0;
};

#endif
