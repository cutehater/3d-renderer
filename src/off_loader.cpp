#include "off_loader.h"

#include "configuration.h"
#include "global_usings.h"

#include <cassert>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ScratchRenderer {
Object Loader::Load(const std::string &filepath) const {
    checkFileExtension(filepath);
    std::ifstream file(filepath);
    std::string line;

    size_t vertexCount, faceCount;
    std::vector<Primitives::Vertex> vertices;
    std::vector<Primitives::Triangle> triangles;

    getVertexFaceEdgeCount(file, vertexCount, faceCount);
    processVertices(file, vertexCount, vertices);
    processSurfaces(file, faceCount, vertices, triangles);

    return Object(std::move(triangles));
}

void Loader::checkFileExtension(const std::string &filepath) const {
    if (filepath.length() < 4 ||
        filepath.substr(filepath.length() - 4, filepath.length()) != configuration::gModelExtension) {
        throw(std::invalid_argument(std::string("Only ") + configuration::gModelExtension +
                                    "files are supported"));
    }
}

bool Loader::isBlankLineOrComment(const std::string &line) const {
    return line.length() == 0 || line[0] == '#';
}

void Loader::convertToCommonRGBCoordinates(double &r, double &g, double &b, double &a,
                                           bool isDefaultA) const {
    if (r >= 0 && r <= 1 && g >= 0 && g <= 1 && b >= 0 && b <= 1 && a >= 0 && a <= 1) {
        r *= RGBMultiplier;
        g *= RGBMultiplier;
        b *= RGBMultiplier;
        a *= RGBMultiplier;
    } else {
        assert(r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255 && a >= 0 && a <= 255 &&
               "invalid color record in .off file");
        if (isDefaultA) {
            a = RGBMultiplier;
        }
    }
}

void Loader::getVertexFaceEdgeCount(std::ifstream &file, size_t &vertexCount, size_t &faceCount) const {
    std::string line;
    bool isFirstLine = true;

    while (getline(file, line)) {
        if (isBlankLineOrComment(line) || (line.substr(0, 3) == "OFF" && isFirstLine)) {
            continue;
        }
        isFirstLine = false;

        std::istringstream lineReader(line);
        size_t edgeCount;
        lineReader >> vertexCount >> edgeCount >> faceCount;
        break;
    }
}

void Loader::processVertices(std::ifstream &file, size_t vertexCount,
                             std::vector<Primitives::Vertex> &vertices) const {
    std::string line;
    vertices.reserve(vertexCount);

    for (size_t i = 0; i < vertexCount; ++i) {
        while (getline(file, line)) {
            if (isBlankLineOrComment(line)) {
                continue;
            }

            std::istringstream lineReader(line);
            double x, y, z, r, g, b, a;
            bool isDefaultA = false;
            lineReader >> x >> y >> z;

            if (lineReader >> r >> g >> b) {
                if (!(lineReader >> a)) {
                    isDefaultA = true;
                    a = 1;
                }
                convertToCommonRGBCoordinates(r, g, b, a, isDefaultA);
                vertices.emplace_back(Vector4(x, y, z), Color(r, g, b, a));
            } else {
                vertices.emplace_back(Vector4(x, y, z));
            }

            break;
        }
    }
}

void Loader::processSurfaces(std::ifstream &file, size_t faceCount, std::vector<Primitives::Vertex> &vertices,
                             std::vector<Primitives::Triangle> &triangles) const {
    std::string line;

    for (size_t i = 0; i < faceCount; ++i) {
        while (getline(file, line)) {
            if (isBlankLineOrComment(line)) {
                continue;
            }
            std::istringstream lineReader(line);
            size_t faceVertexCount;
            lineReader >> faceVertexCount;
            std::vector<size_t> faceVerticesIdx;
            faceVerticesIdx.reserve(faceVertexCount);
            for (size_t j = 0; j < faceVertexCount; ++j) {
                size_t idx;
                lineReader >> idx;
                faceVerticesIdx.emplace_back(idx);
            }

            bool isFaceColored = false;
            double r, g, b, a;
            bool isDefaultA = false;
            if (lineReader >> r >> g >> b) {
                isFaceColored = true;
                if (!(lineReader >> a)) {
                    a = 1;
                    isDefaultA = true;
                }
            }
            convertToCommonRGBCoordinates(r, g, b, a, isDefaultA);

            if (isFaceColored) {
                for (size_t j = 0; j < faceVertexCount; ++j) {
                    vertices[faceVerticesIdx[j]].setColor(Color(r, g, b, a));
                }
            }
            for (size_t j = 1; j + 1 < faceVertexCount; ++j) {
                triangles.emplace_back(vertices[faceVerticesIdx[0]], vertices[faceVerticesIdx[j]],
                                       vertices[faceVerticesIdx[j + 1]]);
            }

            break;
        }
    }
}
} // namespace ScratchRenderer
