#pragma once

/**
 *
 * This class is responible for creating a window context, as well the
 * openGL/glad context. It also stores width/height information. So the
 * dimensions
 */

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
