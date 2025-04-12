#include "AppState.h"

StateManager::StateManager(EventBus &eb, AppState &s) : eventBus(eb), state(s) {
  setupSubscriptions();
}

void StateManager::setupSubscriptions() {

  // Mouse visibility
  eventBus.subscribe<ToggleMouseVisibilityEvent>([this](const Event &) {
    state.mouseVisible = !state.mouseVisible;

    eventBus.publish(MouseVisibilityChanged(state.mouseVisible));
  });

  // GUI visibility
  eventBus.subscribe<ToggleGuiEvent>([this](const Event &) {
    state.guiVisible = !state.guiVisible;
    eventBus.publish(GuiVisibilityChanged(state.guiVisible));
  });

  // Pause state
  eventBus.subscribe<PauseEvent>([this](const Event &) {
    state.simulationPaused = !state.simulationPaused;
    eventBus.publish(SimulationPaused(state.simulationPaused));
  });

  // Window state
  eventBus.subscribe<MaximizeWindowEvent>([this](const Event &) {
    state.windowMaximized = !state.windowMaximized;
    eventBus.publish(WindowMaximized(state.windowMaximized));
  });
}