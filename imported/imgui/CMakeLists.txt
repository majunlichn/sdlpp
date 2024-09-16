set(IMGUI_SOURCE_FILES
    imconfig.h
    imgui.cpp
    imgui.h
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    implot
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    backends/imgui_impl_sdl3.cpp
    backends/imgui_impl_sdl3.h
    backends/imgui_impl_sdlrenderer3.cpp
    backends/imgui_impl_sdlrenderer3.h
    implot/implot.cpp
    implot/implot.h
    implot/implot_demo.cpp
    implot/implot_internal.h
    implot/implot_items.cpp
)

if (DEFINED VULKAN_INCLUDE_DIR)
    list(APPEND IMGUI_SOURCE_FILES
        backends/imgui_impl_vulkan.cpp
        backends/imgui_impl_vulkan.h
    )
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${IMGUI_SOURCE_FILES})

add_library(imgui
    ${IMGUI_SOURCE_FILES}
)

target_include_directories(imgui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(imgui
    PUBLIC SDL3::SDL3
)

if (DEFINED VULKAN_INCLUDE_DIR)
    target_include_directories(imgui
        PUBLIC ${VULKAN_INCLUDE_DIR}
    )
endif()

set_target_properties(imgui PROPERTIES
    FOLDER "imported"
)
