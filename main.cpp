#include "src/application.h"
#include "src/global_usings.h"
#include "src/object.h"
#include "src/off_loader.h"

#include <utility>

void createScene(ScratchRenderer::Application &app) {
    using Point4 = ScratchRenderer::Vector4;
    using Vertex = ScratchRenderer::Primitives::Vertex;
    using Vector3 = ScratchRenderer::Vector3;

    Point4 A{0, 0, 4};
    Point4 B{0, 0, 2};
    Point4 C{1, 0, 3};
    Point4 D{-1, 0, 3};
    Point4 E{0, 1.5, 3};

    auto createFace = [](const Point4 &A, const Point4 &B, const Point4 &C, const sf::Color &color) {
        return ScratchRenderer::Primitives::Triangle{
            Vertex{A, color},
            Vertex{B, color},
            Vertex{C, color},
        };
    };
    auto createFaceGradient = [](const Point4 &A, const Point4 &B, const Point4 &C) {
        return ScratchRenderer::Primitives::Triangle{
            Vertex{A, sf::Color::Red},
            Vertex{B, sf::Color::Blue},
            Vertex{C, sf::Color::Green},
        };
    };
    // std::vector<ScratchRenderer::Primitives::Triangle> triangles = {
    //    createFace(A, E, C, sf::Color::Blue), createFace(A, E, D, sf::Color::Magenta),
    //    createFace(B, E, D, sf::Color::Cyan), createFace(B, E, C, sf::Color::Green),
    //    createFace(A, B, D, sf::Color::Red),  createFace(A, B, C, sf::Color::Red),
    //};
    std::vector<ScratchRenderer::Primitives::Triangle> triangles = {
        createFaceGradient(A, E, C), createFaceGradient(A, E, D),         createFaceGradient(B, E, D),
        createFaceGradient(B, E, C), createFace(A, B, D, sf::Color::Red), createFace(A, B, C, sf::Color::Red),
    };

    app.addObject(ScratchRenderer::Object(std::move(triangles)));
}

int main() {
    ScratchRenderer::Application app;
    ScratchRenderer::Loader loader;
    app.addObject(loader.Load("br2.off"));
    // createScene(app);
    app.run();
    return 0;
}
