// clang-format off

#include "pch.h"
#include "InputManager.h"
#include "EventSystem.h"

// clang-format on

namespace Celestia
{

InputManager::InputManager(EventBus &eventBus) : eventBus(eventBus)
{
    setupEventSubscriptions();
}

void InputManager::processEvent(const SDL_Event &event)
{

    if (event.type == SDL_EVENT_KEY_DOWN)
    {

        // continuous key input
        eventBus.publish(KeyEvent(event.key.scancode, true));

        switch (event.key.key)
        {

        // press Esc in fullscreen mode exit it
        case SDLK_ESCAPE:

            // if window in fullscreen then exit fullscreen
            if (m_windowFullscreen)
            {

                eventBus.publish(SetFullscreenModeEvent{static_cast<bool>(!m_windowFullscreen)});
            }

            break;

        // press F1 to show/hide the gui windows
        case SDLK_F1:
            eventBus.publish(ToggleGuiVisibilityEvent{});
            break;

            // press m to show/hide the mouse
        case SDLK_M:
            eventBus.publish(ToggleMouseVisibilityEvent{});

            break;

        // press f to maximize the window
        case SDLK_F:

            // safety check, only can maximize window when not in fullscreen mode.
            if (!m_windowFullscreen)
            {
                eventBus.publish(ToggleWindowMaximizedEvent{});
            }

            break;

        // press p to pause/unpause the simulation
        case SDLK_P:
            eventBus.publish(TogglePauseEvent{});
            break;

        // press q+ctrl+shift to close the simulation
        case SDLK_Q:

            if ((event.key.mod & (SDL_KMOD_LCTRL | SDL_KMOD_LSHIFT)) == (SDL_KMOD_LCTRL | SDL_KMOD_LSHIFT))
            {
                eventBus.publish(QuitEvent{});
            }

            break;
        }
    }

    if (event.type == SDL_EVENT_KEY_UP)
    {
        eventBus.publish(KeyEvent(event.key.scancode, false));
    }

    // Convert mouse events
    if (event.type == SDL_EVENT_MOUSE_MOTION)
    {
        eventBus.publish(MouseMoveEvent{static_cast<float>(event.motion.xrel), static_cast<float>(event.motion.yrel)});
    }

    // Convert scroll events
    if (event.type == SDL_EVENT_MOUSE_WHEEL)
    {
        eventBus.publish(MouseScrollEvent{static_cast<float>(event.wheel.y)});
    }

    if (event.type == SDL_EVENT_QUIT)
    {
        eventBus.publish(QuitEvent{});
    }

    if (event.type == SDL_EVENT_WINDOW_RESIZED)
    {
        eventBus.publish(WindowResizeEvent(event.window.data1, event.window.data2));
    }
}

void InputManager::setupEventSubscriptions()
{
    eventBus.subscribe<WindowFullscreenChanged>(
        [this](const WindowFullscreenChanged &ev) { m_windowFullscreen = ev.fullscreen; });
}

} // namespace Celestia
