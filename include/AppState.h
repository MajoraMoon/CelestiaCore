#pragma once

#include "EventBus.h"
#include "Events.h"

// these are the default values for the states. Headerfiles who use these values
// have the values defined as well. Otherwise it is not initialized correctly
// for some reason
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
