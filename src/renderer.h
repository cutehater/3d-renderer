#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "primitives.h"
#include "screen.h"
#include "storage2d.h"
#include "world.h"

namespace ScratchRenderer {
class Renderer {
public:
    using Image = std::vector<sf::Vertex>;

    Renderer(size_t width, size_t height);

    const Image &renderFrame(const World &world, const Camera &camera);

private:
    struct ZBufferVertex {
        static constexpr double kMaxDepth = 1;

        double depth = kMaxDepth;
        Color color = DefaultColor;
    };
    using ZBuffer = Storage2D<ZBufferVertex>;

    double getInterpolateCoef(int left, int mid, int right) const;
    void updateZBuffer(int i, int j, const Primitives::Vertex &v);
    void sortVerticesByXCoordinate(Primitives::Vertex &vMin, Primitives::Vertex &vMid,
                                   Primitives::Vertex &vMax);
    DiscreteVector2 projectVertexToScreenAndDiscretize(const Primitives::Vertex &v) const;
    void renderWorldTriangles(const std::vector<Primitives::Triangle> &triangles);
    void renderTriangle(const Primitives::Triangle &triangle);
    void renderLine(const Primitives::Vertex &vLeft, const Primitives::Vertex &vRight, int y);
    void fillScreen();

    ZBuffer zbuffer_;
    Screen screen_;
};
} // namespace ScratchRenderer

#endif // RENDERER_H
