#include <sdlpp/Core/Logging.h>

namespace sdl
{

spdlog::logger* GetLogger()
{
    static std::shared_ptr<spdlog::logger> logger = rad::CreateLogger("sdlpp");
    return logger.get();
}

} // namespace sdl
