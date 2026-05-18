#include "APrimitive.hpp"

APrimitive::APrimitive()
    : _m(Matrix4()), _invM(Matrix4()) {}

void APrimitive::setTransform(const Matrix4 &m) {
    _m = m;
    _invM = m.inverse();
}

Vec3 APrimitive::getColor() const {
    return {0.0, 0.0, 0.0};
}

double APrimitive::hit(const Ray &r) {
    const Ray localRay(
        _invM.applyPoint(r.getOrigin()),
        _invM.applyVec(r.getDirection())
    );
    return localHit(localRay);
}

Vec3 APrimitive::getNormalAt(const Ray &r, const double t) {
    const Ray localRay(
        _invM.applyPoint(r.getOrigin()),
        _invM.applyVec(r.getDirection())
    );
    const Vec3 localNormal = localNormalAt(localRay, t);
    const Vec3 worldNormal(
        _invM.m[0][0] * localNormal.t[0] + _invM.m[1][0] * localNormal.t[1] + _invM.m[2][0] * localNormal.t[2],
        _invM.m[0][1] * localNormal.t[0] + _invM.m[1][1] * localNormal.t[1] + _invM.m[2][1] * localNormal.t[2],
        _invM.m[0][2] * localNormal.t[0] + _invM.m[1][2] * localNormal.t[1] + _invM.m[2][2] * localNormal.t[2]
    );
    return worldNormal.unitVector();
}
