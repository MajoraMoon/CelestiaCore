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
 * notifications. This is also a single source of truth Struct. That means, all
 * classes should accept the values from here.
 */
struct AppState {

  struct Gui {
    bool visible = true; // Global GUI visibility state
  } gui;

  struct Simulation {
    bool paused = false; // Simulation pause state
  } simulation;

  struct Window {
    bool mouseVisible = true;
    bool maximized = true;
    bool fullscreen = false;
    bool vsync = false;

  } window;

  struct CelestiaCore {
    bool quit = false; // Application termination flag
  } celestiaCore;

  struct Camera {
    float mouseSensitivity = 0.150f; // Camera control sensitivity
  } camera;
};

} // namespace Celestia