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

    /* -------------------- Events emited (published) by keyboard/mouse input ------------------ */

    // Mouse visibility
    eventBus.subscribe<ToggleMouseVisibilityEvent>([this](const ToggleMouseVisibilityEvent &) {
        state.mouseVisible = !state.mouseVisible;
        eventBus.publish(MouseVisibilityChanged{state.mouseVisible});
    });

    // GUI visibility
    eventBus.subscribe<ToggleGuiVisibilityEvent>([this](const ToggleGuiVisibilityEvent &) {
        state.guiVisible = !state.guiVisible;
        eventBus.publish(GuiVisibilityChanged{state.guiVisible});
    });

    // Pause state
    eventBus.subscribe<TogglePauseEvent>([this](const TogglePauseEvent &) {
        state.simulationPaused = !state.simulationPaused;
        eventBus.publish(SimulationPausedChanged{state.simulationPaused});
    });

    // Window state
    eventBus.subscribe<ToggleWindowMaximizedEvent>([this](const ToggleWindowMaximizedEvent &) {
        state.windowMaximized = !state.windowMaximized;
        eventBus.publish(WindowMaximizedChanged{state.windowMaximized});
    });

    // the quitEvent does not have multiple bool changes because when the main loop is stopped, the whole simulation and
    // therefore the window disappears.
    eventBus.subscribe<QuitEvent>([this](const QuitEvent &) {
        state.quit = true;
        eventBus.publish(CelestiaCoreQuitChanged{state.quit});
    });

    /* -------------------- Events emited (published) by gui input ------------------ */

    // Mouse sensitivity
    eventBus.subscribe<SetMouseSensitivityEvent>([this](const SetMouseSensitivityEvent &ev) {
        // no redundant updates for this float value. I might forgot it
        // everywhere else lol
        // So an if-statement costs more than assigning a new value each frame,
        // but it also triggers the eventBus publish function.
        if (state.mouseSensitivity != ev.sensitivity)
        {
            state.mouseSensitivity = ev.sensitivity;
            eventBus.publish(MouseSensitivityChanged{ev.sensitivity});
        }
    });

    // Fullscreen mode
    eventBus.subscribe<SetFullscreenModeEvent>([this](const SetFullscreenModeEvent &ev) {
        state.windowFullscreen = ev.fullscreen;
        eventBus.publish(WindowFullscreenChanged{ev.fullscreen});
    });
}

void StateManager::publishInitialStates()
{

    // Broadcast initial state to all listeners
    eventBus.publish(MouseVisibilityChanged{state.mouseVisible});
    eventBus.publish(GuiVisibilityChanged{state.guiVisible});
    eventBus.publish(SimulationPausedChanged{state.simulationPaused});
    eventBus.publish(WindowMaximizedChanged{state.windowMaximized});
    eventBus.publish(MouseSensitivityChanged{state.mouseSensitivity});
    eventBus.publish(WindowFullscreenChanged{state.windowFullscreen});
}

} // namespace Celestia
