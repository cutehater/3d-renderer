#include "renderer.h"

#include <array>
#include <utility>

namespace ScratchRenderer {
Renderer::Renderer(size_t width, size_t height) : screen_(width, height), zbuffer_(width, height) {}

void Renderer::renderFrame(sf::RenderWindow &window, const World &world, const Camera &camera) {
    std::vector<Primitives::Triangle> projectedTriangles = std::move(camera.projectWorldObjects(world));
    for (const Primitives::Triangle &triangle : projectedTriangles) {
        renderTriangle(triangle);
    }
    for (size_t i = 0; i < screen_.getWidth(); ++i) {
        for (size_t j = 0; j < screen_.getHeight(); ++j) {
            screen_.setPixel(i, j, zbuffer_(i, j).color);
        }
    }
    drawFrame(window);
}

double Renderer::getInterpolateCoef(size_t left, size_t mid, size_t right) const {
    assert(left != right && left <= mid && mid <= right && "Bad interpolating coefficient");
    return double(mid - left) / (right - left);
}

void Renderer::updateZBuffer(size_t i, size_t j, const Primitives::Vertex &v) {
    if (zbuffer_(i, j).depth > v.getPosition().z) {
        zbuffer_(i, j).depth = v.getPosition().z;
        zbuffer_(i, j).color = v.getColor();
    }
}

void Renderer::renderTriangle(const Primitives::Triangle &triangle) {
    auto [vMin, vMid, vMax] = triangle.getYOrderedVertices();
    size_t yMin = screen_.projectVertexToScreenAndDiscretize(vMin).y;
    size_t yMid = screen_.projectVertexToScreenAndDiscretize(vMid).y;
    size_t yMax = screen_.projectVertexToScreenAndDiscretize(vMax).y;

    if (yMin == yMax) {
        size_t xMin = screen_.projectVertexToScreenAndDiscretize(vMin).x;
        size_t xMid = screen_.projectVertexToScreenAndDiscretize(vMid).x;
        size_t xMax = screen_.projectVertexToScreenAndDiscretize(vMax).x;
        if (xMin > xMid) {
            std::swap(xMin, xMid);
            std::swap(vMin, vMid);
        }
        if (xMid > xMax) {
            std::swap(xMid, xMax);
            std::swap(vMid, vMax);
        }
        if (xMin > xMid) {
            std::swap(xMin, xMid);
            std::swap(vMin, vMid);
        }
        renderLine(vMin, vMax, yMin);
        return;
    }

    for (size_t y = yMin; y <= yMax; ++y) {
        Primitives::Vertex vLeft =
            Primitives::Vertex::interpolate(vMin, vMax, getInterpolateCoef(yMin, y, yMax));
        Primitives::Vertex vRight =
            (yMid > yMin && y <= yMid)
                ? Primitives::Vertex::interpolate(vMin, vMid, getInterpolateCoef(yMin, y, yMid))
                : Primitives::Vertex::interpolate(vMid, vMax, getInterpolateCoef(yMid, y, yMax));

        size_t xLeft = screen_.projectVertexToScreenAndDiscretize(vLeft).x;
        size_t xRight = screen_.projectVertexToScreenAndDiscretize(vRight).x;
        if (xLeft > xRight) {
            std::swap(vLeft, vRight);
        }

        renderLine(vLeft, vRight, y);
    }
}

void Renderer::renderLine(const Primitives::Vertex &vLeft, const Primitives::Vertex &vRight, size_t y) {
    size_t xLeft = screen_.projectVertexToScreenAndDiscretize(vLeft).x;
    size_t xRight = screen_.projectVertexToScreenAndDiscretize(vRight).x;

    if (xLeft == xRight) {
        updateZBuffer(xLeft, y, (vLeft.getPosition().z < vRight.getPosition().z ? vLeft : vRight));
    } else {
        for (size_t x = xLeft; x <= xRight; ++x) {
            updateZBuffer(
                x, y, Primitives::Vertex::interpolate(vLeft, vRight, getInterpolateCoef(xLeft, x, xRight)));
        }
    }
}

void Renderer::drawFrame(sf::RenderWindow &window) {
    window.draw(screen_.getDrawData().data(), screen_.getDrawData().size(), sf::Points);
    zbuffer_.clear();
    screen_.clear();
}
} // namespace ScratchRenderer
