

// clang-format off
#include "pch.h"
#include "InputManager.h"
// clang-format on

InputManager::InputManager(WindowSDLGL &window, FrameTimer &frameTimer,
                           GuiManager &guiManager)
    : window(window), frameTimer(frameTimer), guiManager(guiManager) {}

// main sdl Events
void InputManager::processEvent(const SDL_Event &event, WindowSDLGL &window) {

  if (event.type == SDL_EVENT_QUIT) {

    quitRequested = true;
  }

  // when the window is resized, tell it openGL
  if (event.type == SDL_EVENT_WINDOW_RESIZED) {

    handleWindowResize(event.window.data1, event.window.data2);
  }

  // main events when keys are pressed.
  if (event.type == SDL_EVENT_KEY_DOWN) {

    // close program
    if (event.key.key == CLOSE_PROGRAM) {
      quitRequested = true;
    }

    // disable/enable DearImGui Window
    if (event.key.key == TOGGLE_GUI) {

      guiManager.toggleVisibility();
    }

    // toggle mouse for camera mode
    if (event.key.key == TOGGLE_MOUSE) {

      handleMouseVisibity(window.getSDLGLWindow(), window.getSDLGLWindowWidth(),
                          window.getSDLGLWindowHeight());
    }

    if (event.key.key == MAXIMIZE_WINDOW) {

      handleMaximizeWindow(window.getSDLGLWindow());
    }
  }

  // mouse movement events
  if (event.type == SDL_EVENT_MOUSE_MOTION) {

    if (!mouseVisibility) {
      mouseXRel += event.motion.xrel;
      mouseYRel += event.motion.yrel;
    }
  }

  // mouse scroll events
  if (event.type == SDL_EVENT_MOUSE_WHEEL) {

    if (!mouseVisibility) {
      scrollY += event.wheel.y;
    }
  }

  switch (event.type) {
  case SDL_EVENT_KEY_DOWN:
    if (event.key.scancode < SDL_SCANCODE_COUNT) {
      keys[event.key.scancode] = true;
    }
    break;
  case SDL_EVENT_KEY_UP:
    if (event.key.scancode < SDL_SCANCODE_COUNT) {
      keys[event.key.scancode] = false;
    }
    break;
  }
}

void InputManager::updateCamera(Camera &camera) {

  if (!mouseVisibility) {
    // Keyboard
    if (keys[MOVE_FRONT])
      camera.processKeyboard(FORWARD, frameTimer.getDeltaTime());
    if (keys[MOVE_BACK])
      camera.processKeyboard(BACKWARD, frameTimer.getDeltaTime());
    if (keys[MOVE_LEFT])
      camera.processKeyboard(LEFT, frameTimer.getDeltaTime());
    if (keys[MOVE_RIGHT])
      camera.processKeyboard(RIGHT, frameTimer.getDeltaTime());
    if (keys[MOVE_UP])
      camera.processKeyboard(UP, frameTimer.getDeltaTime());
    if (keys[MOVE_DOWN])
      camera.processKeyboard(DOWN, frameTimer.getDeltaTime());

    // Mouse
    if (mouseXRel != 0 || mouseYRel != 0) {
      camera.processMouseMovement(mouseXRel, -mouseYRel);
      mouseXRel = mouseYRel = 0;
    }
    if (scrollY != 0) {
      camera.processMouseScroll(scrollY);
      scrollY = 0;
    }
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