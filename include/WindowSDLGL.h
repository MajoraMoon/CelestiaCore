#pragma once

namespace Celestia {

class EventBus;
class AppState;

/**
 * @class WindowSDLGL
 * @brief Manages SDL window creation, window-event related functions and OpenGL
 * context initialization.
 *
 * Handles window lifecycle, display mode changes (e.g. fullscreen/windowed),
 * and GL context management. Publishes window-related events through EventBus.
 *
 *@note Uses SDL3 properties system for window configuration
 */
class WindowSDLGL {

public:
  WindowSDLGL(const std::string &title, const std::string &version,
              EventBus &eventBus, AppState &appState);
  ~WindowSDLGL();

  SDL_Window *getSDLGLWindow() const { return m_window; }
  SDL_GLContext getGLContext() const { return m_glContext; }

  int getWidth() const { return m_width; }
  int getHeight() const { return m_height; }

private:
  EventBus &eventBus;
  AppState &appState;
  SDL_Window *m_window = nullptr;
  SDL_GLContext m_glContext = nullptr;

  /**
   * @brief Initializes SDL video subsystem and application metadata
   * @throws std::runtime_error If SDL initialization fails
   */
  void initializeSDL();

  /**
   * @brief Creates a SDL Window with standard properties
   * @throws std::runtime_error If Window creation with SDL_Properties fails
   */
  void createWindow();
  void createGLContext();
  void initializeGlad();

  /**
   * @brief Sets some initial values afte being called in the constructor
   */
  void initializeState();

  //------------------------------------------------------------------------------
  //
  // Event Subscription Setup
  //
  //------------------------------------------------------------------------------
  void setupEventSubscriptions();
  void handleMouseVisibity(bool visible);
  void handleWindowResize(unsigned int width, unsigned int height);
  void handleMaximizeWindow(bool maximized);
  void handleFullscreenMode(bool fullscreen);
  void handleVsyncMode(bool vsync);

  // start resolution initialized here, not in the AppState
  // Although it is set in the class creation, it throws errors
  int m_width = 1280;
  int m_height = 720;

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
