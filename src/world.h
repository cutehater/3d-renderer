#ifndef WORLD_H
#define WORLD_H

#include "object.h"
#include "primitives.h"
#include <vector>

namespace ScratchRenderer {
class World {
private:
    class ConstIterator {
    public:
        ConstIterator(const World *world, size_t objectIdx, size_t triangleIdx);
        const Primitives::Triangle &operator*() const;
        ConstIterator &operator++();
        ConstIterator operator++(int);
        bool operator==(ConstIterator other) const;
        bool operator!=(ConstIterator other) const;

    private:
        const World *world_;
        size_t objectIdx_;
        size_t triangleIdx_;
    };

public:
    World() = default;

    ConstIterator begin() const;
    ConstIterator end() const;

    void addObject(Object &&object);

private:
    std::vector<Object> objects_;
};
} // namespace ScratchRenderer

#endif