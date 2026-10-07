# ---------------------------------------------------------------------------
# Sandbox - a runnable demo application that links against the engine.
# ---------------------------------------------------------------------------

add_executable(Sandbox
    src/main.cpp
    src/SandboxApp.cpp)

target_include_directories(Sandbox PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(Sandbox PRIVATE RealEngine)

re_set_warnings(Sandbox)

# Keep runtime assets next to the executable so relative asset paths work from
# the build tree on both Windows and Linux.
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Assets
            $<TARGET_FILE_DIR:Sandbox>/Assets
    COMMENT "Copying Assets next to the Sandbox executable")
