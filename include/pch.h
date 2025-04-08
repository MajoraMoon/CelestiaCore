#pragma once

// Standard Library
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// OpenGL
#include <glad/glad.h>

// SDL3
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Enable overloaded mathematical operators for ImVec2 and ImVec4 types in Dear
// ImGui.
#define IMGUI_DEFINE_MATH_OPERATORS

// Indicate the use of a custom OpenGL loader with Dear ImGui's OpenGL backend.
// This prevents conflicts by ensuring ImGui does not include its own loader.

// Both is needed, so precompiled headers can work
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

// Dear ImGui
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <imgui_internal.h>
