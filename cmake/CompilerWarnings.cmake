# re_set_warnings(<target>)
#
# Applies a strict but practical warning set to first-party targets only.
# Third-party code (glad / glfw / glm / spdlog) is left untouched.
function(re_set_warnings TARGET)
    if(MSVC)
        target_compile_options(${TARGET} PRIVATE
            /W4
            /permissive-
            /Zc:__cplusplus
            /Zc:preprocessor
            /utf-8
            /wd4100   # unreferenced formal parameter
        )
    else()
        target_compile_options(${TARGET} PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wshadow
            -Wnon-virtual-dtor
            -Wno-unused-parameter
        )
    endif()
endfunction()
