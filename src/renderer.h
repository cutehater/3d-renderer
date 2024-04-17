#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "primitives.h"
#include "screen.h"
#include "storage2d.h"
#include "world.h"
#include <SFML/Graphics.hpp>

namespace ScratchRenderer {
class Renderer {
public:
    Renderer(size_t width, size_t height);

    void renderFrame(sf::RenderWindow &window, const World &world, const Camera &camera);

private:
    struct ZBufferVertex {
        static constexpr double kMaxDepth = 1 + Epsilon;

        double depth = kMaxDepth;
        Color color = DefaultColor;
    };
    using ZBuffer = Storage2D<ZBufferVertex>;

    double getInterpolateCoef(size_t left, size_t mid, size_t right) const;
    void updateZBuffer(size_t i, size_t j, const Primitives::Vertex &v);
    void renderTriangle(const Primitives::Triangle &triangle);
    void renderLine(const Primitives::Vertex &vLeft, const Primitives::Vertex &vRight, size_t y);
    void drawFrame(sf::RenderWindow &window);

    ZBuffer zbuffer_;
    Screen screen_;
};
} // namespace ScratchRenderer

#endif // RENDERER_H
