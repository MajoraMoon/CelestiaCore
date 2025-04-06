#pragma once

// clang-format off
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

/**
 * 
 * This class is responible for creating a window context, as well the openGL/glad context.
 * It also stores width/height information. So the dimensions
 */

// clang-format on
class WindowSDLGL {

public:
  WindowSDLGL(const std::string &title, const std::string &version,
              unsigned int width = 1920, unsigned int height = 1080);
  ~WindowSDLGL();

  SDL_Window *getSDLGLWindow() const { return window; }
  SDL_GLContext getGLContext() const { return glContext; }

  unsigned int getSDLGLWindowHeight() const { return height; }
  unsigned int getSDLGLWindowWidth() const { return width; }

  void setSDLGLWindowSize(unsigned int newWidth, unsigned int newHeight) {
    width = newWidth;
    height = newHeight;
  }

private:
  SDL_Window *window;
  SDL_GLContext glContext;
  // standard values
  unsigned int width = 1920;
  unsigned int height = 1080;
};
