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
    state.paused = !state.paused;
    eventBus.publish(SimulationPaused(state.paused));
  });

  // Window state
  eventBus.subscribe<MaximizeWindowEvent>([this](const Event &) {
    state.windowMaximized = !state.windowMaximized;
    eventBus.publish(WindowMaximized(state.windowMaximized));
  });
}