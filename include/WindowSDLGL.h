#pragma once

#include "EventBus.h"
#include "Events.h"

/**
 *
 * This class is responible for creating a window context, as well the
 * openGL/glad context. It also stores width/height information. So the
 * dimensions
 */

class WindowSDLGL {

public:
  WindowSDLGL(const std::string &title, const std::string &version,
              EventBus &eventBus, unsigned int initialWidth = 1920,
              unsigned int initialHeight = 1080);
  ~WindowSDLGL();

  SDL_Window *getSDLGLWindow() const { return window; }
  SDL_GLContext getGLContext() const { return glContext; }

  int getWidth() const { return width; }
  int getHeight() const { return height; }

  void publishCurrentWindowSize();

private:
  EventBus &eventBus;
  SDL_Window *window;
  SDL_GLContext glContext;
  // standard values
  int width;
  int height;

  bool mouseVisible = false;
  bool windowIsMaximized = false;

  void handleMouseVisibity(unsigned int width, unsigned int height);
  void handleWindowResize(unsigned int width, unsigned int height);
  void handleMaximizeWindow();
};
