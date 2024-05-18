#ifndef APPLICATION_H
#define APPLICATION_H

#include "camera.h"
#include "object.h"
#include "renderer.h"
#include "world.h"

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

namespace ScratchRenderer {
class Application {
public:
    using Initializer = std::function<void(World &)>;
    Application(Initializer init);

    void run();

private:
    struct Handler {
        sf::Keyboard::Key key;
        std::function<void()> body;
    };

    void createKeyboardHandlers();
    bool hasWindowClosed();
    void handleKeyboardInput();
    void drawFrame(const Renderer::Image &image);

    Renderer renderer_;
    World world_;
    Camera camera_;
    sf::RenderWindow window_;
    std::vector<Handler> keyboardHandlers_;
};
} // namespace ScratchRenderer

#endif
