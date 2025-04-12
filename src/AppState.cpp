#include "AppState.h"

StateManager::StateManager(EventBus &eb, AppState &s) : eventBus(eb), state(s) {
  setupSubscriptions();
}

void StateManager::setupSubscriptions() {

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
}