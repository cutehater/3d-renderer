#ifndef OBJECT_H
#define OBJECT_H

#include "global_usings.h"
#include "primitives.h"
#include <vector>

namespace ScratchRenderer {
class Object {
public:
    Object() = default;
    explicit Object(std::vector<Primitives::Triangle> &&triangles);

    const std::vector<Primitives::Triangle> &getTriangles() const;

private:
    std::vector<Primitives::Triangle> triangles_;
};
} // namespace ScratchRenderer

#endif OBJECT_H
