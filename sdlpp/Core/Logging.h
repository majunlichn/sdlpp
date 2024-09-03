#pragma once

#include <rad/IO/Logging.h>
#include <SDL3/SDL_log.h>

namespace sdl
{

spdlog::logger* GetLogger();

} // namespace sdl
