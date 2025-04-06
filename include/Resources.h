#pragma once
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
