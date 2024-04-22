#include "off_loader.h"

#include "configuration.h"
#include "global_usings.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ScratchRenderer {
Object Loader::Load(const std::string &filepath) const {
    if (!checkFileExtension(filepath)) {
        throw(std::invalid_argument(std::string("Only ") + configuration::kModelExtension +
                                    "files are supported"));
    }
    std::ifstream file(filepath);
    std::string line;

    std::vector<Primitives::Vertex> vertices;
    std::vector<Primitives::Triangle> triangles;
    bool isFirstLine = true;

    size_t vertexCount, faceCount;
    while (getline(file, line)) {
        if (checkBlankLinesAndComments(line) || (isFirstLine && line == "OFF")) {
            isFirstLine = false;
            continue;
        }
        isFirstLine = false;

        std::istringstream lineReader(line);
        size_t edgeCount;
        lineReader >> vertexCount >> edgeCount >> faceCount;
        break;
    }

    vertices.reserve(vertexCount);
    for (size_t i = 0; i < vertexCount; ++i) {
        while (getline(file, line)) {
            if (checkBlankLinesAndComments(line)) {
                continue;
            }

            std::istringstream lineReader(line);
            double x, y, z, r, g, b, a;
            lineReader >> x >> y >> z;
            if (lineReader >> r >> g >> b >> a) {
                vertices.emplace_back(Vector4(x, y, z),
                                      Color(uint8_t(r), uint8_t(g), uint8_t(b), uint8_t(a)));
            } else {
                vertices.emplace_back(Vector4(x, y, z));
            }
            break;
        }
    }

    for (size_t i = 0; i < faceCount; ++i) {
        while (getline(file, line)) {
            if (checkBlankLinesAndComments(line)) {
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
            if (lineReader >> r >> g >> b >> a) {
                isFaceColored = true;
            }

            for (size_t j = 0; j < faceVertexCount; ++j) {
                if (isFaceColored) {
                    for (size_t vi = j; vi <= j + 2; ++vi) {
                        vertices[faceVerticesIdx[vi % faceVertexCount]].setColor(
                            Color(uint8_t(r), uint8_t(g), uint8_t(b), uint8_t(a)));
                    }
                }
                triangles.emplace_back(vertices[faceVerticesIdx[j]],
                                       vertices[faceVerticesIdx[(j + 1) % faceVertexCount]],
                                       vertices[faceVerticesIdx[(j + 2) % faceVertexCount]]);
            }

            break;
        }
    }

    file.close();
    return Object(std::move(triangles));
}

bool Loader::checkFileExtension(const std::string &filepath) const {
    if (filepath.length() < 4) {
        return false;
    }
    std::string extension = filepath.substr(filepath.length() - 4, filepath.length());
    return extension == configuration::kModelExtension;
}

bool Loader::checkBlankLinesAndComments(const std::string &line) const {
    return line.length() == 0 || line[0] == '#';
}
} // namespace ScratchRenderer
