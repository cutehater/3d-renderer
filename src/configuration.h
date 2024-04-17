#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstddef>
#include <string>
// #include <numbers>

namespace ScratchRenderer {
namespace configuration {
constexpr char kWindowName[] = "3d-renderer";

constexpr size_t kWindowWidth = 1000;
constexpr size_t kWindowHeight = 1000;
constexpr double kAspectRatio = double(kWindowHeight) / kWindowWidth;

constexpr double kNearPlaneDist = 1;
constexpr double kFarPlaneDist = 1000;
constexpr double kFieldOfViewAngle = 3.14159265358979 / 2;

constexpr double kCameraTranslateSpeed = 10;
constexpr double kCameraRotateSpeed = 0.1;
} // namespace configuration
} // namespace ScratchRenderer

#endif // CONFIGURATION_H
