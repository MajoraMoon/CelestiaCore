cmake_minimum_required(VERSION 3.15)

# some standard cmake settings
project(CelestiaCore C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Binary location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# compile all .cpp files in the src folder
file(GLOB_RECURSE SOURCES "src/*.cpp")

# set up glad
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
set_source_files_properties(${GLAD_SRC} PROPERTIES LANGUAGE C)

add_subdirectory(lib/sdl3 EXCLUDE_FROM_ALL)


add_executable(CelestiaCore ${SOURCES} ${GLAD_SRC})

target_include_directories(CelestiaCore PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(CelestiaCore PRIVATE SDL3::SDL3)