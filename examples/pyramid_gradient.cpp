#include "application.h"
#include "object.h"
#include "primitives.h"

#include <SFML/Graphics.hpp>
#include <utility>
#include <vector>

int main() {
    using Triangle = ScratchRenderer::Primitives::Triangle;
    using Vertex = ScratchRenderer::Primitives::Vertex;
    using Vector4 = ScratchRenderer::Vector4;
    using Color = sf::Color;

    auto makeGradient = [](const Vector4 &A, const Vector4 &B, const Vector4 &C) {
        return Triangle{
            Vertex{A, Color::Blue},
            Vertex{B, Color::Green},
            Vertex{C, Color::Red},
        };
    };

    auto makeUsual = [](const Vector4 &A, const Vector4 &B, const Vector4 &C, const Color &color) {
        return Triangle{
            Vertex{A, color},
            Vertex{B, color},
            Vertex{C, color},
        };
    };

    Vector4 O(0, 1, 5);
    Vector4 A(-1, -1, 4);
    Vector4 B(1, -1, 4);
    Vector4 C(1, -1, 6);
    Vector4 D(-1, -1, 6);
    ScratchRenderer::Object pyramid({makeUsual(A, B, D, Color::Cyan), makeUsual(D, C, A, Color::Cyan),
                                     makeGradient(O, A, B), makeGradient(O, C, B), makeGradient(O, C, D),
                                     makeGradient(O, A, D)});

    ScratchRenderer::Application app;
    app.addObject(std::move(pyramid));
    app.run();
    return 0;
}
