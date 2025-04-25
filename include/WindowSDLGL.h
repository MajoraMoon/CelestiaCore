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
              EventBus &eventBus);
  ~WindowSDLGL();

  void publishCurrentWindowSize();

  SDL_Window *getSDLGLWindow() const { return m_window; }
  SDL_GLContext getGLContext() const { return m_glContext; }

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

private:
  EventBus &eventBus;
  SDL_Window *m_window = nullptr;
  SDL_GLContext m_glContext = nullptr;

  void initializeSDL();
  void createWindow();
  void createGLContext();
  void initializeGlad();
  void initializeState();

  // Event handlers
  void setupEventSubscriptions();
  void handleMouseVisibity();
  void handleWindowResize(unsigned int width, unsigned int height);
  void handleMaximizeWindow();
  void handleFullscreenMode();
  void handleVsyncMode();

  bool m_mouseVisible;
  bool m_windowIsMaximized;
  bool m_windowFullscreen;
  bool m_vsyncMode;

  int m_width = 1920;
  int m_height = 1080;

  std::string m_videoDriver = "";
  std::string m_title = "";
  std::string m_version = "";

  // Fullscreen mode member variables
  int m_prevWidth = 0;
  int m_prevHeight = 0;
  int m_prevX = 0;
  int m_prevY = 0;
};

} // namespace Celestia
