#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstddef>
#include <numbers>
#include <string>

namespace ScratchRenderer {
namespace configuration {
constexpr char kWindowName[] = "3d-renderer";
constexpr char kModelExtension[] = ".off";

constexpr size_t kWindowWidth = 1000;
constexpr size_t kWindowHeight = 1000;
constexpr double kAspectRatio = double(kWindowHeight) / kWindowWidth;

constexpr double kNearPlaneDist = 1.4;
constexpr double kFarPlaneDist = 100;
constexpr double kFieldOfViewAngle = std::numbers::pi / 6;

constexpr double kCameraTranslateSpeed = 0.3;
constexpr double kCameraRotateSpeed = 0.05;
} // namespace configuration
} // namespace ScratchRenderer

#endif // CONFIGURATION_H
