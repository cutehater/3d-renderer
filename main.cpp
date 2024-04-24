#include "src/application.h"
#include "src/global_usings.h"
#include "src/object.h"
#include "src/off_loader.h"

#include <utility>

int main() {
    ScratchRenderer::Application app;
    ScratchRenderer::Loader loader;
    for (size_t i = 0; i < 4; ++i) {
        auto cube = loader.Load("cube.off");
        if (i % 2 == 0) {
            cube.rotate(ScratchRenderer::Axe::Z, std::numbers::pi / 4);
        }
        cube.translate(ScratchRenderer::Axe::X, (i % 2 == 0) * 17 * ((i > 1) ? -1 : 1));
        cube.translate(ScratchRenderer::Axe::Y, (i % 2 == 1) * 17 * ((i > 1) ? -1 : 1));
        app.addObject(std::move(cube));
    }
    app.run();
    return 0;
}
