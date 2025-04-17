cmake_minimum_required(VERSION 3.16)

# some standard cmake settings
project(CelestiaCore C CXX)


# default build type to Release with Debug Info
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Common GCC/Clang flags
    add_compile_options(
        -O3
        -march=native
        -Wall
    )
    
    add_link_options(
        -Wl,--gc-sections
    )

endif()



# Binary & Library Output Locations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/libs)

# SDL configuration
set(SDL_SHARED ON CACHE BOOL "Build SDL as shared library" FORCE)
set(SDL_STATIC OFF CACHE BOOL "Disable static SDL" FORCE)
set(SDL_IMAGE_SHARED ON CACHE BOOL "Build SDL_image as shared" FORCE)
set(SDL_TESTS OFF CACHE BOOL "Disable SDL tests" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "Disable SDL examples" FORCE)


set(ASSIMP_BUILD_TESTS OFF)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_DOCS OFF)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF)
set(ASSIMP_BUILD_SAMPLES OFF)
set(ASSIMP_BUILD_ZLIB ON)            # <— zlib aus Assimp-Contrib wird jetzt mitgebaut
set(ASSIMP_BUILD_DRACO OFF)

set(ASSIMP_BUILD_OBJ_IMPORTER ON)
set(ASSIMP_BUILD_FBX_IMPORTER ON)
set(ASSIMP_BUILD_GLTF_IMPORTER ON)

add_subdirectory(lib/sdl3 EXCLUDE_FROM_ALL)
add_subdirectory(lib/sdl3_image EXCLUDE_FROM_ALL)
add_subdirectory(lib/assimp EXCLUDE_FROM_ALL)


# compile all .cpp files in the src folder
file(GLOB_RECURSE SOURCES "src/*.cpp")

# set up glad
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
set_source_files_properties(${GLAD_SRC} PROPERTIES LANGUAGE C)



file(GLOB IMGUI_SOURCES 
    ${CMAKE_SOURCE_DIR}/lib/imgui/*.cpp
    ${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_sdl3.cpp
    ${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp
)


add_executable(CelestiaCore ${SOURCES} ${GLAD_SRC} ${IMGUI_SOURCES})

target_precompile_headers(CelestiaCore PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:${CMAKE_SOURCE_DIR}/include/pch.h>
)



target_include_directories(CelestiaCore PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib/imgui
    ${CMAKE_SOURCE_DIR}/lib/imgui/backends
    ${CMAKE_SOURCE_DIR}/lib/glm
    ${CMAKE_SOURCE_DIR}/lib/assimp/include
)

target_link_libraries(CelestiaCore PRIVATE 
    SDL3::SDL3
    SDL3_image::SDL3_image
    assimp::assimp
)

# put lib data into a libs folder to make everything cleaner on linux builds. Windows gets the standard treatment
# That means, all the dll files are at the same directory as the executable
if(WIN32)
    # Windows DLL Deployment
    add_custom_command(TARGET CelestiaCore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL3::SDL3> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL3_image::SDL3_image> ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        COMMENT "Copying DLLs to output directory"
    )

elseif(UNIX)

    # Linux library handling
    set(LIB_DEST ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs)
    file(MAKE_DIRECTORY ${LIB_DEST})

    add_custom_command(TARGET CelestiaCore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL3::SDL3> ${LIB_DEST}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL3_image::SDL3_image> ${LIB_DEST}
        COMMENT "Copying shared libraries to libs directory"
    )
    
    set_target_properties(CelestiaCore PROPERTIES
        INSTALL_RPATH "$ORIGIN/libs"
        BUILD_RPATH "${LIB_DEST}"
    )

endif()

