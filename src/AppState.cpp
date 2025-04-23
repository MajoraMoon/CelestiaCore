#include "EventSystem.h"
#include "pch.h"

namespace Celestia {
StateManager::StateManager(EventBus &eb, AppState &s) : eventBus(eb), state(s) {
  setupSubscriptions();
}

void StateManager::setupSubscriptions() {

  /**
   *
   * These values should be the same for every class accessing them. So it is an
   * implementation of a global variable, but only indirectly.
   *
   * These are subscriptions, which trigger to change a  boolean value and then
   * publish the value to another specific event which can be accessed to use
   * the boolean value.
   *
   * idk if I explain it well, but these functions should not be that
   * complicated to understand if you know how the basic idea of this BusEvent
   * works
   */

  /* ----------- Events emited (published) by keyboard/mouse input -----------
   */

  // Mouse visibility
  eventBus.on<ToggleMouseVisibilityEvent>(
      [this](const ToggleMouseVisibilityEvent &) {
        state.window.mouseVisible = !state.window.mouseVisible;
        eventBus.emit(MouseVisibilityChanged{state.window.mouseVisible});
      });

  // Window state
  eventBus.on<ToggleWindowMaximizedEvent>(
      [this](const ToggleWindowMaximizedEvent &) {
        state.window.maximized = !state.window.maximized;
        eventBus.emit(WindowMaximizedChanged{state.window.maximized});
      });

  // GUI visibility
  eventBus.on<ToggleGuiVisibilityEvent>(
      [this](const ToggleGuiVisibilityEvent &) {
        state.gui.visible = !state.gui.visible;
        eventBus.emit(GuiVisibilityChanged{state.gui.visible});
      });

  // Pause state
  eventBus.on<TogglePauseEvent>([this](const TogglePauseEvent &) {
    state.simulation.paused = !state.simulation.paused;
    eventBus.emit(SimulationPausedChanged{state.simulation.paused});
  });

  // the quitEvent does not have multiple bool changes because when the main
  // loop is stopped, the whole simulation and therefore the window disappears.
  eventBus.on<QuitEvent>([this](const QuitEvent &) {
    state.celestiaCore.quit = true;
    eventBus.emit(CelestiaCoreQuitChanged{state.celestiaCore.quit});
  });

  /* ---------------- Events emited (published) by gui input -------------- */

  // Mouse sensitivity
  eventBus.on<SetMouseSensitivityEvent>(
      [this](const SetMouseSensitivityEvent &ev) {
        // no redundant updates for this float value. I might forgot it
        // everywhere else lol
        // So an if-statement costs more than assigning a new value each frame,
        // but it also triggers the eventBus publish function.

        state.camera.mouseSensitivity = ev.sensitivity;
        eventBus.emit(MouseSensitivityChanged{state.camera.mouseSensitivity});
      });

  // Fullscreen mode
  eventBus.on<SetFullscreenModeEvent>([this](const SetFullscreenModeEvent &ev) {
    state.window.fullscreen = ev.fullscreen;
    eventBus.emit(WindowFullscreenChanged{state.window.fullscreen});
  });

  // Vsync mode
  eventBus.on<SetVsyncModeEvent>([this](const SetVsyncModeEvent &ev) {
    state.window.vsync = ev.vsync;
    eventBus.emit(VsyncModeChanged{state.window.vsync});
  });
}

void StateManager::publishInitialStates() {

  // Broadcast initial state to all listeners
  eventBus.emit(MouseVisibilityChanged{state.window.mouseVisible});
  eventBus.emit(GuiVisibilityChanged{state.gui.visible});
  eventBus.emit(SimulationPausedChanged{state.simulation.paused});
  eventBus.emit(WindowMaximizedChanged{state.window.maximized});
  eventBus.emit(MouseSensitivityChanged{state.camera.mouseSensitivity});
  eventBus.emit(WindowFullscreenChanged{state.window.fullscreen});
  eventBus.emit(VsyncModeChanged{state.window.vsync});
}

} // namespace Celestia
