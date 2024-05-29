#ifndef WORLD_INIT_H
#define WORLD_INIT_H

#include "application.h"
#include "world.h"

#include <string>
#include <vector>

namespace ScratchRenderer {
void cubesInit(World &world);
void pyramidGradientInit(World &world);
Application::Initializer modelInit(const std::string &modelName);
} // namespace ScratchRenderer

#endif // WORLD_INIT_H
