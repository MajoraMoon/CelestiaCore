// clang-format off
#include "pch.h"
#include "WindowSDLGL.h"
// clang-format on

WindowSDLGL::WindowSDLGL(const std::string &title, const std::string &version,
                         EventBus &eventBus, unsigned int initialWidth,
                         unsigned int initialHeight)
    : width(initialWidth), height(initialHeight), eventBus(eventBus) {

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
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
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

  SDL_GetWindowSize(window, &width, &height);

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

  glViewport(0, 0, width, height);

  if (!SDL_SetWindowRelativeMouseMode(window, true)) {

    std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
              << std::endl;
  }

  // Window Event subscriptions

  eventBus.subscribe<WindowResizeEvent>([this](const Event &e) {
    const auto &ev = static_cast<const WindowResizeEvent &>(e);
    width = ev.width;
    height = ev.height;

    handleWindowResize(width, height);
  });

  eventBus.subscribe<MouseVisibilityChanged>([this](const Event &e) {
    const auto &ev = static_cast<const MouseVisibilityChanged &>(e);

    mouseVisible = ev.mouseVisible;
    handleMouseVisibity(width, height);
  });

  eventBus.subscribe<WindowMaximizedChanged>([this](const Event &e) {
    const auto &ev = static_cast<const WindowMaximizedChanged &>(e);
    windowIsMaximized = ev.windowMaximized;
    handleMaximizeWindow();
  });
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
  bool relativeMode = !mouseVisible;

  if (!SDL_SetWindowRelativeMouseMode(window, relativeMode)) {
    std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
              << std::endl;
  }

  // when entering the mouse mode or camera mode, will be placed at the
  // center of the window
  SDL_WarpMouseInWindow(window, width / 2, height / 2);
}

void WindowSDLGL::handleWindowResize(unsigned int width, unsigned int height) {
  this->width = width;
  this->height = height;
  glViewport(0, 0, width, height);
}

void WindowSDLGL::handleMaximizeWindow() {

  // invert  boolean values again
  bool shouldRestore = !windowIsMaximized;

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
  eventBus.publish(WindowResizeEvent(width, height));
}