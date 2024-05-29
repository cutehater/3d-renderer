#include "world.h"

#include <cassert>

namespace ScratchRenderer {
World::ConstIterator::ConstIterator(const World &world, size_t objectIdx, size_t triangleIdx)
    : world_(world), objectIdx_(objectIdx), triangleIdx_(triangleIdx) {}

const Primitives::Triangle &World::ConstIterator::operator*() const {
    return world_.get().objects_[objectIdx_].getTriangles()[triangleIdx_];
}

World::ConstIterator &World::ConstIterator::operator++() {
    ++triangleIdx_;
    if (world_.get().objects_[objectIdx_].getTriangles().size() == triangleIdx_) {
        ++objectIdx_;
        triangleIdx_ = 0;
    }
    return *this;
}

World::ConstIterator World::ConstIterator::operator++(int) {
    ConstIterator tmp = *this;
    ++(*this);
    return tmp;
}

const Primitives::Triangle *World::ConstIterator::operator->() const { return &(**this); }

bool World::ConstIterator::operator==(ConstIterator other) const {
    return world_.get().objects_.begin() == other.world_.get().objects_.begin() &&
           objectIdx_ == other.objectIdx_ && triangleIdx_ == other.triangleIdx_;
}

bool World::ConstIterator::operator!=(ConstIterator other) const { return !(*this == other); }

World::ConstIterator World::begin() const { return ConstIterator(*this, 0, 0); }

World::ConstIterator World::end() const { return ConstIterator(*this, objects_.size(), 0); }

size_t World::size() const { return size_; }

void World::addObject(Object &&object) {
    size_ += object.getTriangles().size();
    objects_.emplace_back(std::move(object));
}

} // namespace ScratchRenderer
