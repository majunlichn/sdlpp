#pragma once

#include <sdlpp/Gui/Window.h>
#include <sdlpp/Gui/Renderer.h>

class WindowTest : public sdl::Window
{
public:
    WindowTest();
    ~WindowTest();

    bool Init();

protected:
    virtual bool OnEvent(const SDL_Event& event) override;
    virtual void OnIdle() override;

    // Window events:
    virtual void OnShown() override;
    virtual void OnHidden() override;
    virtual void OnExposed() override;
    virtual void OnMoved(int x, int y) override;
    virtual void OnResized(int width, int height) override;
    virtual void OnPixelSizeChanged(int width, int height) override;
    virtual void OnMinimized() override;
    virtual void OnMaximized() override;
    virtual void OnRestored() override;
    virtual void OnMouseEnter() override;
    virtual void OnMouseLeave() override;
    // Window has gained keyboard focus.
    virtual void OnFocusGained() override;
    // Window has lost keyboard focus.
    virtual void OnFocusLost() override;
    virtual void OnCloseRequested() override;
    virtual void OnHitTest() override;
    virtual void OnIccProfileChanged() override;
    virtual void OnDisplayChanged() override;
    virtual void OnDisplayScaleChanged() override;
    virtual void OnOccluded() override;
    virtual void OnEnterFullscreen() override;
    virtual void OnLeaveFullscreen() override;
    virtual void OnDestroyed() override;

    // Keyboard events:
    virtual void OnKeyDown(const SDL_KeyboardEvent& keyDown) override;
    virtual void OnKeyUp(const SDL_KeyboardEvent& keyUp) override;
    virtual void OnTextEditing(const SDL_TextEditingEvent& textEditing) override;
    virtual void OnTextInput(const SDL_TextInputEvent& textInput) override;

    // Mouse events:
    virtual void OnMouseMove(const SDL_MouseMotionEvent& mouseMotion) override;
    virtual void OnMouseButtonDown(const SDL_MouseButtonEvent& mouseButton) override;
    virtual void OnMouseButtonUp(const SDL_MouseButtonEvent& mouseButton) override;
    virtual void OnMouseWheel(const SDL_MouseWheelEvent& mouseWheel) override;

    // User
    virtual void OnUserEvent(const SDL_UserEvent& user) override;


private:
    const char* GetMouseButtonName(Uint8 button);

    std::shared_ptr<spdlog::logger> m_logger;

}; // class WindowTest
