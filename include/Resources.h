#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

// clang-format off

/**
 * 
 * Just a single header to load a single function without any class.
 * It is using SDL3_image to load images and textures
 * 
 */

// clang-format on
unsigned char *loadImage(const char *filePath, int *width, int *height,
                         bool flipHorizontally = false,
                         bool flipVertically = false);
