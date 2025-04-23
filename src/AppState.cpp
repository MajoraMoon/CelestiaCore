#include "EventSystem.h"
#include "pch.h"

namespace Celestia
{
StateManager::StateManager(EventBus &eb, AppState &s) : eventBus(eb), state(s)
{
    setupSubscriptions();
}

void StateManager::setupSubscriptions()
{

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

    /* ----------- Events emited (published) by keyboard/mouse input ----------- */

    // Mouse visibility
    eventBus.subscribe<ToggleMouseVisibilityEvent>([this](const ToggleMouseVisibilityEvent &) {
        state.window.mouseVisible = !state.window.mouseVisible;
        eventBus.publish(MouseVisibilityChanged{state.window.mouseVisible});
    });

    // Window state
    eventBus.subscribe<ToggleWindowMaximizedEvent>([this](const ToggleWindowMaximizedEvent &) {
        state.window.maximized = !state.window.maximized;
        eventBus.publish(WindowMaximizedChanged{state.window.maximized});
    });

    // GUI visibility
    eventBus.subscribe<ToggleGuiVisibilityEvent>([this](const ToggleGuiVisibilityEvent &) {
        state.gui.visible = !state.gui.visible;
        eventBus.publish(GuiVisibilityChanged{state.gui.visible});
    });

    // Pause state
    eventBus.subscribe<TogglePauseEvent>([this](const TogglePauseEvent &) {
        state.simulation.paused = !state.simulation.paused;
        eventBus.publish(SimulationPausedChanged{state.simulation.paused});
    });

    // the quitEvent does not have multiple bool changes because when the main
    // loop is stopped, the whole simulation and therefore the window disappears.
    eventBus.subscribe<QuitEvent>([this](const QuitEvent &) {
        state.celestiaCore.quit = true;
        eventBus.publish(CelestiaCoreQuitChanged{state.celestiaCore.quit});
    });

    /* ---------------- Events emited (published) by gui input -------------- */

    // Mouse sensitivity
    eventBus.subscribe<SetMouseSensitivityEvent>([this](const SetMouseSensitivityEvent &ev) {
        // no redundant updates for this float value. I might forgot it
        // everywhere else lol
        // So an if-statement costs more than assigning a new value each frame,
        // but it also triggers the eventBus publish function.

        state.camera.mouseSensitivity = ev.sensitivity;
        eventBus.publish(MouseSensitivityChanged{state.camera.mouseSensitivity});
    });

    // Fullscreen mode
    eventBus.subscribe<SetFullscreenModeEvent>([this](const SetFullscreenModeEvent &ev) {
        state.window.fullscreen = ev.fullscreen;
        eventBus.publish(WindowFullscreenChanged{state.window.fullscreen});
    });

    // Vsync mode
    eventBus.subscribe<SetVsyncModeEvent>([this](const SetVsyncModeEvent &ev) {
        state.window.vsync = ev.vsync;
        eventBus.publish(VsyncModeChanged{state.window.vsync});
    });
}

void StateManager::publishInitialStates()
{

    // Broadcast initial state to all listeners
    eventBus.publish(MouseVisibilityChanged{state.window.mouseVisible});
    eventBus.publish(GuiVisibilityChanged{state.gui.visible});
    eventBus.publish(SimulationPausedChanged{state.simulation.paused});
    eventBus.publish(WindowMaximizedChanged{state.window.maximized});
    eventBus.publish(MouseSensitivityChanged{state.camera.mouseSensitivity});
    eventBus.publish(WindowFullscreenChanged{state.window.fullscreen});
    eventBus.publish(VsyncModeChanged{state.window.vsync});
}

} // namespace Celestia
