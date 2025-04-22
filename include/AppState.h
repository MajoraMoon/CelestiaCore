#pragma once

/**
 *
 * these are the default values for the states. Headerfiles who use these values
 * have the values defined as well. Otherwise it is not initialized correctly
 * for some reason
 *
 */

namespace Celestia {

// forward declarations
class EventBus;
struct AppState;

// these "global" states have the class+usage naming decleration (to refer where
// the specific value is effecting which class)
struct AppState {
  bool guiManagerGuiVisible = true;
  bool frameTimerSimulationPaused = false;

  bool windowMouseVisible = false;
  bool windowMaximized = false;
  bool windowFullscreen = false;

  bool celestiaCoreQuit;
  float cameraMouseSensitivity = 0.1f;
};

class StateManager {

public:
  StateManager(EventBus &eventBus, AppState &state);

  void publishInitialStates();

private:
  EventBus &eventBus;
  AppState &state;

  void setupSubscriptions();
};

} // namespace Celestia