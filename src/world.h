#ifndef WORLD_H
#define WORLD_H

#include "object.h"
#include "primitives.h"

#include <functional>
#include <vector>

namespace ScratchRenderer {
class World {
public:
    class ConstIterator {
    public:
        ConstIterator(const World &world, size_t objectIdx, size_t triangleIdx);

        const Primitives::Triangle &operator*() const;
        ConstIterator &operator++();
        ConstIterator operator++(int);
        const Primitives::Triangle *operator->() const;
        bool operator==(ConstIterator other) const;
        bool operator!=(ConstIterator other) const;

    private:
        std::reference_wrapper<const World> world_;
        size_t objectIdx_;
        size_t triangleIdx_;
    };

    World() = default;

    ConstIterator begin() const;
    ConstIterator end() const;
    size_t size() const;

    void addObject(Object &&object);

private:
    std::vector<Object> objects_;
    size_t size_ = 0;
};
} // namespace ScratchRenderer

#endif
