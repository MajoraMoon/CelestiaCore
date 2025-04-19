#pragma once
#include "pch.h"

namespace Celestia {

/* ---------------------------------------------------------------- */
/* ------------------------ CORE INPUT EVENTS --------------------- */
/* ---------------------------------------------------------------- */
// Raw system/input events that report instantaneous state changes

// Keyboard key state change (press/release)
// Published by InputManager for every key state change
struct KeyEvent : Event {
  SDL_Scancode scancode;
  bool pressed;

  KeyEvent(SDL_Scancode code, bool isPressed)
      : scancode(code), pressed(isPressed) {}
};

// Relative mouse movement
// Published by InputManager when mouse moves
struct MouseMoveEvent : Event {
  float xrel;
  float yrel;

  MouseMoveEvent(float x, float y) : xrel(x), yrel(y) {}
};

// Mouse wheel scroll
// Published by InputManager for scroll events
struct MouseScrollEvent : Event {
  float yoffset;
  explicit MouseScrollEvent(float y) : yoffset(y) {}
};

// Window size change notification
// Published by window system when resized
struct WindowResizeEvent : Event {
  int width;
  int height;
  WindowResizeEvent(int w, int h) : width(w), height(h) {}
};

// Frame timing information
// Published by main loop each frame from the FrameTimer class
struct FrameUpdateEvent : Event {
  float deltaTime;
  float lastTime;
  float simulationTime;
  float simulationDeltaTime;
  float stableFPS;
  bool paused;

  FrameUpdateEvent(float delta, float last, float simTime, float simDelta,
                   float fps, bool paused)
      : deltaTime(delta), lastTime(last), simulationTime(simTime),
        simulationDeltaTime(simDelta), stableFPS(fps), paused(paused) {}
};

/* ---------------------------------------------------------------- */
/* -------------------- APP STATE COMMAND EVENTS ------------------ */
/* ---------------------------------------------------------------- */
// Intent events to request state changes (typically from input/GUI)

// Toggle commands (for keybinds)
// These Toggle events are published by the InputManager without any arugments
// to set

// Published by InputManager (M key)
struct ToggleMouseVisibilityEvent : Event {};
// Published by InputManager (F1 key)
struct ToggleGuiVisibilityEvent : Event {};
// Published by InputManager (P key)
struct TogglePauseEvent : Event {};
// Published by InputManager (F key)
struct ToggleWindowMaximizedEvent : Event {};

// Request to quit application
// Published by InputManager (ESC Key)
struct QuitEvent : Event {};

// Request to set mouse sensitivity
// Published by GUI settings panel
struct SetMouseSensitivityEvent : Event {
  float sensitivity;
  SetMouseSensitivityEvent(float s) : sensitivity(s) {}
};

// These Set-Events down below are not used yet, but practiaclly if anyone wants
// to implement it into the gui later.

// Request to set mouse visibility state
// NOT Published by GUI settings panel
struct SetMouseVisibilityEvent : Event {
  bool visible;
  SetMouseVisibilityEvent(bool v) : visible(v) {}
};

// Request to set GUI visibility state
// NOT Published by GUI settings panel
struct SetGuiVisibilityEvent : Event {
  bool visible;
  SetGuiVisibilityEvent(bool v) : visible(v) {}
};

// Request to pause/unpause simulation
// NOT Published by GUI settings panel
struct SetSimulationPausedEvent : Event {
  bool paused;
  SetSimulationPausedEvent(bool p) : paused(p) {}
};

// Request to maximize/restore window
// NOT Published by GUI settings panel
struct SetWindowMaximizedEvent : Event {
  bool maximized;
  SetWindowMaximizedEvent(bool m) : maximized(m) {}
};

/* ---------------------------------------------------------------- */
/* ------------------- APP STATE CHANGE EVENTS -------------------- */
/* ---------------------------------------------------------------- */
// Notification events about completed state changes

// Notification of mouse visibility change
// Published by StateManager
struct MouseVisibilityChanged : Event {
  bool visible;
  MouseVisibilityChanged(bool v) : visible(v) {}
};

// Notification of GUI visibility change
// Published by StateManager
struct GuiVisibilityChanged : Event {
  bool visible;
  GuiVisibilityChanged(bool v) : visible(v) {}
};

// Notification of simulation pause state change
// Published by StateManager
struct SimulationPausedChanged : Event {
  bool paused;
  SimulationPausedChanged(bool p) : paused(p) {}
};

// Notification of window maximize state change
// Published by StateManager
struct WindowMaximizedChanged : Event {
  bool maximized;
  WindowMaximizedChanged(bool m) : maximized(m) {}
};

// Notification of mouse sensitivity change
// Published by StateManager
struct MouseSensitivityChanged : Event {
  float sensitivity;
  MouseSensitivityChanged(float s) : sensitivity(s) {}
};

} // namespace Celestia