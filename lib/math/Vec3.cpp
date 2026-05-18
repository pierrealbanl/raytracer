#include "Vec3.hpp"

Vec3::Vec3() : t{0, 0, 0} {}

Vec3::Vec3(const double x, const double y, const double z) : t{x, y, z} {}

Vec3 Vec3::operator-() const {
    return {-t[0], -t[1], -t[2]};
}

double Vec3::operator[](const int i) const {
    assert(i >= 0 && i < 3);
    return t[i];
}

double &Vec3::operator[](const int i) {
    assert(i >= 0 && i < 3);
    return t[i];
}

Vec3 &Vec3::operator+=(const Vec3& u) {
    t[0] += u.t[0];
    t[1] += u.t[1];
    t[2] += u.t[2];
    return *this;
}

Vec3 &Vec3::operator*=(const double n) {
    t[0] *= n;
    t[1] *= n;
    t[2] *= n;
    return *this;
}

Vec3& Vec3::operator/=(const double n) {
    return *this *= 1/n;
}

double Vec3::vecLengthSquared() const {
    return t[0] * t[0] + t[1] * t[1] + t[2] * t[2];
}

double Vec3::vecLength() const {
    return std::sqrt(vecLengthSquared());
}

double Vec3::dot(const Vec3 &u) const {
    return u.t[0] * t[0] + u.t[1] * t[1] + u.t[2] * t[2];
}

Vec3 Vec3::cross(const Vec3 &u) const {
    return {
        u.t[1] * t[2] - u.t[2] * t[1],
        u.t[2] * t[0] - u.t[0] * t[2],
        u.t[0] * t[1] - u.t[1] * t[0]
        };
}

Vec3 Vec3::unitVector() const {
    const double len = this->vecLength();
    if (len == 0.0)
        return {0, 0, 0};
    return *this / len;
}

std::ostream& Vec3::operator<<(std::ostream &out) const {
    return out << t[0] << ' ' << t[1] << ' ' << t[2];
}

Vec3 Vec3::operator+(const Vec3 &u) const {
    return {u.t[0] + t[0], u.t[1] + t[1], u.t[2] + t[2]};
}

Vec3 Vec3::operator-(const Vec3 &u) const {
    return {t[0] - u.t[0], t[1] - u.t[1], t[2] - u.t[2]};
}

Vec3 Vec3::operator-(const double n) const {
    return {t[0] - n, t[1] - n, t[2] - n};
}

Vec3 Vec3::operator*(const Vec3 &u) const {
    return {u.t[0] * t[0], u.t[1] * t[1], u.t[2] * t[2]};
}

Vec3 Vec3::operator*(const double n) const {
    return {t[0] * n, t[1] * n, t[2] * n};
}

Vec3 Vec3::operator/(const double n) const {
    return *this * (1 / n);
}
