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
    Application();

    void addObject(Object &&object);
    void run();

private:
    struct Handler {
        sf::Keyboard::Key key;
        std::function<void()> body;
    };

    void createKeyboardHandlers();

    Renderer renderer_;
    World world_;
    Camera camera_;
    sf::RenderWindow window_;
    std::vector<Handler> keyboardHandlers;
};
} // namespace ScratchRenderer

#endif
