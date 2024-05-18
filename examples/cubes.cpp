#include "application.h"
#include "except.h"
#include "object.h"
#include "off_loader.h"
#include "world_init.h"

#include <utility>

int main() {
    try {
        ScratchRenderer::Application app(ScratchRenderer::cubesInit);
        app.run();
    } catch (...) {
        Except::react();
    }
    return 0;
}
