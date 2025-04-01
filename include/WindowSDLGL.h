#ifndef WINDOW_SDLGL_H
#define WINDOW_SDLGL_H

// clang-format off
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>

// clang-format on
class WindowSDLGL {

public:
  WindowSDLGL(const std::string &title, const std::string &version,
              unsigned int width = 800, unsigned int height = 600,
              bool show_dearImgui_window = true);
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
  unsigned int width = 800;
  unsigned int height = 600;
};

#endif