#include <sdlpp/Gui/GuiContext.h>
#include <rad/Core/Integer.h>

namespace sdl
{

GuiContext::GuiContext(Window* window, rad::Ref<Renderer> renderer) :
    m_window(window),
    m_renderer(std::move(renderer))
{
}

GuiContext::~GuiContext()
{
    Destroy();
}

bool GuiContext::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends:
    bool result = ImGui_ImplSDL3_InitForSDLRenderer(m_window->GetHandle(), m_renderer->GetHandle());
    if (!result)
    {
        SDL_LOG(err, "ImGui_ImplSDL3_InitForSDLRenderer failed!");
        return false;
    }
    result = ImGui_ImplSDLRenderer3_Init(m_renderer->GetHandle());
    if (!result)
    {
        SDL_LOG(err, "ImGui_ImplSDLRenderer3_Init failed!");
        return false;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindow(m_window->GetHandle());
    SDL_Rect rect = {};
    float fontSize = 24.0f;
    if (SDL_GetDisplayBounds(displayID, &rect) == SDL_TRUE)
    {
        fontSize = (float)rad::RoundUpToMultiple<uint32_t>(rect.h / 72, 12);
    }
#if defined(_WIN32)
    auto fonts = ImGui::GetIO().Fonts;
    fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\consola.ttf", fontSize);
#endif
    return true;
}

void GuiContext::Destroy()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

bool GuiContext::ProcessEvent(const SDL_Event& event)
{
    return ImGui_ImplSDL3_ProcessEvent(&event);
}

void GuiContext::NewFrame()
{
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void GuiContext::Render()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(
        ImGui::GetDrawData(), m_renderer->GetHandle());
}

} // namespace sdl
