#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstddef>
#include <numbers>

namespace ScratchRenderer {
namespace configuration {
constexpr char gWindowName[] = "3d-renderer";
constexpr char gModelExtension[] = ".off";

constexpr size_t gWindowWidth = 1400;
constexpr size_t gWindowHeight = 1000;
constexpr double gAspectRatio = double(gWindowHeight) / gWindowWidth;

constexpr double gNearPlaneDist = 1;
constexpr double gFarPlaneDist = 1000;
constexpr double gFieldOfViewAngle = std::numbers::pi / 8;

constexpr double gCameraTranslateSpeed = 0.3;
constexpr double gCameraRotateSpeed = 0.05;
} // namespace configuration
} // namespace ScratchRenderer

#endif // CONFIGURATION_H
