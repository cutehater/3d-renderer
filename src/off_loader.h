#ifndef OFF_LOADER_H
#define OFF_LOADER_H

#include "object.h"
#include <string>

namespace ScratchRenderer {
class Loader {
public:
    Object Load(const std::string &filepath) const;

private:
    static constexpr double RGBMultiplier = 255;

    bool checkFileExtension(const std::string &filepath) const;
    bool checkBlankLinesAndComments(const std::string &line) const;
};
} // namespace ScratchRenderer

#endif // OFF_LOADER_H
