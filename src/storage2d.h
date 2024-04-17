#ifndef STORAGE_2D_H
#define STORAGE_2D_H

#include <cassert>
#include <vector>

namespace ScratchRenderer {
template <typename T> class Storage2D {
public:
    Storage2D(size_t rows, size_t cols)
        : rows_(rows), cols_(cols), data_(rows * cols){};

    T &operator()(size_t i, size_t j) {
        assert(i < rows_ && j < cols_ && "Index out of storage bound");
        return data_[cols_ * i + j];
    }

    const T &operator()(size_t i, size_t j) const {
        assert(i < rows_ && j < cols_ && "Index out of storage bound");
        return data_[cols_ * i + j];
    }

    void clear() {
        for (size_t i = 0; i < rows_ * cols_; ++i) {
            data_[i] = T{};
        }
    }

private:
    size_t rows_;
    size_t cols_;
    std::vector<T> data_;
};
} // namespace ScratchRenderer

#endif // STORAGE_2D_H
