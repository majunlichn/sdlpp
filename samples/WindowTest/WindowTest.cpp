#include "WindowTest.h"

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
    return true;
}

bool WindowTest::OnEvent(const SDL_Event& event)
{
    return Window::OnEvent(event);
}

void WindowTest::OnIdle()
{
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
