#ifndef WINDOW_SDLGL_H
#define WINDOW_SDLGL_H

// clang-format off
#include <iostream>
#include <string>

#include <glad/glad.h>
#include <SDL3/SDL.h>

// clang-format on
class WindowSDLGL {

public:
  WindowSDLGL(const std::string &title, const std::string &version,
              unsigned int width, unsigned int height, bool resizable);
  ~WindowSDLGL();

  SDL_Window *getSDLGLWindow() const { return window; }
  SDL_GLContext getGLContext() const { return glContext; }

private:
  SDL_Window *window;
  SDL_GLContext glContext;
};

#endif