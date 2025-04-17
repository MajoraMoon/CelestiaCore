#pragma once

/**
 *
 * Just a single header to load a single function without any class.
 * It is using SDL3_image to load images and textures
 *
 */

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

unsigned char *loadImage(const char *filePath, int *width, int *height,
                         bool flipHorizontally = false,
                         bool flipVertically = false);
