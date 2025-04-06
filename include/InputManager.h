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
  InputManager(FrameTimer &frameTimer, GuiManager &guiManager);

  void processEvent(const SDL_Event &event, WindowSDLGL &window);
  void updateCamera(Camera &camera);

  // state tracking
  bool quitRequested = false;
  bool uiVisible = true;

private:
  FrameTimer &frameTimer;
  GuiManager &guiManager;

  // Camera movement
  bool keys[SDL_SCANCODE_COUNT] = {false};
  float mouseXRel = 0;
  float mouseYRel = 0;
  float scrollY = 0;

  // SDL keycodes for input behaviour
  const SDL_Keycode CLOSE_PROGRAM = SDLK_ESCAPE;
  const SDL_Keycode TOGGLE_GUI = SDLK_F1;
};
