#pragma once

/**
 *
 * This class is responsible to process the keyboard/mouse input using SDL3.
 *
 */

namespace Celestia {

// forward declarations
class EventBus;
class AppState;

class InputManager {

public:
  InputManager(EventBus &eventBus, AppState &appState);

  void processEvent(const SDL_Event &event);

private:
  EventBus &eventBus;
  AppState &appState;
};

} // namespace Celestia
