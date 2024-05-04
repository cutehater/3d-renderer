#include "application.h"
#include "off_loader.h"

int main() {
    ScratchRenderer::Application app;
    ScratchRenderer::Loader loader;
    app.addObject(loader.Load("paste_your_model_name.off"));
    app.run();
    return 0;
}
