#ifndef CLIPPING_H
#define CLIPPING_H

#include "global_usings.h"
#include "intersection.h"
#include "primitives.h"

namespace ScratchRenderer {
struct ClippedTriangle {
    enum class Type {
        Empty,
        OneTriangle,
        TwoTriangles,
    };

    Type type;
    std::array<const Primitives::Triangle &, 2> triangles;
};

const ClippedTriangle &clipTrianglePlane(const Primitives::Triangle &triangle,
                                         const Primitives::Plane &plane);

} // namespace ScratchRenderer

#endif // CLIPPING_H
