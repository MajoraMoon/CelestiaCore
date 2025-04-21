#pragma once

/**
 *
 * This class is responsible to process the keyboard/mouse input using SDL3.
 *
 */

namespace Celestia
{

// forward declarations
class EventBus;

class InputManager
{

  public:
    InputManager(EventBus &eventBus);

    void processEvent(const SDL_Event &event);

  private:
    EventBus &eventBus;

    int m_windowFullscreen;

    void setupEventSubscriptions();
};

} // namespace Celestia
