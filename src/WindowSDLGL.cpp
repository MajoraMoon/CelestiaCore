// clang-format off
#include "pch.h"
#include "WindowSDLGL.h"
#include "EventSystem.h"
// clang-format on

namespace Celestia {

WindowSDLGL::WindowSDLGL(const std::string &title, const std::string &version,
                         EventBus &eventBus, AppState &appState)
    : eventBus(eventBus), appState(appState), m_title(title),
      m_version(version) {

  // Note: Do not fuck with this Order here, it is important
  setupEventSubscriptions();
  initializeSDL();
  createWindow();
  createGLContext();
  initializeGlad();
  initializeState();
}

WindowSDLGL::~WindowSDLGL() {
  SDL_GL_DestroyContext(m_glContext);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
  SDL_Log("Quitted successfully");
}

void WindowSDLGL::initializeSDL() {

  // Metadata is new in SDL3, why not using it :)
  SDL_SetAppMetadata(m_title.c_str(), m_version.c_str(), nullptr);

  if (SDL_Init(SDL_INIT_VIDEO) == false) {

    throw std::runtime_error("SDL initialization failed: " +
                             std::string(SDL_GetError()));
  }
}

void WindowSDLGL::createWindow() {

  // instead of creating a window with properties directly, using the more
  // modular approach here.
  SDL_PropertiesID props = SDL_CreateProperties();
  if (props == 0) {

    throw std::runtime_error("Unable to create properties: " +
                             std::string(SDL_GetError()));
  }

  SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING,
                        m_title.c_str());
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, m_width);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, m_height);
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);
  SDL_SetBooleanProperty(
      props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true);

  m_window = SDL_CreateWindowWithProperties(props);
  if (m_window == nullptr) {

    // idk which error log feature is actually better to use
    throw std::runtime_error("Could not initiate Window: " +
                             std::string(SDL_GetError()));
  }
}

void WindowSDLGL::createGLContext() {

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  m_glContext = SDL_GL_CreateContext(m_window);
  if (!m_glContext) {
    throw std::runtime_error("OpenGL context creation failed: " +
                             std::string(SDL_GetError()));
  }
}

void WindowSDLGL::initializeGlad() {
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }
}

void WindowSDLGL::initializeState() {

  glViewport(0, 0, m_width, m_height);
  SDL_GetWindowSize(m_window, &m_width, &m_height);
  m_prevWidth = m_width;
  m_prevHeight = m_height;
  m_videoDriver = SDL_GetCurrentVideoDriver();

  handleMaximizeWindow(appState.window.maximized);
  handleMouseVisibity(appState.window.mouseVisibility);
  handleFullscreenMode(appState.window.fullscreen);
  handleVsyncMode(appState.window.vsync);
}

void WindowSDLGL::handleMouseVisibity(bool visible) {
  // invert  boolean values.
  // mouseEvent says: mouse not visible? then false. mouse visible: then true.
  bool relativeMode = !visible;

  if (!SDL_SetWindowRelativeMouseMode(m_window, relativeMode)) {
    std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
              << std::endl;
  }

  // when entering the mouse mode or camera mode, will be placed at the
  // center of the window
  SDL_WarpMouseInWindow(m_window, m_width / 2, m_height / 2);
}

void WindowSDLGL::handleWindowResize(unsigned int width, unsigned int height) {
  // ensure that the dimensions are set. Sometimes it does not set itself
  // without telling it specifically
  this->m_width = width;
  this->m_height = height;
  glViewport(0, 0, width, height);
}

void WindowSDLGL::handleMaximizeWindow(bool maximized) {
  if (maximized) {
    if (!SDL_MaximizeWindow(m_window)) {
      std::cerr << "Unable to maximize window: " << SDL_GetError() << std::endl;
    }
  } else {
    if (!SDL_RestoreWindow(m_window)) {
      std::cerr << "Could not restore window properties: " << SDL_GetError()
                << std::endl;
    }
  }
}

void WindowSDLGL::handleFullscreenMode(bool fullscreen) {
  bool isWayland = (m_videoDriver == "wayland");

  // set to fullscreen mode
  if (fullscreen) {

    SDL_GetWindowSize(m_window, &m_prevWidth, &m_prevHeight);
    if (!isWayland) {
      SDL_GetWindowPosition(m_window, &m_prevX, &m_prevY);
    }
    SDL_SetWindowFullscreen(m_window, true);
  } else
  // set to windowed mode
  {
    SDL_SetWindowFullscreen(m_window, false);

    if (isWayland) {
      SDL_SetWindowSize(m_window, m_prevWidth, m_prevHeight);
      SDL_SetWindowBordered(m_window, true);
    } else {
      SDL_SetWindowBordered(m_window, true);
      SDL_SetWindowSize(m_window, m_prevWidth, m_prevHeight);
      SDL_SetWindowPosition(m_window, m_prevX, m_prevY);
    }
  }

  eventBus.emit(WindowResizeEvent(m_width, m_height));
}

void WindowSDLGL::handleVsyncMode(bool vsync) {
  if (vsync) {
    std::cout << vsync << std::endl;
    SDL_GL_SetSwapInterval(1);
  } else {
    SDL_GL_SetSwapInterval(0);
  }
}

void WindowSDLGL::setupEventSubscriptions() {
  eventBus.on<WindowResizeEvent>([this](const auto &ev) {
    m_width = ev.width;
    m_height = ev.height;

    handleWindowResize(m_width, m_height);
  });

  eventBus.on<SetMouseVisibilityEvent>(
      [this](const auto &ev) { handleMouseVisibity(ev.visible); });

  eventBus.on<SetWindowMaximizedEvent>(
      [this](const auto &ev) { handleMaximizeWindow(ev.maximized); });

  eventBus.on<SetFullscreenModeEvent>(
      [this](const auto &ev) { handleFullscreenMode(ev.fullscreen); });

  eventBus.on<SetVsyncModeEvent>(
      [this](const auto &ev) { handleVsyncMode(ev.vsync); });
}

} // namespace Celestia
