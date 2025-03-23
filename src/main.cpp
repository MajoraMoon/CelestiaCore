// clang-format off

#include <iostream>

#include <SDL3/SDL.h>

#include "FrameTimer.h"
#include "Renderer.h"
#include "WindowSDLGL.h"

// clang-format on

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

int main(int argc, char *argv[]) {

  WindowSDLGL window("LunaCore", "0.1", SCR_WIDTH, SCR_HEIGHT, true);

  if (!window.getSDLGLWindow() || !window.getGLContext()) {
    std::cerr << "Failed to initialize Window or OpenGL context." << std::endl;

    return -1;
  }

  Renderer renderer;
  FrameTimer frameTimer;

  bool running = true;
  SDL_Event event;

  // main loop
  while (running) {
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

    frameTimer.update();
    renderer.renderFrame(SCR_WIDTH, SCR_HEIGHT);
    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }

  return 0;
}
