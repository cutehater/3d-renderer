#include "application.h"

#include "configuration.h"
#include "vector4.h"

namespace ScratchRenderer {
Application::Application()
    : renderer_(configuration::kWindowWidth, configuration::kWindowHeight), world_(), camera_(),
      window_(sf::VideoMode(configuration::kWindowWidth, configuration::kWindowHeight),
              configuration::kWindowName) {
    createKeyboardHandlers();
};

void Application::addObject(Object &&object) { world_.addObject(std::move(object)); }

void Application::run() {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
                return;
            }
        }
        for (const Handler &handler : keyboardHandlers_) {
            if (sf::Keyboard::isKeyPressed(handler.key)) {
                handler.body();
            }
        }
        renderer_.renderFrame(window_, world_, camera_);
        window_.display();
    }
}

void Application::createKeyboardHandlers() {
    keyboardHandlers_ = {
        {.key = sf::Keyboard::A,
         .body = [this]() { camera_.translate(Camera::Axe::X, configuration::kCameraTranslateSpeed); }},
        {.key = sf::Keyboard::D,
         .body = [this]() { camera_.translate(Camera::Axe::X, -configuration::kCameraTranslateSpeed); }},
        {.key = sf::Keyboard::W,
         .body = [this]() { camera_.translate(Camera::Axe::Z, configuration::kCameraTranslateSpeed); }},
        {.key = sf::Keyboard::S,
         .body = [this]() { camera_.translate(Camera::Axe::Z, -configuration::kCameraTranslateSpeed); }},
        {.key = sf::Keyboard::Z,
         .body = [this]() { camera_.translate(Camera::Axe::Y, configuration::kCameraTranslateSpeed); }},
        {.key = sf::Keyboard::X,
         .body = [this]() { camera_.translate(Camera::Axe::Y, -configuration::kCameraTranslateSpeed); }},
        {.key = sf::Keyboard::I,
         .body = [this]() { camera_.rotate(Camera::Axe::X, configuration::kCameraRotateSpeed); }},
        {.key = sf::Keyboard::K,
         .body = [this]() { camera_.rotate(Camera::Axe::X, -configuration::kCameraRotateSpeed); }},
        {.key = sf::Keyboard::J,
         .body = [this]() { camera_.rotate(Camera::Axe::Z, configuration::kCameraRotateSpeed); }},
        {.key = sf::Keyboard::L,
         .body = [this]() { camera_.rotate(Camera::Axe::Z, -configuration::kCameraRotateSpeed); }},
        {.key = sf::Keyboard::Q,
         .body = [this]() { camera_.rotate(Camera::Axe::Y, configuration::kCameraRotateSpeed); }},
        {.key = sf::Keyboard::E,
         .body = [this]() { camera_.rotate(Camera::Axe::Y, -configuration::kCameraRotateSpeed); }},

    };
}
} // namespace ScratchRenderer
