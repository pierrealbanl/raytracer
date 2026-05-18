cmake_minimum_required(VERSION 3.16)
project(raytracer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED IMPORTED_TARGET libconfig++)

add_executable(raytracer
    src/main.cpp
    src/Core.cpp
    src/Parser.cpp
    src/factory/Factory.cpp
    src/camera/Camera.cpp
    src/primitives/APrimitive.cpp
    src/primitives/PrimitiveManager.cpp
    src/primitives/sphere/Sphere.cpp
    src/primitives/plane/Plane.cpp
    src/light/LightManager.cpp
    src/light/ambient/AmbientLight.cpp
    src/light/directional/DirectionalLight.cpp
    src/material/FlatColor.cpp
    lib/math/Vec3.cpp
    lib/math/Point3.cpp
    lib/math/Ray.cpp
    lib/math/Matrix4.cpp
    lib/color/Color.cpp
)

target_include_directories(raytracer PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(raytracer PRIVATE PkgConfig::LIBCONFIG)
