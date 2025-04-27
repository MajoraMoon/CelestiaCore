#include "EventSystem.h"
#include "pch.h"

namespace Celestia {
StateManager::StateManager(EventBus &eb, AppState &s) : eventBus(eb), state(s) {
  setupSubscriptions();
}

void StateManager::setupSubscriptions() {

  //------------------------------------------------------------------------------
  //
  // Input-Driven State  Changes (From User input -> keyboard, mouse, window...)
  //
  //------------------------------------------------------------------------------

  // Handle mouse visibility toggle requests (M key)
  eventBus.on<ToggleMouseVisibilityEvent>([this](const auto &) {
    state.window.mouseVisible = !state.window.mouseVisible;
    eventBus.emit(MouseVisibilityChanged{state.window.mouseVisible});
  });

  // Handle window maximize toggle requests (F key)
  eventBus.on<ToggleWindowMaximizedEvent>([this](const auto &) {
    state.window.maximized = !state.window.maximized;
    eventBus.emit(WindowMaximizedChanged{state.window.maximized});
  });

  // Handle GUI visibility toggle requests (F1 key)
  eventBus.on<ToggleGuiVisibilityEvent>([this](const auto &) {
    state.gui.visible = !state.gui.visible;
    eventBus.emit(GuiVisibilityChanged{state.gui.visible});
  });

  // Handle simulation pause toggle requests (P key)
  eventBus.on<TogglePauseEvent>([this](const auto &) {
    state.simulation.paused = !state.simulation.paused;
    eventBus.emit(SimulationPausedChanged{state.simulation.paused});
  });

  // the quitEvent does not have multiple bool changes because when the main
  // loop is stopped, the whole simulation and therefore the window disappears.
  // Handle application termination requests (CTRL+SHIFT+Q)
  eventBus.on<QuitEvent>([this](const auto &) {
    state.celestiaCore.quit = true;
    eventBus.emit(CelestiaCoreQuitChanged{state.celestiaCore.quit});
  });

  //------------------------------------------------------------------------------
  //
  // GUI-Driven State Changes (From settings panels)
  //
  //------------------------------------------------------------------------------

  // Apply mouse sensitivity changes from GUI slider
  eventBus.on<SetMouseSensitivityEvent>([this](const auto &ev) {
    // no redundant updates for this float value. I might forgot it
    // everywhere else lol
    // So an if-statement costs more than assigning a new value each frame,
    // but it also triggers the eventBus publish function.

    state.camera.mouseSensitivity = ev.sensitivity;
    eventBus.emit(MouseSensitivityChanged{state.camera.mouseSensitivity});
  });

  // Apply fullscreen mode changes from GUI selector
  eventBus.on<SetFullscreenModeEvent>([this](const auto &ev) {
    state.window.fullscreen = ev.fullscreen;
    eventBus.emit(WindowFullscreenChanged{state.window.fullscreen});
  });

  // Apply VSync mode changes from GUI selector
  eventBus.on<SetVsyncModeEvent>([this](const auto &ev) {
    state.window.vsync = ev.vsync;
    eventBus.emit(VsyncModeChanged{state.window.vsync});
  });
}

void StateManager::publishInitialStates() {

  // Broadcast initial state to synchronize all subscribers
  eventBus.emit(MouseVisibilityChanged{state.window.mouseVisible});
  eventBus.emit(GuiVisibilityChanged{state.gui.visible});
  eventBus.emit(SimulationPausedChanged{state.simulation.paused});
  eventBus.emit(WindowMaximizedChanged{state.window.maximized});
  eventBus.emit(MouseSensitivityChanged{state.camera.mouseSensitivity});
  eventBus.emit(WindowFullscreenChanged{state.window.fullscreen});
  eventBus.emit(VsyncModeChanged{state.window.vsync});
}

} // namespace Celestia
