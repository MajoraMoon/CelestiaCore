#include "pch.h"

StateManager::StateManager(EventBus &eb, AppState &s) : eventBus(eb), state(s) {
  setupSubscriptions();
}

void StateManager::setupSubscriptions() {

  /**
   *
   * These values should be the same for every class accessing them. So it is an
   * implementation of a global variable, but only indirectly.
   *
   * These are subscriptions, which trigger to change a  boolean value and then
   * publish the value to another specific event which can be accessed to use
   * the boolean value.
   *
   * idk if I explain it well, but these functions should not be that
   * complicated to understand if you know how the basic idea of this BusEvent
   * works
   */

  // Mouse visibility
  eventBus.subscribe<ToggleMouseVisibilityEvent>(
      [this](const ToggleMouseVisibilityEvent &) {
        state.mouseVisible = !state.mouseVisible;
        eventBus.publish(MouseVisibilityChanged{state.mouseVisible});
      });

  // GUI visibility
  eventBus.subscribe<ToggleGuiEvent>([this](const ToggleGuiEvent &) {
    state.guiVisible = !state.guiVisible;
    eventBus.publish(GuiVisibilityChanged{state.guiVisible});
  });

  // Pause state
  eventBus.subscribe<PauseEvent>([this](const PauseEvent &) {
    state.simulationPaused = !state.simulationPaused;
    eventBus.publish(SimulationPausedChanged{state.simulationPaused});
  });

  // Window state
  eventBus.subscribe<MaximizeWindowEvent>([this](const MaximizeWindowEvent &) {
    state.windowMaximized = !state.windowMaximized;
    eventBus.publish(WindowMaximizedChanged{state.windowMaximized});
  });

  // Mouse sensitivity
  eventBus.subscribe<MouseSensitivityChanged>(
      [this](const MouseSensitivityChanged &ev) {
        state.mouseSensitivity = ev.sensitivity;
      });
}