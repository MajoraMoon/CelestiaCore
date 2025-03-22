#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <iostream>

int main(int argc, char const *argv[]) {

  SDL_SetAppMetadata("CelestiaCore", "0.1", NULL);

  if (!SDL_Init(SDL_INIT_VIDEO)) {

    SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

    return -1;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // instead of creating a window with properties directly, using the more
  // modular approach here.
  SDL_PropertiesID props = SDL_CreateProperties();
  if (props == 0) {
    SDL_Log("Unable to create properties: %s", SDL_GetError());

    return -1;
  }

  SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING,
                        "CelestiaCore");
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_WIDTH_NUMBER, 1920);
  SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_HEIGHT_NUMBER, 1080);
  SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_OPENGL_BOOLEAN, true);

  SDL_Window *window = SDL_CreateWindowWithProperties(props);

  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Could not initiate Window context: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();

    return -1;
  }

  SDL_GLContext glContext = SDL_GL_CreateContext(window);

  if (!glContext) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "Could not create OpenGL context: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return -1;
  }

  bool running = true;

  while (running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }

      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_ESCAPE) {
          running = false;
        }
      }
    }

    SDL_GL_SwapWindow(window);
  }

  SDL_GL_DestroyContext(glContext);
  SDL_DestroyWindow(window);
  SDL_Quit();
  SDL_Log("Quitted successfully");

  return 0;
}
