#ifndef RESOURCES_H
#define RESOURCES_H

// clang-format off

#include <cstdio>
#include <cstdlib>
#include <string>

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// clang-format on
unsigned char *loadImage(const char *filePath, int *width, int *height);

#endif