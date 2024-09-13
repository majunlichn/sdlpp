set(SDLPP_SOURCE_FILES
    Core/Application.h
    Core/Application.cpp
    Core/EventHandler.h
    Core/EventHandler.cpp
    Core/Logging.h
    Core/Logging.cpp
    Core/ErrorHandling.h
    Core/ErrorHandling.cpp
    Core/Timer.h
    Core/Timer.cpp
    Core/Power.h
    Core/Power.cpp
    Gui/Window.h
    Gui/Window.cpp
    Gui/Renderer.h
    Gui/Renderer.cpp
    Gui/Surface.h
    Gui/Surface.cpp
    Gui/Texture.h
    Gui/Texture.cpp
    Gui/Image.h
    Gui/Image.cpp
    Gui/GuiContext.h
    Gui/GuiContext.cpp
    Media/Audio.h
    Media/Audio.cpp
    Media/AudioMixer.h
    Media/AudioMixer.cpp
    Media/Camera.h
    Media/Camera.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SDLPP_SOURCE_FILES})

add_library(sdlpp STATIC ${SDLPP_SOURCE_FILES})

target_include_directories(sdlpp
    PUBLIC ${SDLPP_ROOT}
    PUBLIC ${SDLPP_ROOT}/imported/radcpp
)

target_link_libraries(sdlpp
    PUBLIC rad
    PUBLIC SDL3::SDL3
    PUBLIC SDL3_mixer::SDL3_mixer
    PUBLIC imgui
)
