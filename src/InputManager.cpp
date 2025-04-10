

// clang-format off
#include "pch.h"
#include "InputManager.h"
// clang-format on

InputManager::InputManager(EventBus &eventBus) : eventBus(eventBus) {}

// main sdl Events
void InputManager::processEvent(const SDL_Event &event) {

  if (event.type == SDL_EVENT_QUIT) {
    eventBus.publish(QuitEvent{});
  }

  if (event.type == SDL_EVENT_KEY_DOWN) {

    eventBus.publish(KeyEvent(event.key.scancode, true));

    switch (event.key.key) {
    case SDLK_ESCAPE:
      eventBus.publish(QuitEvent{});
      break;

    case SDLK_F1:
      eventBus.publish(ToggleGuiEvent{});
      break;

    case SDLK_M:
      eventBus.publish(ToggleMouseEvent{});
      break;

    case SDLK_F:
      eventBus.publish(MaximizeWindowEvent{});
      break;

    case SDLK_P:
      eventBus.publish(PauseEvent{});
      break;
    }
  }

  // Convert mouse events
  if (event.type == SDL_EVENT_MOUSE_MOTION && !mouseVisibility) {
    eventBus.publish(MouseMoveEvent{static_cast<float>(event.motion.xrel),
                                    static_cast<float>(event.motion.yrel)});
  }

  // Convert scroll events
  if (event.type == SDL_EVENT_MOUSE_WHEEL && !mouseVisibility) {
    eventBus.publish(MouseScrollEvent{static_cast<float>(event.wheel.y)});
  }
}
