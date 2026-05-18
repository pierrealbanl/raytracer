#include "Parser.hpp"

#include <iostream>
#include <memory>
#include <string>

static std::unique_ptr<IMaterial> parseMaterial(const libconfig::Setting &s) {
    if (s.exists("material")) {
        const libconfig::Setting &material = s["material"];
        if (material.exists("flatColor")) {
            const libconfig::Setting &flatColor = material["flatColor"];
            int cr = 0, cg = 0, cb = 0;
            flatColor.lookupValue("r", cr);
            flatColor.lookupValue("g", cg);
            flatColor.lookupValue("b", cb);
            return std::make_unique<FlatColor>(Vec3(cr / 255.0, cg / 255.0, cb / 255.0));
        }
    }
    return std::make_unique<FlatColor>(Vec3(0, 0, 0));
}

static Vec3 parsePosition(const libconfig::Setting &s) {
    int x = 0, y = 0, z = 0;
    s.lookupValue("x", x);
    s.lookupValue("y", y);
    s.lookupValue("z", z);
    return {static_cast<double>(x), static_cast<double>(y), static_cast<double>(z)};
}

static int parseCamera(const libconfig::Setting &root, Core *core) {
    if (!root.exists("camera")) {
        std::cerr << "Error: The 'camera' block is missing." << std::endl;
        return 84;
    }

    const libconfig::Setting &camera = root["camera"];
    int width = 0, height = 0;
    double fov = 0.0;
    camera["resolution"].lookupValue("width", width);
    camera["resolution"].lookupValue("height", height);
    camera.lookupValue("fieldOfView", fov);
    Vec3 pos = parsePosition(camera["position"]);
    core->setCamera(std::make_unique<Camera>(width, height, Point3(pos[0], pos[1], pos[2]), fov));
    return 0;
}

static void parsePrimitiveList(
    const libconfig::Setting &primitives,
    const std::string &type,
    const Core *core,
    const std::function<PrimitiveParams(const libconfig::Setting &, std::unique_ptr<IMaterial>)> &buildParams) {
    if (!primitives.exists(type))
        return;

    const libconfig::Setting &list = primitives[type];
    for (int i = 0; i < list.getLength(); ++i) {
        const libconfig::Setting &s = list[i];
        Vec3 pos = parsePosition(s);
        std::unique_ptr<IMaterial> material = parseMaterial(s);
        PrimitiveParams params = buildParams(s, std::move(material));

        std::unique_ptr<IPrimitive> obj = core->getFactory()->createPrimitive(type.substr(0, type.size() - 1), std::move(params));
        if (!obj) {
            std::cerr << "Error: Failed to create " << type << "_" << i << std::endl;
            continue;
        }
        obj->setTransform(Matrix4::translation(pos[0], pos[1], pos[2]));
        core->getPrimitiveManager()->insertObject(type + "_" + std::to_string(i), std::move(obj));
    }
}

static int parsePrimitives(const libconfig::Setting &root, const Core *core) {
    if (!root.exists("primitives")) {
        std::cerr << "Error: The 'primitives' block is missing." << std::endl;
        return 84;
    }

    const libconfig::Setting &primitives = root["primitives"];
    parsePrimitiveList(primitives, "spheres", core, [](const libconfig::Setting &s, std::unique_ptr<IMaterial> mat) {
        int r = 0;
        s.lookupValue("r", r);
        return PrimitiveParams{Point3(), std::move(mat), r, std::nullopt};
    });
    parsePrimitiveList(primitives, "planes", core, [](const libconfig::Setting &s, std::unique_ptr<IMaterial> mat) {
        int x = 0, y = 0, z = 0;
        s.lookupValue("x", x);
        s.lookupValue("y", y);
        s.lookupValue("z", z);
        Vec3 normal(0, 0, 0);
        if (x != 0)      normal[0] = 1.0;
        else if (y != 0) normal[1] = 1.0;
        else if (z != 0) normal[2] = 1.0;
        return PrimitiveParams{Point3(), std::move(mat), std::nullopt, normal};
    });
    return 0;
}

static void parseLightList(
    const libconfig::Setting &lights,
    const std::string &configKey,
    const std::string &factoryKey,
    const Core *core,
    const std::function<LightParams(const libconfig::Setting &)> &buildParams) {
    if (!lights.exists(configKey))
        return;

    const libconfig::Setting &list = lights[configKey];
    for (int i = 0; i < list.getLength(); ++i) {
        LightParams params = buildParams(list[i]);
        std::unique_ptr<ILight> light = core->getFactory()->createLight(factoryKey, params);
        if (light)
            core->getLightManager()->insertLight(factoryKey + "_" + std::to_string(i), std::move(light));
    }
}

static int parseLights(const libconfig::Setting &root, const Core *core) {
    if (!root.exists("lights")) {
        std::cerr << "Error: The 'lights' block is missing." << std::endl;
        return 84;
    }

    const libconfig::Setting &lights = root["lights"];
    parseLightList(lights, "ambient", "ambient", core, [](const libconfig::Setting &s) {
        double intensity = 0.0;
        s.lookupValue("intensity", intensity);
        return LightParams{intensity, std::nullopt};
    });
    parseLightList(lights, "directionnal", "directional", core, [](const libconfig::Setting &s) {
        double intensity = 0.0;
        s.lookupValue("intensity", intensity);
        Vec3 dir = parsePosition(s);
        return LightParams{intensity, dir};
    });
    return 0;
}

int Parser::parsing(int argc, char **argv, Core *core) {
    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << " <SCENE_FILE.conf>" << std::endl;
        return 84;
    }
    try {
        libconfig::Config cfg;
        cfg.readFile(argv[1]);
        const libconfig::Setting &root = cfg.getRoot();

        if (parseCamera(root, core) == 84)
            return 84;
        if (parsePrimitives(root, core) == 84)
            return 84;
        if (parseLights(root, core) == 84)
            return 84;
    } catch (const libconfig::FileIOException &) {
        std::cerr << "Error: File not found or read error ('" << argv[1] << "')." << std::endl;
        return 84;
    } catch (const libconfig::ParseException &pex) {
        std::cerr << "Syntax error at line " << pex.getLine() << ": " << pex.getError() << std::endl;
        return 84;
    } catch (const libconfig::SettingException &ex) {
        std::cerr << "Error: Invalid configuration (" << ex.getPath() << ")." << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error during loading." << std::endl;
        return 84;
    }
    return 0;
}
