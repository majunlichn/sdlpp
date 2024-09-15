#include "WindowTest.h"
#include <sdlpp/Gui/Texture.h>
#include <sdlpp/Gui/Image.h>

WindowTest::WindowTest()
{
    m_logger = rad::CreateLogger("WindowTest");
    RAD_LOG(m_logger, info, "WindowTest::WindowTest()");
}

WindowTest::~WindowTest()
{
    RAD_LOG(m_logger, info, "WindowTest::~WindowTest()");
}

bool WindowTest::Init()
{
    SDL_WindowFlags flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN;
    Create("WindowTest", 800, 600, flags);

    m_renderer = RAD_NEW sdl::Renderer(this);
    if (!m_renderer->Init())
    {
        return false;
    }
    m_renderer->SetVSync(1);

    m_guiContext = RAD_NEW sdl::GuiContext(this, m_renderer);
    if (!m_guiContext->Init())
    {
        return false;
    }

    sdl::ImageU8 image;
    if (image.Load("SDL_logo.png", 4))
    {
        m_logo = sdl::Texture::Create(m_renderer,
            SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC,
            image.m_width, image.m_height);
        m_logo->Update(nullptr, image.m_data, image.m_width * 4);
    }
    return true;
}

bool WindowTest::OnEvent(const SDL_Event& event)
{
    if (m_guiContext)
    {
        m_guiContext->ProcessEvent(event);
    }
    return Window::OnEvent(event);
}

void WindowTest::OnIdle()
{
    if (GetFlags() & SDL_WINDOW_MINIMIZED)
    {
        return;
    }
    m_renderer->Clear();
    if (m_logo)
    {
        float texWidth = 0;
        float texHeight = 0;
        m_logo->GetSize(&texWidth, &texHeight);

        SDL_FRect dstRect = {};
        dstRect.x = 0.0f;
        dstRect.y = 0.0f;
        dstRect.w = texWidth;
        dstRect.h = texHeight;
        m_renderer->DrawTexture(m_logo.get(), nullptr, &dstRect);
    }
    m_guiContext->NewFrame();
    if (m_showDemoWindow)
    {
        ImGui::ShowDemoWindow(&m_showDemoWindow);
    }
    m_guiContext->Render();
    m_renderer->Present();
}

void WindowTest::OnShown()
{
    RAD_LOG(m_logger, info, "OnShown");
}

void WindowTest::OnHidden()
{
    RAD_LOG(m_logger, info, "OnHidden");
}

void WindowTest::OnExposed()
{
    RAD_LOG(m_logger, info, "OnExposed");
}

void WindowTest::OnMoved(int x, int y)
{
    RAD_LOG(m_logger, info, "OnMoved: {:4}, {:4}", x, y);
}

void WindowTest::OnResized(int width, int height)
{
    RAD_LOG(m_logger, info, "OnResized: {:4}, {:4}", width, height);
}

void WindowTest::OnPixelSizeChanged(int width, int height)
{
    RAD_LOG(m_logger, info, "OnPixelSizeChanged: {:4}, {:4}", width, height);
}

void WindowTest::OnMinimized()
{
    RAD_LOG(m_logger, info, "OnMinimized");
}

void WindowTest::OnMaximized()
{
    RAD_LOG(m_logger, info, "OnMaximized");
}

void WindowTest::OnRestored()
{
    RAD_LOG(m_logger, info, "OnRestored");
}

void WindowTest::OnMouseEnter()
{
    RAD_LOG(m_logger, info, "OnMouseEnter");
}

void WindowTest::OnMouseLeave()
{
    RAD_LOG(m_logger, info, "OnMouseLeave");
}

void WindowTest::OnFocusGained()
{
    RAD_LOG(m_logger, info, "OnFocusGained");
}

void WindowTest::OnFocusLost()
{
    RAD_LOG(m_logger, info, "OnFocusLost");
}

void WindowTest::OnCloseRequested()
{
    RAD_LOG(m_logger, info, "OnCloseRequested");
    Destroy();
}

void WindowTest::OnHitTest()
{
    RAD_LOG(m_logger, info, "OnHitTest");
}

void WindowTest::OnIccProfileChanged()
{
    RAD_LOG(m_logger, info, "OnIccProfileChanged");
}

void WindowTest::OnDisplayChanged()
{
    RAD_LOG(m_logger, info, "OnDisplayChanged");
}

void WindowTest::OnDisplayScaleChanged()
{
    RAD_LOG(m_logger, info, "OnDisplayScaleChanged");
}

void WindowTest::OnOccluded()
{
    RAD_LOG(m_logger, info, "OnOccluded");
}

void WindowTest::OnEnterFullscreen()
{
    RAD_LOG(m_logger, info, "OnEnterFullscreen");
}

void WindowTest::OnLeaveFullscreen()
{
    RAD_LOG(m_logger, info, "OnLeaveFullscreen");
}

void WindowTest::OnDestroyed()
{
    RAD_LOG(m_logger, info, "OnDestroyed");
}

void WindowTest::OnKeyDown(const SDL_KeyboardEvent& keyDown)
{
    RAD_LOG(m_logger, info, "OnKeyDown: {}", SDL_GetKeyName(keyDown.key));
    if (keyDown.key == SDLK_F1)
    {
        m_showDemoWindow = !m_showDemoWindow;
    }
}

void WindowTest::OnKeyUp(const SDL_KeyboardEvent& keyUp)
{
    RAD_LOG(m_logger, info, "OnKeyUp: {}", SDL_GetKeyName(keyUp.key));
}

void WindowTest::OnTextEditing(const SDL_TextEditingEvent& textEditing)
{
    RAD_LOG(m_logger, info, "OnTextEditing: {}", textEditing.text);
}

void WindowTest::OnTextInput(const SDL_TextInputEvent& textInput)
{
    RAD_LOG(m_logger, info, "OnTextInput: {}", textInput.text);
}

void WindowTest::OnMouseMove(const SDL_MouseMotionEvent& mouseMotion)
{
    RAD_LOG(m_logger, info, "OnMouseMove: x={:4} ({:+4}); y={:4} ({:+4})",
        mouseMotion.x, mouseMotion.xrel, mouseMotion.y, mouseMotion.yrel);
}

void WindowTest::OnMouseButtonDown(const SDL_MouseButtonEvent& mouseButton)
{
    RAD_LOG(m_logger, info, "OnMouseButtonDown: {}", GetMouseButtonName(mouseButton.button));
}

void WindowTest::OnMouseButtonUp(const SDL_MouseButtonEvent& mouseButton)
{
    RAD_LOG(m_logger, info, "OnMouseButtonUp: {}", GetMouseButtonName(mouseButton.button));
}

void WindowTest::OnMouseWheel(const SDL_MouseWheelEvent& mouseWheel)
{
    RAD_LOG(m_logger, info, "OnMouseWheel: {:+}", mouseWheel.y);
}

void WindowTest::OnUserEvent(const SDL_UserEvent& user)
{
    RAD_LOG(m_logger, info, "OnUserEvent");
}

const char* WindowTest::GetMouseButtonName(Uint8 button)
{
    switch (button)
    {
    case SDL_BUTTON_LEFT: return "SDL_BUTTON_LEFT";
    case SDL_BUTTON_MIDDLE: return "SDL_BUTTON_MIDDLE";
    case SDL_BUTTON_RIGHT: return "SDL_BUTTON_RIGHT";
    case SDL_BUTTON_X1: return "SDL_BUTTON_X1";
    case SDL_BUTTON_X2: return "SDL_BUTTON_X2";
    }
    return "SDL_BUTTON_UNKNOWN";
}
