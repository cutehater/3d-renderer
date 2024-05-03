#include "off_loader.h"

#include "configuration.h"
#include "global_usings.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace ScratchRenderer {
Object Loader::Load(const std::string &filepath) const {
    checkFileExtension(filepath);
    std::ifstream file(filepath);
    std::string line;

    std::vector<Primitives::Vertex> vertices;
    std::vector<Primitives::Triangle> triangles;
    bool isFirstLine = true;

    size_t vertexCount, faceCount;
    while (getline(file, line)) {
        if (checkBlankLinesAndComments(line) || line.substr(0, 3) == "OFF") {
            continue;
        }

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
            processVertex(line, vertices);
            break;
        }
    }

    for (size_t i = 0; i < faceCount; ++i) {
        while (getline(file, line)) {
            if (checkBlankLinesAndComments(line)) {
                continue;
            }
            processSurface(line, vertices, triangles);
            break;
        }
    }

    file.close();
    return Object(std::move(triangles));
}

void Loader::checkFileExtension(const std::string &filepath) const {
    if (filepath.length() < 4 ||
        filepath.substr(filepath.length() - 4, filepath.length()) != configuration::kModelExtension) {
        throw(std::invalid_argument(std::string("Only ") + configuration::kModelExtension +
                                    "files are supported"));
    }
}

bool Loader::checkBlankLinesAndComments(const std::string &line) const {
    return line.length() == 0 || line[0] == '#';
}

void Loader::convertToCommonRGBCoordinates(double &r, double &g, double &b, double &a, bool aDefault) const {
    if (r >= 0 && r <= 1 && g >= 0 && g <= 1 && b >= 0 && b <= 1 && a >= 0 && a <= 1) {
        r *= RGBMultiplier;
        g *= RGBMultiplier;
        b *= RGBMultiplier;
        a *= RGBMultiplier;
    } else if (aDefault) {
        a = RGBMultiplier;
    }
}

void Loader::processVertex(const std::string &line, std::vector<Primitives::Vertex> &vertices) const {
    std::istringstream lineReader(line);
    double x, y, z, r, g, b, a;
    bool aDefault = false;
    lineReader >> x >> y >> z;
    if (lineReader >> r >> g >> b) {
        if (!(lineReader >> a)) {
            aDefault = true;
            a = 1;
        }
        convertToCommonRGBCoordinates(r, g, b, a, aDefault);
        vertices.emplace_back(Vector4(x, y, z), Color(r, g, b, a));
    } else {
        vertices.emplace_back(Vector4(x, y, z));
    }
}

void Loader::processSurface(const std::string &line, std::vector<Primitives::Vertex> &vertices,
                            std::vector<Primitives::Triangle> &triangles) const {
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
    bool aDefault = false;
    if (lineReader >> r >> g >> b) {
        isFaceColored = true;
        if (!(lineReader >> a)) {
            a = 1;
            aDefault = true;
        }
    }
    convertToCommonRGBCoordinates(r, g, b, a, aDefault);

    if (isFaceColored) {
        for (size_t j = 0; j < faceVertexCount; ++j) {
            vertices[faceVerticesIdx[j]].setColor(Color(r, g, b, a));
        }
    }
    for (size_t j = 1; j + 1 < faceVertexCount; ++j) {
        triangles.emplace_back(vertices[faceVerticesIdx[0]], vertices[faceVerticesIdx[j]],
                               vertices[faceVerticesIdx[j + 1]]);
    }
}
} // namespace ScratchRenderer
