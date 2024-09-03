set(WINDOWTEST_SOURCE_FILES
    main.cpp
    WindowTest.h
    WindowTest.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${WINDOWTEST_SOURCE_FILES})

add_executable(WindowTest ${WINDOWTEST_SOURCE_FILES})

target_link_libraries(WindowTest PRIVATE sdlpp)

set_target_properties(WindowTest PROPERTIES
    FOLDER "samples"
    VS_DPI_AWARE "PerMonitor"
)

add_custom_command(TARGET WindowTest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:WindowTest> $<TARGET_FILE_DIR:WindowTest>
    COMMAND_EXPAND_LISTS
)
