#include "application.h"
#include "object.h"
#include "off_loader.h"

#include <utility>

const double kCubeDistanceFromOrigin = 17;

int main() {
    ScratchRenderer::Application app;
    ScratchRenderer::Loader loader;
    for (size_t i = 0; i < 4; ++i) {
        auto cube = loader.Load("cube.off");
        if (i % 2 == 0) {
            cube.rotate(ScratchRenderer::Axe::Z, std::numbers::pi / 4);
        }
        cube.translate(ScratchRenderer::Axe::X, (i % 2 == 0) * kCubeDistanceFromOrigin * ((i > 1) ? -1 : 1));
        cube.translate(ScratchRenderer::Axe::Z, (i % 2 == 1) * kCubeDistanceFromOrigin * ((i > 1) ? -1 : 1));
        app.addObject(std::move(cube));
    }
    app.run();
    return 0;
}
