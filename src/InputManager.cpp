#include "InputManager.h"

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

void InputManager::updateCamera(Camera &camera, float deltaTime) {
  // Keyboard
  if (keys[SDL_SCANCODE_W])
    camera.processKeyboard(FORWARD, deltaTime);
  if (keys[SDL_SCANCODE_S])
    camera.processKeyboard(BACKWARD, deltaTime);
  if (keys[SDL_SCANCODE_A])
    camera.processKeyboard(LEFT, deltaTime);
  if (keys[SDL_SCANCODE_D])
    camera.processKeyboard(RIGHT, deltaTime);

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