#pragma once

/**
 *
 * these are the default values for the states. Headerfiles who use these values
 * have the values defined as well. Otherwise it is not initialized correctly
 * for some reason
 *
 */

namespace Celestia
{

// forward declarations
class EventBus;
struct AppState;

// these "global" states have the class+usage naming decleration (to refer where
// the specific value is effecting which class)
struct AppState
{
    struct Gui
    {
        bool visible = true;
    } gui;

    struct Simulation
    {
        bool paused = false;
    } simulation;

    struct Window
    {
        bool mouseVisible = false;
        bool maximized = false;
        bool fullscreen = false;
        bool vsync = false;

    } window;

    struct CelestiaCore
    {
        // no default initialization needed because if that is true, the whole
        // program is burned next to the sun already. I good english speak very gut
        bool quit;
    } celestiaCore;

    struct Camera
    {
        float mouseSensitivity = 0.150f;
    } camera;
};

class StateManager
{

  public:
    StateManager(EventBus &eventBus, AppState &state);

    void publishInitialStates();

  private:
    EventBus &eventBus;
    AppState &state;

    void setupSubscriptions();
};

} // namespace Celestia