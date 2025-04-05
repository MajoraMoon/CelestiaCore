#include "InputManager.h"

InputManager::InputManager(FrameTimer &frameTimer) : frameTimer(frameTimer) {}

// main sdl Events
void InputManager::processEvent(const SDL_Event &event, WindowSDLGL &window) {

  if (event.type == SDL_EVENT_QUIT ||
      (event.type == SDL_EVENT_KEY_DOWN && event.key.key == CLOSE_PROGRAM)) {

    quitRequested = true;
  }

  if (event.type == SDL_EVENT_MOUSE_MOTION) {
    mouseXRel += event.motion.xrel;
    mouseYRel += event.motion.yrel;
  }

  if (event.type == SDL_EVENT_MOUSE_WHEEL) {
    scrollY += event.wheel.y;
  }

  switch (event.type) {
  case SDL_EVENT_KEY_DOWN:
    if (event.key.scancode < SDL_SCANCODE_COUNT) {
      keys[event.key.scancode] = true;
    }
    break;
  case SDL_EVENT_KEY_UP:
    if (event.key.scancode < SDL_SCANCODE_COUNT) {
      keys[event.key.scancode] = false;
    }
    break;
  }
}

void InputManager::updateCamera(Camera &camera) {
  // Keyboard
  if (keys[SDL_SCANCODE_W])
    camera.processKeyboard(FORWARD, frameTimer.getDeltaTime());
  if (keys[SDL_SCANCODE_S])
    camera.processKeyboard(BACKWARD, frameTimer.getDeltaTime());
  if (keys[SDL_SCANCODE_A])
    camera.processKeyboard(LEFT, frameTimer.getDeltaTime());
  if (keys[SDL_SCANCODE_D])
    camera.processKeyboard(RIGHT, frameTimer.getDeltaTime());

  // Mouse
  if (mouseXRel != 0 || mouseYRel != 0) {
    camera.processMouseMovement(mouseXRel, -mouseYRel);
    mouseXRel = mouseYRel = 0;
  }
  if (scrollY != 0) {
    camera.processMouseScroll(scrollY);
    scrollY = 0;
  }
}