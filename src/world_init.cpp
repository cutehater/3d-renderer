#include "world_init.h"

#include "global_usings.h"
#include "object.h"
#include "off_loader.h"
#include "primitives.h"

namespace ScratchRenderer {
void cubesInit(World &world) {
    constexpr double kCubeDistanceFromOrigin = 17;

    Loader loader;
    for (size_t i = 0; i < 4; ++i) {
        auto cube = loader.Load("cube.off");
        if (i % 2 == 0) {
            cube.rotate(Axis::Z, std::numbers::pi / 4);
        }
        cube.translate(Axis::X, (i % 2 == 0) * kCubeDistanceFromOrigin * ((i > 1) ? -1 : 1));
        cube.translate(Axis::Z, (i % 2 == 1) * kCubeDistanceFromOrigin * ((i > 1) ? -1 : 1));
        world.addObject(std::move(cube));
    }
}

void pyramidGradientInit(World &world) {
    auto makeGradient = [](const Vector4 &A, const Vector4 &B, const Vector4 &C) {
        return Primitives::Triangle{
            Primitives::Vertex{A, Color::Blue},
            Primitives::Vertex{B, Color::Green},
            Primitives::Vertex{C, Color::Red},
        };
    };

    auto makeUsual = [](const Vector4 &A, const Vector4 &B, const Vector4 &C, const Color &color) {
        return Primitives::Triangle{
            Primitives::Vertex{A, color},
            Primitives::Vertex{B, color},
            Primitives::Vertex{C, color},
        };
    };

    Vector4 O(0, 1, 5);
    Vector4 A(-1, -1, 4);
    Vector4 B(1, -1, 4);
    Vector4 C(1, -1, 6);
    Vector4 D(-1, -1, 6);
    Object pyramid({makeUsual(A, B, D, Color::Cyan), makeUsual(D, B, C, Color::Cyan), makeGradient(O, A, B),
                    makeGradient(O, C, B), makeGradient(O, C, D), makeGradient(O, A, D)});

    world.addObject(std::move(pyramid));
}

Application::Initializer modelInit(const std::string &modelName) {
    return [&modelName](World &world) {
        Loader loader;
        world.addObject(loader.Load(modelName));
    };
}

} // namespace ScratchRenderer
