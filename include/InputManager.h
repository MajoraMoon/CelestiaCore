#pragma once

/**
 *
 * This class is responsible to process the keyboard/mouse input using SDL3.
 *
 */

class EventBus;

class InputManager {

public:
  InputManager(EventBus &eventBus);

  void processEvent(const SDL_Event &event);

private:
  EventBus &eventBus;

  // SDL keycodes for input behaviour
  const SDL_Keycode CLOSE_PROGRAM = SDLK_ESCAPE;
  const SDL_Keycode TOGGLE_GUI = SDLK_F1;
  const SDL_Keycode TOGGLE_MOUSE = SDLK_M;
  const SDL_Keycode MAXIMIZE_WINDOW = SDLK_F;
  const SDL_Keycode PAUSE = SDLK_P;
};
