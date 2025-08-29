// clang-format off
#include "pch.h"
#include "InputManager.h"
#include "EventSystem.h"
// clang-format on

namespace Celestia {

InputManager::InputManager(EventBus &eventBus, AppState &appState)
    : eventBus(eventBus), appState(appState) {}

void InputManager::processEvent(const SDL_Event &event) {

  if (event.type == SDL_EVENT_KEY_DOWN) {

    // continuous key input
    eventBus.emit(KeyEvent(event.key.scancode, true));

    switch (event.key.key) {

    // press Esc in fullscreen mode exit it
    case SDLK_ESCAPE:

      // if window in fullscreen then exit fullscreen
      if (appState.window.fullscreen) {
        eventBus.emit(SetFullscreenModeEvent(!appState.window.fullscreen));
      }
      break;

    // press F1 to show/hide the gui windows
    case SDLK_F1:
      eventBus.emit(SetGuiVisibilityEvent(!appState.gui.visibility));
      break;

      // press m to show/hide the mouse
    case SDLK_M:
      eventBus.emit(SetMouseVisibilityEvent(!appState.window.mouseVisibility));
      break;

    // press f to maximize the window
    case SDLK_F:
      eventBus.emit(SetWindowMaximizedEvent(!appState.window.maximized));
      break;

    // press p to pause/unpause the simulation
    case SDLK_P:
      eventBus.emit(SetPauseEvent(!appState.simulation.paused));
      break;

    // press q+ctrl+shift to close the simulation
    case SDLK_Q:

      if ((event.key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_LSHIFT)) ==
          (SDL_KMOD_LCTRL | SDL_KMOD_LSHIFT)) {
        eventBus.emit(QuitEvent{});
      }

      break;
    }
  }

  if (event.type == SDL_EVENT_KEY_UP) {
    eventBus.emit(KeyEvent(event.key.scancode, false));
  }

  // Convert mouse events
  if (event.type == SDL_EVENT_MOUSE_MOTION) {
    eventBus.emit(MouseMoveEvent{static_cast<float>(event.motion.xrel),
                                 static_cast<float>(event.motion.yrel)});
  }

  // Convert scroll events
  if (event.type == SDL_EVENT_MOUSE_WHEEL) {
    eventBus.emit(MouseScrollEvent{static_cast<float>(event.wheel.y)});
  }

  if (event.type == SDL_EVENT_QUIT) {
    eventBus.emit(QuitEvent{});
  }

  if (event.type == SDL_EVENT_WINDOW_RESIZED) {
    eventBus.emit(WindowResizeEvent(event.window.data1, event.window.data2));
  }
}

} // namespace Celestia
