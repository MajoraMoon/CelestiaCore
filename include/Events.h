#pragma once
#include "pch.h"

namespace Celestia {

//------------------------------------------------------------------------------
//
// CORE INPUT EVENTS
//
//------------------------------------------------------------------------------

// Raw system/input events that report instantaneous state changes

/**
 * @struct keyEvent
 * @brief Signals a keyboard key state change
 * @param scancode SDL_SCANCODE value of the affected key
 * @param pressed True if key was pressed, false if released
 * @note Published by InputManager during event processing loop
 */
struct KeyEvent {
  SDL_Scancode scancode; // Platform-independent key identifier
  bool pressed;          // Key state

  KeyEvent(SDL_Scancode code, bool isPressed)
      : scancode(code), pressed(isPressed) {}
};

/**
 * @struct MouseMoveEvent
 * @brief Reports relative mouse movement in pixels
 * @param xrel Horizontal movement since last frame
 * @param yrel Vertical movement since last frame
 * @note Published by InputManager after mouse motion detection
 */
struct MouseMoveEvent {
  float xrel;
  float yrel;

  MouseMoveEvent(float x, float y) : xrel(x), yrel(y) {}
};

/**
 * @struct MouseScrollEvent
 * @brief Reports vertical mouse wheel movement
 * @param yoffset Vertical scroll offset (positive = up, negative = down)
 * @note Published by InputManager for precise scroll wheel tracking
 */
struct MouseScrollEvent {
  float yoffset;
  explicit MouseScrollEvent(float y) : yoffset(y) {}
};

/**
 * @struct FrameUpdateEvent
 * @brief Contains timing information for frame-based updates
 * @param deltaTime Time since last frame (seconds)
 * @param lastTime Current timestamp (system clock)
 * @param simulationTime Scaled simulation time when unpaused
 * @param simulationDeltaTime Scaled time since last simulation update
 * @param stableFPS Smoothed frames per second average
 * @param paused Whether simulation updates are suspended
 * @note Published by FrameTimer at start of each frame
 */
struct FrameUpdateEvent {
  float deltaTime;           // Real-time frame duration
  float lastTime;            // Current time in seconds
  float simulationTime;      // scaled simulation clock
  float simulationDeltaTime; // scaled simulation step
  float stableFPS;           // Filtered FPS measurement

  FrameUpdateEvent(float delta, float last, float simTime, float simDelta,
                   float fps)
      : deltaTime(delta), lastTime(last), simulationTime(simTime),
        simulationDeltaTime(simDelta), stableFPS(fps) {}
};

//------------------------------------------------------------------------------
//
// COMMAND EVENTS -  STATE COMMAND EVENTS
//
//------------------------------------------------------------------------------

// Intent events requesting application state changes

/// @brief Toggles mouse cursor visibility (M key)
/// @note Published by InputManager, handled by StateManager
struct ToggleMouseVisibilityEvent {};

/// @brief Toggles GUI panel visibility (F1 key)
/// @note Published by InputManager, handled by GuiManager
struct ToggleGuiVisibilityEvent {};

/// @brief Pauses/unpauses simulation (P key)
/// @note Published by InputManager, handled by FrameTimer
struct TogglePauseEvent {};

/// @brief Toggles window between normal/maximized states (F key)
/// @note Published by InputManager, handled by WindowSDLGL
struct ToggleWindowMaximizedEvent {};

/// @brief Requests application termination (CTRL+SHIFT+Q)
/// @note Published by InputManager, handled by CelestiaCore
struct QuitEvent {};

/**
 * @struct WindowResizeEvent
 * @brief Signals viewport dimension changes
 * @param width New window width in pixels
 * @param height New window height in pixels
 * @note Published by WindowSDLGL after resize operations
 */
struct WindowResizeEvent {
  // the initial states of values are not set in the AppState but in the private
  // variable in the windowSDLGL class (Because of OpenGL idk honestly)
  uint32_t width;  // Current viewport width
  uint32_t height; // Current viewport height
  WindowResizeEvent(uint32_t w, uint32_t h) : width(w), height(h) {}
};

/// @brief Sets mouse sensitivity from GUI control
/// @param sensitivity New sensitivity value (normalized 0.0-1.0)
/// @note Published by GuiManager, handled by CameraSystem
struct SetMouseSensitivityEvent {
  float sensitivity;
  SetMouseSensitivityEvent(float s) : sensitivity(s) {}
};

/// @brief Changes window fullscreen state
/// @param fullscreen Requested fullscreen mode
/// @note Published by GuiManager & InputManager, handled by WindowSDLGL
struct SetFullscreenModeEvent {
  bool fullscreen;
  SetFullscreenModeEvent(bool f) : fullscreen(f) {}
};

/// @brief Controls vertical synchronization
/// @param vsync True to enable VSync, false to disable
/// @note Published by GuiManager, handled by WindowSDLGL
struct SetVsyncModeEvent {
  bool vsync;
  SetVsyncModeEvent(bool v) : vsync(v) {}
};

} // namespace Celestia