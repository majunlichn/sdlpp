#define SDL_MAIN_USE_CALLBACKS
#include "WindowTest.h"
#include <SDL3/SDL_main.h>

rad::Ref<sdl::Application> g_app;
rad::Ref<WindowTest> g_window;

SDL_AppResult SDL_AppInit(void** appState, int argc, char** argv)
{
    g_app = RAD_NEW sdl::Application();
    if (!g_app->Init(argc, argv))
    {
        return SDL_APP_FAILURE;
    }
    g_window = RAD_NEW WindowTest();
    if (!g_window->Init())
    {
        return SDL_APP_FAILURE;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appState)
{
    g_app->OnIdle();
    return g_app->GetExit() ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    g_app->OnEvent(*event);
    return g_app->GetExit() ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    g_window.reset();
    g_app.reset();
}
