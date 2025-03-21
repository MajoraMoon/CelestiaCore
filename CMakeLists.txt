cmake_minimum_required(VERSION 3.15)

project(CelestiaCore C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

file(GLOB_RECURSE SOURCES "src/*.cpp")
set(GLAD_SRC ${CMAKE_SOURCE_DIR}/lib/glad/src/glad.c)
set_source_files_properties(${GLAD_SRC} PROPERTIES LANGUAGE C)


add_executable(CelestiaCore ${SOURCES} ${GLAD_SRC})

target_include_directories(CelestiaCore PRIVATE 
    ${CMAKE_SOURCE_DIR}/lib/glad/include
    ${CMAKE_SOURCE_DIR}/include
)