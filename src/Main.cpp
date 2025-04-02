// clang-format off

#include <iostream>

#include <SDL3/SDL.h>

#include "FrameTimer.h"
#include "Renderer.h"
#include "WindowSDLGL.h"
#include "GuiManager.h"

// clang-format on

int main(int argc, char *argv[]) {

  // the dear imgui window can be disabled too
  WindowSDLGL window("LunaCore", "0.1");

  if (!window.getSDLGLWindow() || !window.getGLContext()) {
    std::cerr << "Failed to initialize Window or OpenGL context." << std::endl;

    return -1;
  }

  SDL_Event event;
  FrameTimer frameTimer;
  Renderer renderer(frameTimer);
  GuiManager guiManager(window, frameTimer);

  bool running = true;
  // main loop
  while (running) {

    frameTimer.update();

    while (SDL_PollEvent(&event)) {
      guiManager.processGUIEvent(&event);

      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
        running = false;
      }
      // adjust the resolution to provide openGL correct data
      if (event.window.type == SDL_EVENT_WINDOW_RESIZED) {

        window.setSDLGLWindowSize(event.window.data1, event.window.data2);
      }
    }

    // acutal rendering in this single function. (making it more abstact later)
    renderer.renderFrame(window.getSDLGLWindowWidth(),
                         window.getSDLGLWindowHeight());

    // dear ImGui-rendering
    guiManager.newFrame();
    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }

  return 0;
}
