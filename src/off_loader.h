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

    void checkFileExtension(const std::string &filepath) const;
    bool isBlankLineOrComment(const std::string &line) const;
    void convertToCommonRGBCoordinates(double &r, double &g, double &b, double &a, bool aDefault) const;
    void getVertexFaceEdgeCount(std::ifstream &file, size_t &vertexCount, size_t &faceCount) const;
    void processVertices(std::ifstream &file, size_t vertexCount,
                         std::vector<Primitives::Vertex> &vertices) const;
    void processSurfaces(std::ifstream &file, size_t faceCount, std::vector<Primitives::Vertex> &vertices,
                         std::vector<Primitives::Triangle> &triangles) const;
};
} // namespace ScratchRenderer

#endif // OFF_LOADER_H
