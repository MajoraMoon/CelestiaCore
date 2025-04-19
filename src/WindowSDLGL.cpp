// clang-format off
#include "pch.h"
#include "WindowSDLGL.h"
// clang-format on

namespace Celestia {

WindowSDLGL::WindowSDLGL(const std::string &title, const std::string &version,
                         EventBus &eventBus, unsigned int initialWidth,
                         unsigned int initialHeight)
    : eventBus(eventBus), m_width(initialWidth), m_height(initialHeight) {

  // Metadata is new in SDL3, why not using it :)
  SDL_SetAppMetadata(title.c_str(), version.c_str(), nullptr);

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    std::cerr << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    window = nullptr;
    glContext = nullptr;
    return;
  }

  // OpenGL-context attribute set up
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // instead of creating a window with properties directly, using the more
  // modular approach here.
  SDL_PropertiesID props = SDL_CreateProperties();
  if (props == 0) {
    std::cerr << "Unable to create properties: " << SDL_GetError() << std::endl;
    window = nullptr;
    glContext = nullptr;
    return;
  }

  SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING,
                        title.c_str());
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, m_width);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, m_height);
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);
  SDL_SetBooleanProperty(
      props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true);

  window = SDL_CreateWindowWithProperties(props);
  if (window == nullptr) {
    // idk which error log feature is actually better to use
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Could not initiate Window with custom wayland context: %s\n",
                 SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    glContext = nullptr;
    return;
  }

  SDL_GetWindowSize(window, &m_width, &m_height);

  glContext = SDL_GL_CreateContext(window);
  if (!glContext) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Could not create OpenGL context: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    glContext = nullptr;
    return;
  }

  // init glad
  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    std::cerr << "Could not load glad." << std::endl;
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    glContext = nullptr;
    window = nullptr;
    return;
  }

  glViewport(0, 0, m_width, m_height);

  if (!SDL_SetWindowRelativeMouseMode(window, true)) {

    std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
              << std::endl;
  }

  setupEventSubscriptions();
}

WindowSDLGL::~WindowSDLGL() {

  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_Log("Quitted successfully");
}

void WindowSDLGL::handleMouseVisibity(unsigned int width, unsigned int height) {

  // invert  boolean values.
  // mouseEvent says: mouse not visible? then false. mouse visible: then true.
  bool relativeMode = !m_mouseVisible;

  if (!SDL_SetWindowRelativeMouseMode(window, relativeMode)) {
    std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
              << std::endl;
  }

  // when entering the mouse mode or camera mode, will be placed at the
  // center of the window
  SDL_WarpMouseInWindow(window, width / 2, height / 2);
}

void WindowSDLGL::handleWindowResize(unsigned int width, unsigned int height) {

  // ensure that the dimensions are set. Sometimes it does not set itself
  // without telling it specifically
  this->m_width = width;
  this->m_height = height;
  glViewport(0, 0, width, height);
}

void WindowSDLGL::handleMaximizeWindow() {

  // invert  boolean values again
  bool shouldRestore = !m_windowIsMaximized;

  if (shouldRestore) {
    // Restore window before resizing
    if (!SDL_RestoreWindow(window)) {
      std::cerr << "Could not restore window properties: " << SDL_GetError()
                << std::endl;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindow(window);
    SDL_Rect usableBounds;
    if (!SDL_GetDisplayUsableBounds(displayID, &usableBounds)) {
      std::cerr << "Could not detect usable desktop area: " << SDL_GetError()
                << std::endl;
    } else {
      int newWidth = usableBounds.w / 2;
      int newHeight = usableBounds.h / 2;

      SDL_SetWindowSize(window, newWidth, newHeight);

      int posX = usableBounds.x + (usableBounds.w - newWidth) / 2;
      int posY = usableBounds.y + (usableBounds.h - newHeight) / 2;
      SDL_SetWindowPosition(window, posX, posY);
    }
  } else {
    if (!SDL_MaximizeWindow(window)) {
      std::cerr << "Unable to maximize window: " << SDL_GetError() << std::endl;
    }
  }
}

void WindowSDLGL::publishCurrentWindowSize() {
  eventBus.publish(WindowResizeEvent(m_width, m_height));
}

void WindowSDLGL::setupEventSubscriptions() {
  eventBus.subscribe<WindowResizeEvent>([this](const WindowResizeEvent &ev) {
    m_width = ev.width;
    m_height = ev.height;

    handleWindowResize(m_width, m_height);
  });

  eventBus.subscribe<MouseVisibilityChanged>(
      [this](const MouseVisibilityChanged &ev) {
        m_mouseVisible = ev.visible;
        handleMouseVisibity(m_width, m_height);
      });

  eventBus.subscribe<WindowMaximizedChanged>(
      [this](const WindowMaximizedChanged &ev) {
        m_windowIsMaximized = ev.maximized;
        handleMaximizeWindow();
      });
}

} // namespace Celestia
