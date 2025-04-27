#pragma once

namespace Celestia {

// forward declarations
class EventBus;
struct AppState;

/**
 * @class AppState
 * @brief Centralized application state container and management system
 *
 *  Provides a structured hierarchy for all global application state values,
 * including window configuration, GUI visibility, simulation control,
 * and core lifecycle flags. Managed exclusively through EventBus notifications
 *
 * @note MOST state modification should happen through EventBus
 * notifications. (There are exceptions, e.g. start-resolution)
 */
struct AppState {

  struct Gui {
    bool visible = true; // Global GUI visibility state
  } gui;

  struct Simulation {
    bool paused = false; // Simulation pause state
  } simulation;

  struct Window {
    bool mouseVisible = false; // Mouse cursor visibility state
    bool maximized = false;    // Window maximized state
    bool fullscreen = false;   // Fullscreen mode state
    bool vsync = false;        // Vertical synchronization state (aka Vsync)

  } window;

  struct CelestiaCore {
    // no default initialization needed because when the main loop is not
    // looping anymore the simulation closes
    bool quit; // Application termination flag
  } celestiaCore;

  struct Camera {
    float mouseSensitivity = 0.150f; // Camera control sensitivity
  } camera;
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