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

struct AppState
{
    bool mouseVisible = false;
    bool guiVisible = true;
    bool simulationPaused = false;
    bool windowMaximized = false;
    bool quit = false;
    float mouseSensitivity = 0.1f;
};

class StateManager
{

  public:
    StateManager(EventBus &eventBus, AppState &state);

  private:
    EventBus &eventBus;
    AppState &state;

    void setupSubscriptions();
};

} // namespace Celestia