#include <WindowSDLGL.h>

WindowSDLGL::WindowSDLGL(const std::string &title, const std::string &version,
                         unsigned int width, unsigned int height,
                         bool resizable) {

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
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN,
                         resizable);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, width);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, height);
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);

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
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    glContext = nullptr;
    window = nullptr;
    return;
  }
}

WindowSDLGL::~WindowSDLGL() {

  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_Log("Quitted successfully");
}
