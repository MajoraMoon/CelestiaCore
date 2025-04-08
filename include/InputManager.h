#pragma once

// clang-format off

#include "Camera.h"
#include "WindowSDLGL.h"
#include "FrameTimer.h"
#include "GuiManager.h"

// clang-format on

/**
 *
 * This class is responsible to process the keyboard/mouse input using SDL3.
 *
 */

class InputManager {

public:
  InputManager(WindowSDLGL &window, FrameTimer &frameTimer,
               GuiManager &guiManager);

  void processEvent(const SDL_Event &event, WindowSDLGL &window);
  void updateCamera(Camera &camera);

  void toggleMouseVisibility() { mouseVisibility = !mouseVisibility; }
  void toggleWindowIsMaximized() { windowIsMaximized = !windowIsMaximized; }

  // state tracking
  bool quitRequested = false;

private:
  FrameTimer &frameTimer;
  GuiManager &guiManager;
  WindowSDLGL &window;

  // SDL keycodes for input behaviour
  const SDL_Keycode CLOSE_PROGRAM = SDLK_ESCAPE;
  const SDL_Keycode TOGGLE_GUI = SDLK_F1;
  const SDL_Keycode TOGGLE_MOUSE = SDLK_M;
  const SDL_Keycode MAXIMIZE_WINDOW = SDLK_F;

  const SDL_Scancode MOVE_FRONT = SDL_SCANCODE_W;
  const SDL_Scancode MOVE_BACK = SDL_SCANCODE_S;
  const SDL_Scancode MOVE_LEFT = SDL_SCANCODE_A;
  const SDL_Scancode MOVE_RIGHT = SDL_SCANCODE_D;
  const SDL_Scancode MOVE_UP = SDL_SCANCODE_SPACE;
  const SDL_Scancode MOVE_DOWN = SDL_SCANCODE_LCTRL;
  const SDL_Scancode MOVE_FAST = SDL_SCANCODE_LSHIFT;

  // Camera movement
  bool keys[SDL_SCANCODE_COUNT] = {false};
  float mouseXRel = 0;
  float mouseYRel = 0;
  float scrollY = 0;
  bool mouseVisibility = false;
  bool windowIsMaximized = false;

  // Input functions

  void handleWindowResize(int width, int height);
  void handleMouseVisibity(SDL_Window *window, int width, int height);
  void handleMaximizeWindow(SDL_Window *window);
};
