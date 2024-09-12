#pragma once

#include <rad/IO/Logging.h>
#include <SDL3/SDL_log.h>

namespace sdl
{

spdlog::logger* GetLogger();

#define SDL_LOG(Level, ...) RAD_LOG(sdl::GetLogger(), Level, __VA_ARGS__)

} // namespace sdl
