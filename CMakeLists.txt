cmake_minimum_required(VERSION 3.15)

# some standard cmake settings
project(CelestiaCore C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Binary & Library Output Locations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/libs)

# compile all .cpp files in the src folder
file(GLOB_RECURSE SOURCES "src/*.cpp")

# set up glad
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
set_source_files_properties(${GLAD_SRC} PROPERTIES LANGUAGE C)

add_subdirectory(lib/sdl3 EXCLUDE_FROM_ALL)
add_subdirectory(lib/sdl3_image EXCLUDE_FROM_ALL)


add_executable(CelestiaCore ${SOURCES} ${GLAD_SRC})

target_include_directories(CelestiaCore PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(CelestiaCore PRIVATE SDL3_image::SDL3_image SDL3::SDL3)

# set library and if not there create libs folder
set(LIB_DEST ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/libs)
file(MAKE_DIRECTORY ${LIB_DEST})

# find libraries
get_target_property(SDL3_LIB SDL3::SDL3 IMPORTED_LOCATION)
get_target_property(SDL3_IMAGE_LIB SDL3_image::SDL3_image IMPORTED_LOCATION)

# copy lib data into the libs folder
if(SDL3_LIB AND SDL3_IMAGE_LIB)
    add_custom_command(TARGET CelestiaCore POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL3_LIB} ${LIB_DEST}
        COMMAND ${CMAKE_COMMAND} -E copy ${SDL3_IMAGE_LIB} ${LIB_DEST}
    )
endif()

# set RPATH, so the binary file can actually find the libraries in the libs folder
set_target_properties(CelestiaCore PROPERTIES
    INSTALL_RPATH "$ORIGIN/libs"
)