#include "application.h"
#include "except.h"
#include "object.h"
#include "off_loader.h"
#include "world_init.h"

int main() {
    try {
        ScratchRenderer::Application app(ScratchRenderer::modelInit("apple.off"));
        app.run();
    } catch (...) {
        Except::react();
    }
    return 0;
}
