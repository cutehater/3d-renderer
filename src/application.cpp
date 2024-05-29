#include "application.h"

#include "configuration.h"
#include "global_usings.h"

namespace ScratchRenderer {
Application::Application(Initializer init)
    : renderer_(configuration::gWindowWidth, configuration::gWindowHeight),
      window_(sf::VideoMode(configuration::gWindowWidth, configuration::gWindowHeight),
              configuration::gWindowName) {
    createKeyboardHandlers();
    init(world_);
};

void Application::run() {
    while (window_.isOpen()) {
        if (hasWindowClosed()) {
            return;
        }
        handleKeyboardInput();
        Renderer::Image image = renderer_.renderFrame(world_, camera_);
        drawFrame(image);
    }
}

void Application::createKeyboardHandlers() {
    keyboardHandlers_ = {
        {.key = sf::Keyboard::A,
         .body = [this]() { camera_.translate(Axis::X, -configuration::gCameraTranslateSpeed); }},
        {.key = sf::Keyboard::D,
         .body = [this]() { camera_.translate(Axis::X, configuration::gCameraTranslateSpeed); }},
        {.key = sf::Keyboard::W,
         .body = [this]() { camera_.translate(Axis::Z, configuration::gCameraTranslateSpeed); }},
        {.key = sf::Keyboard::S,
         .body = [this]() { camera_.translate(Axis::Z, -configuration::gCameraTranslateSpeed); }},
        {.key = sf::Keyboard::Z,
         .body = [this]() { camera_.translate(Axis::Y, configuration::gCameraTranslateSpeed); }},
        {.key = sf::Keyboard::X,
         .body = [this]() { camera_.translate(Axis::Y, -configuration::gCameraTranslateSpeed); }},
        {.key = sf::Keyboard::I,
         .body = [this]() { camera_.rotate(Axis::X, configuration::gCameraRotateSpeed); }},
        {.key = sf::Keyboard::K,
         .body = [this]() { camera_.rotate(Axis::X, -configuration::gCameraRotateSpeed); }},
        {.key = sf::Keyboard::J,
         .body = [this]() { camera_.rotate(Axis::Y, configuration::gCameraRotateSpeed); }},
        {.key = sf::Keyboard::L,
         .body = [this]() { camera_.rotate(Axis::Y, -configuration::gCameraRotateSpeed); }},
        {.key = sf::Keyboard::Q,
         .body = [this]() { camera_.rotate(Axis::Z, configuration::gCameraRotateSpeed); }},
        {.key = sf::Keyboard::E,
         .body = [this]() { camera_.rotate(Axis::Z, -configuration::gCameraRotateSpeed); }},

    };
}

bool Application::hasWindowClosed() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
            return true;
        }
    }
    return false;
}

void Application::handleKeyboardInput() {
    for (const Handler &handler : keyboardHandlers_) {
        if (sf::Keyboard::isKeyPressed(handler.key)) {
            handler.body();
        }
    }
}

void Application::drawFrame(const Renderer::Image &image) {
    window_.draw(image.data(), image.size(), sf::Points);
    window_.display();
}
} // namespace ScratchRenderer
