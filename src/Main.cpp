// clang-format off

#include <iostream>

#include <SDL3/SDL.h>

#include "FrameTimer.h"
#include "Renderer.h"
#include "WindowSDLGL.h"
#include "GuiManager.h"

// clang-format on

// Key bindings for better overview of their actual function
// (also easier to change if needed)
const SDL_Keycode CLOSE_PROGRAM = SDLK_ESCAPE;
const SDL_Keycode TOGGLE_UI_KEY = SDLK_F1;

int main(int argc, char *argv[]) {
  // the dear imgui window can be disabled too
  WindowSDLGL window("LunaCore", "0.1");

  if (!window.getSDLGLWindow() || !window.getGLContext()) {
    std::cerr << "Failed to initialize Window or OpenGL context." << std::endl;

    return -1;
  }

  SDL_SetWindowRelativeMouseMode(window.getSDLGLWindow(), true);

  SDL_Event event;
  FrameTimer frameTimer;
  Renderer renderer(frameTimer);
  GuiManager guiManager(window, frameTimer);

  bool running = true;
  // main loop
  while (running) {

    frameTimer.update();

    while (SDL_PollEvent(&event)) {
      if (guiManager.IsVisible()) {
        guiManager.processGUIEvent(&event);
      }

      if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN &&
                                           event.key.key == CLOSE_PROGRAM)) {
        running = false;
      }
      // adjust the resolution to provide openGL correct data
      if (event.window.type == SDL_EVENT_WINDOW_RESIZED) {

        window.setSDLGLWindowSize(event.window.data1, event.window.data2);
      }
      // main if statement for keys pressed down
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == TOGGLE_UI_KEY) {
          guiManager.toggleVisibility();
          SDL_SetWindowRelativeMouseMode(window.getSDLGLWindow(),
                                         guiManager.IsVisible() ? false : true);
        }
      }

      if (event.type == SDL_EVENT_MOUSE_MOTION) {
        renderer.getCamera().processMouseMovement(event.motion.xrel,
                                                  -event.motion.yrel);
      }

      if (event.type == SDL_EVENT_MOUSE_WHEEL) {
        renderer.getCamera().processMouseScroll(event.wheel.y);
      }
    }

    const bool *keyState = SDL_GetKeyboardState(nullptr);
    if (keyState[SDL_SCANCODE_W])
      renderer.getCamera().processKeyboard(FORWARD, frameTimer.getDeltaTime());
    if (keyState[SDL_SCANCODE_S])
      renderer.getCamera().processKeyboard(BACKWARD, frameTimer.getDeltaTime());
    if (keyState[SDL_SCANCODE_A])
      renderer.getCamera().processKeyboard(LEFT, frameTimer.getDeltaTime());
    if (keyState[SDL_SCANCODE_D])
      renderer.getCamera().processKeyboard(RIGHT, frameTimer.getDeltaTime());

    // acutal rendering in this single function.
    // (making it more abstact / efficient later maybe lol)
    renderer.renderFrame(window.getSDLGLWindowWidth(),
                         window.getSDLGLWindowHeight());

    // dear ImGui-rendering
    guiManager.newFrame();
    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }

  return 0;
}
