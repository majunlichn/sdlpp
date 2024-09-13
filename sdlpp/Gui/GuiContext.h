#pragma once

#include <sdlpp/Gui/Renderer.h>

#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

namespace sdl
{

class GuiContext : public rad::RefCounted<GuiContext>
{
public:
    GuiContext(Window* window, rad::Ref<Renderer> renderer);
    ~GuiContext();

    bool Init();
    void Destroy();
    bool ProcessEvent(const SDL_Event& event);

    void NewFrame();
    void Render();

private:
    Window* m_window;
    rad::Ref<Renderer> m_renderer;

}; // class GuiContext

} // namespace sdl
