#include "world.h"

#include <cassert>

namespace ScratchRenderer {
World::ConstIterator::ConstIterator(const World *world, size_t objectIdx,
                                    size_t triangleIdx)
    : world_(world), objectIdx_(objectIdx), triangleIdx_(triangleIdx) {
    assert(world != nullptr && "World ptr shouldn't be null");
}

const Primitives::Triangle &World::ConstIterator::operator*() const {
    return world_->objects_[objectIdx_].getTriangles()[triangleIdx_];
}

World::ConstIterator &World::ConstIterator::operator++() {
    ++triangleIdx_;
    if (world_->objects_[objectIdx_].getTriangles().size() == triangleIdx_) {
        ++objectIdx_;
        triangleIdx_ = 0;
    }
    return *this;
}

World::ConstIterator World::ConstIterator::operator++(int) {
    World::ConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

bool World::ConstIterator::operator==(ConstIterator other) const {
    return world_ == other.world_ && objectIdx_ == other.objectIdx_ &&
           triangleIdx_ == other.triangleIdx_;
}

bool World::ConstIterator::operator!=(ConstIterator other) const {
    return !(*this == other);
}

World::ConstIterator World::begin() const {
    return World::ConstIterator(this, 0, 0);
}

World::ConstIterator World::end() const {
    return World::ConstIterator(this, objects_.size(), 0);
}

void World::addObject(Object &&object) {
    objects_.emplace_back(std::move(object));
}

} // namespace ScratchRenderer