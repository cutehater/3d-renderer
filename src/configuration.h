#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstddef>
#include <numbers>
#include <string>

namespace ScratchRenderer {
namespace configuration {
constexpr char kWindowName[] = "3d-renderer";

constexpr size_t kWindowWidth = 1000;
constexpr size_t kWindowHeight = 1000;
constexpr double kAspectRatio = double(kWindowHeight) / kWindowWidth;

constexpr double kNearPlaneDist = 1;
constexpr double kFarPlaneDist = 10;
constexpr double kFieldOfViewAngle = std::numbers::pi / 2;

constexpr double kCameraTranslateSpeed = 0.1;
constexpr double kCameraRotateSpeed = 0.1;
} // namespace configuration
} // namespace ScratchRenderer

#endif // CONFIGURATION_H
