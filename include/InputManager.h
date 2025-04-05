#pragma once

// clang-format off
#include <SDL3/SDL.h>

#include "Camera.h"
#include "WindowSDLGL.h"
#include "FrameTimer.h"

// clang-format on

class InputManager {

public:
  InputManager(FrameTimer &frameTimer);

  void processEvent(const SDL_Event &event, WindowSDLGL &window);
  void updateCamera(Camera &camera);

  // state tracking
  bool quitRequested = false;
  bool uiVisible = true;

private:
  FrameTimer &frameTimer;

  // Camera movement
  bool keys[SDL_SCANCODE_COUNT] = {false};
  float mouseXRel = 0;
  float mouseYRel = 0;
  float scrollY = 0;

  // SDL keycodes for input behaviour
  const SDL_Keycode CLOSE_PROGRAM = SDLK_ESCAPE;
};
