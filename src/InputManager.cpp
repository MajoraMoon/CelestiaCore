

// clang-format off
#include "pch.h"
#include "InputManager.h"
// clang-format on

InputManager::InputManager(WindowSDLGL &window, FrameTimer &frameTimer,
                           GuiManager &guiManager, EventBus &eventBus)
    : window(window), frameTimer(frameTimer), guiManager(guiManager),
      eventBus(eventBus) {}

// main sdl Events
void InputManager::processEvent(const SDL_Event &event) {

  if (event.type == SDL_EVENT_QUIT) {
    eventBus.publish(QuitEvent{});
  }

  if (event.type == SDL_EVENT_KEY_DOWN) {
    switch (event.key.key) {
    case SDLK_ESCAPE:
      eventBus.publish(QuitEvent{});
      break;

    case SDLK_F1:
      eventBus.publish(ToggleGuiEvent{});
      break;

    case SDLK_M:
      eventBus.publish(ToggleMouseEvent{});
      break;

    case SDLK_F:
      eventBus.publish(MaximizeWindowEvent{});
      break;

    case SDLK_P:
      eventBus.publish(PauseEvent{});
      break;
    }
  }

  // Convert mouse events
  if (event.type == SDL_EVENT_MOUSE_MOTION && !mouseVisibility) {
    eventBus.publish(MouseMoveEvent{static_cast<float>(event.motion.xrel),
                                    static_cast<float>(event.motion.yrel)});
  }

  // Convert scroll events
  if (event.type == SDL_EVENT_MOUSE_WHEEL && !mouseVisibility) {
    eventBus.publish(MouseScrollEvent{static_cast<float>(event.wheel.y)});
  }
}

/**
 * INPUT FUNCTIONS
 */

void InputManager::handleWindowResize(int width, int height) {

  window.setSDLGLWindowSize(width, height);
  glViewport(0, 0, width, height);
}

void InputManager::handleMouseVisibity(SDL_Window *window, int width,
                                       int height) {

  if (!SDL_SetWindowRelativeMouseMode(window, mouseVisibility)) {
    std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
              << std::endl;
  }
  toggleMouseVisibility();

  // when entering the mouse mode or camera mode, will be placed at the
  // center of the window
  SDL_WarpMouseInWindow(window, width / 2, height / 2);
}

void InputManager::handleMaximizeWindow(SDL_Window *window) {
  if (windowIsMaximized) {
    // Restore window before resizing
    if (!SDL_RestoreWindow(window)) {
      std::cerr << "Could not restore window properties: " << SDL_GetError()
                << std::endl;
    }

    SDL_DisplayID displayID = SDL_GetDisplayForWindow(window);
    SDL_Rect usableBounds;
    if (!SDL_GetDisplayUsableBounds(displayID, &usableBounds)) {
      std::cerr << "Could not detect usable desktop area: " << SDL_GetError()
                << std::endl;
    } else {
      int newWidth = usableBounds.w / 2;
      int newHeight = usableBounds.h / 2;

      SDL_SetWindowSize(window, newWidth, newHeight);

      int posX = usableBounds.x + (usableBounds.w - newWidth) / 2;
      int posY = usableBounds.y + (usableBounds.h - newHeight) / 2;
      SDL_SetWindowPosition(window, posX, posY);
      toggleWindowIsMaximized();
    }
  } else {
    if (!SDL_MaximizeWindow(window)) {
      std::cerr << "Unable to maximize window: " << SDL_GetError() << std::endl;
    }
    toggleWindowIsMaximized();
  }
}