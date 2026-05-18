# Designed and implemented a Raytracer in C++

This project is built on the fundamentals of a Raytracer, a 3D rendering engine.
Its goal is to simulate the physical behavior of light by casting rays from a virtual camera,
through each pixel of an image, in order to determine the final color of each point in the scene.
The program constructs a scene from a configuration file describing the objects, lights, and camera,
then generates an image in PPM format by computing ray/primitive intersections and applying lighting models.

This project illustrates the basics of linear algebra (vectors, dot product, transformation matrices) as well as
the principles of geometric optics. These concepts are essential for correctly implementing intersections,
normals, and shadows.

> ⚠ This project is intended to evolve over time. Certain concepts or features have not yet been 
> covered or implemented. Nevertheless, this provides a solid foundation for building a raytracer.

## Architecture

A clear and extensible architecture is essential to be able to add new types of primitives or lights
without modifying the core of the system.

This architecture is organized around several main components:

```
Raytracer/
├── config/
│   └── *.conf                            # Scene configurations (camera, primitives, lights)
├── lib/
│   ├── color/
│   │   └── Color.hpp/cpp                 # Color utilities (PPM writing)
│   └── math/
│       ├── Vec3.hpp/cpp                  # 3D Vector
│       ├── Point3.hpp/cpp                # 3D Point
│       ├── Ray.hpp/cpp                   # Ray (origin + direction)
│       └── Matrix4.hpp/cpp               # 4×4 Matrix (transformations)
├── ppm/
│   └── *.ppm                             # Pre-rendered scene outputs
├── src/
│   ├── main.cpp                          # Entry point, scene construction, render loop
│   ├── Core.hpp/cpp                      # Core functionalities
│   ├── Parser.hpp/cpp                    # .conf file reader
│   ├── camera/
│   │   └── Camera.hpp/cpp                # Per-pixel ray generation
│   ├── factory/
│   │   └── Factory.hpp/cpp               # Primitive and light creation
│   ├── light/
│   │   ├── ILight.hpp                    # Light interface
│   │   ├── LightManager.hpp/cpp          # Lighting and shadows
│   │   ├── ambient/
│   │   │   └── AmbientLight.hpp/cpp      # Ambient light
│   │   └── directional/
│   │       └── DirectionalLight.hpp/cpp  # Directional light
│   ├── material/
│   │   ├── IMaterial.hpp                 # Material interface
│   │   └── FlatColor.hpp/cpp             # Flat color material
│   └── primitives/
│       ├── IPrimitive.hpp                # Primitive interface
│       ├── APrimitive.hpp/cpp            # Abstract class (transformations)
│       ├── PrimitiveManager.hpp/cpp      # Hit management
│       ├── sphere/
│       │   └── Sphere.hpp/cpp            # Sphere
│       └── plane/
│           └── Plane.hpp/cpp             # Infinite plane
```

## Usage

### Build

```bash
cmake -B build
cmake --build build
```

### Run

```bash
./build/raytracer <scene_config_file>
```

The program outputs the rendered image in PPM format to stdout. To save it as a file:

```bash
./build/raytracer config/scene.conf > output.ppm
```

### Scene configuration

Scene files are located in the `config/` directory. Several example scenes are provided:

- `billiards.conf` — Billiard balls
- `snowman.conf` — Snowman
- `solar_system.conf` — Solar system
- `sunset.conf` — Sunset
