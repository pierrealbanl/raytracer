#include "Color.hpp"

#include <algorithm>

void writeColor(std::ostream &out, const Vec3 &v3) {
    const int rbyte = std::clamp(static_cast<int>(MAX_RGB * v3.t[0]), 0, MAX_RGB);
    const int gbyte = std::clamp(static_cast<int>(MAX_RGB * v3.t[1]), 0, MAX_RGB);
    const int bbyte = std::clamp(static_cast<int>(MAX_RGB * v3.t[2]), 0, MAX_RGB);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
