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

  bool mouseIsVisible() const { return mouseVisibility; }

  SDL_Window *getSDLGLWindow() const { return window; }
  SDL_GLContext getGLContext() const { return glContext; }

  unsigned int getSDLGLWindowHeight() const { return height; }
  unsigned int getSDLGLWindowWidth() const { return width; }

private:
  EventBus &eventBus;
  SDL_Window *window;
  SDL_GLContext glContext;
  // standard values
  unsigned int width = 1920;
  unsigned int height = 1080;

  bool mouseVisibility = false;
  bool windowIsMaximized = false;

  void toggleMouseVisibility() { mouseVisibility = !mouseVisibility; }
  void toggleWindowIsMaximized() { windowIsMaximized = !windowIsMaximized; }

  void handleMouseVisibity(unsigned int width, unsigned int height);
  void handleWindowResize(unsigned int width, unsigned int height);
  void handleMaximizeWindow();
};
