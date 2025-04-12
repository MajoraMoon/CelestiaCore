#pragma once

#include "EventBus.h"
#include "Events.h"

struct AppState {
  bool mouseVisible = false;
  bool guiVisible = true;
  bool simulationPaused = false;
  bool windowMaximized = false;
};

class StateManager {

public:
  StateManager(EventBus &eventBus, AppState &state);

private:
  EventBus &eventBus;
  AppState &state;

  void setupSubscriptions();
};
