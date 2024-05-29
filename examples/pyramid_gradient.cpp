#include "application.h"
#include "except.h"
#include "object.h"
#include "primitives.h"
#include "world_init.h"

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

int main() {
    try {
        ScratchRenderer::Application app(ScratchRenderer::pyramidGradientInit);
        app.run();
    } catch (...) {
        Except::react();
    }
    return 0;
}
