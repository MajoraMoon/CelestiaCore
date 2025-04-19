#pragma once

/**
 *
 * This class is responible for creating a window context, as well the
 * openGL/glad context. It also stores width/height information. So the
 * dimensions
 */

namespace Celestia {

// forward declarations
class EventBus;

class WindowSDLGL {

public:
  WindowSDLGL(const std::string &title, const std::string &version,
              EventBus &eventBus, unsigned int initialWidth = 1920,
              unsigned int initialHeight = 1080);
  ~WindowSDLGL();

  SDL_Window *getSDLGLWindow() const { return window; }
  SDL_GLContext getGLContext() const { return glContext; }

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

  void publishCurrentWindowSize();

  enum class FullscreenMode { Windowed, Fullscreen, Borderless };

  void setFullscreenMode(FullscreenMode mode);
  FullscreenMode getFullscreenMode() const { return windowState.currentMode; }

private:
  EventBus &eventBus;
  SDL_Window *window;
  SDL_GLContext glContext;

  int m_width;
  int m_height;

  bool m_mouseVisible;
  bool m_windowIsMaximized;

  void handleMouseVisibity(unsigned int width, unsigned int height);
  void handleWindowResize(unsigned int width, unsigned int height);
  void handleMaximizeWindow();

  void setupEventSubscriptions();

  struct WindowState {
    FullscreenMode currentMode = FullscreenMode::Windowed;
    int prevWidth = 0;
    int prevHeight = 0;
    int prevX = 0;
    int prevY = 0;
  };

  WindowState windowState;
};

} // namespace Celestia
