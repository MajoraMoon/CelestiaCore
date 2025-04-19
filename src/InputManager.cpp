// clang-format off

#include "pch.h"
#include "InputManager.h"
#include "EventSystem.h"

// clang-format on

namespace Celestia
{

InputManager::InputManager(EventBus &eventBus) : eventBus(eventBus)
{
}

// main sdl Events
void InputManager::processEvent(const SDL_Event &event)
{

    if (event.type == SDL_EVENT_KEY_DOWN)
    {

        // continuous key input
        eventBus.publish(KeyEvent(event.key.scancode, true));

        switch (event.key.key)
        {
        case SDLK_ESCAPE:
            eventBus.publish(QuitEvent{});
            break;

        case SDLK_F1:
            eventBus.publish(ToggleGuiVisibilityEvent{});
            break;

        case SDLK_M:
            eventBus.publish(ToggleMouseVisibilityEvent{});
            break;

        case SDLK_F:
            eventBus.publish(ToggleWindowMaximizedEvent{});
            break;

        case SDLK_P:
            eventBus.publish(TogglePauseEvent{});
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

} // namespace Celestia
