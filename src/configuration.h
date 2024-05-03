#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <cstddef>
#include <numbers>

namespace ScratchRenderer {
namespace configuration {
constexpr char kWindowName[] = "3d-renderer";
constexpr char kModelExtension[] = ".off";

constexpr size_t kWindowWidth = 1200;
constexpr size_t kWindowHeight = 800;
constexpr double kAspectRatio = double(kWindowHeight) / kWindowWidth;

constexpr double kNearPlaneDist = 1;
constexpr double kFarPlaneDist = 1000;
constexpr double kFieldOfViewAngle = std::numbers::pi / 8;

constexpr double kCameraTranslateSpeed = 0.3;
constexpr double kCameraRotateSpeed = 0.05;
} // namespace configuration
} // namespace ScratchRenderer

#endif // CONFIGURATION_H
