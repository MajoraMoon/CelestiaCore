#ifndef WINDOW_SDLGL_H
#define WINDOW_SDLGL_H

#include <iostream>
#include <string>

#include <SDL3/SDL.h>
#include <glad/glad.h>

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