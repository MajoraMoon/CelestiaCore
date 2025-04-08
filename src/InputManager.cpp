

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

    window.setSDLGLWindowSize(event.window.data1, event.window.data2);
    glViewport(0, 0, event.window.data1, event.window.data2);
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

      toggleMouseVisibility();

      if (!SDL_SetWindowRelativeMouseMode(window.getSDLGLWindow(),
                                          mouseVisibility)) {
        std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
                  << std::endl;
      }

      // when entering the mouse mode or camera mode, will be placed at the
      // center of the window
      SDL_WarpMouseInWindow(window.getSDLGLWindow(),
                            window.getSDLGLWindowWidth() / 2,
                            window.getSDLGLWindowHeight() / 2);
    }

    if (event.key.key == MAXIMIZE_WINDOW) {

      if (event.key.key == MAXIMIZE_WINDOW) {

        if (windowIsMaximized) {
          // Restore window before resizing
          SDL_RestoreWindow(window.getSDLGLWindow());

          SDL_DisplayID displayID =
              SDL_GetDisplayForWindow(window.getSDLGLWindow());
          SDL_Rect usableBounds;
          if (!SDL_GetDisplayUsableBounds(displayID, &usableBounds)) {
            std::cerr << "Could not detect usable desktop area: "
                      << SDL_GetError() << std::endl;
          } else {
            int newWidth = usableBounds.w / 2;
            int newHeight = usableBounds.h / 2;

            SDL_SetWindowSize(window.getSDLGLWindow(), newWidth, newHeight);

            int posX = usableBounds.x + (usableBounds.w - newWidth) / 2;
            int posY = usableBounds.y + (usableBounds.h - newHeight) / 2;
            SDL_SetWindowPosition(window.getSDLGLWindow(), posX, posY);
            toggleWindowIsMaximized();
          }
        } else {
          if (!SDL_MaximizeWindow(window.getSDLGLWindow())) {
            std::cerr << "Unable to maximize window: " << SDL_GetError()
                      << std::endl;
          }
          toggleWindowIsMaximized();
        }
      }
    }
  }

  // mouse movement events
  if (event.type == SDL_EVENT_MOUSE_MOTION) {

    if (mouseVisibility) {
      mouseXRel += event.motion.xrel;
      mouseYRel += event.motion.yrel;
    }
  }

  // mouse scroll events
  if (event.type == SDL_EVENT_MOUSE_WHEEL) {

    if (mouseVisibility) {
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

  if (mouseVisibility) {
    // Keyboard
    if (keys[SDL_SCANCODE_W])
      camera.processKeyboard(FORWARD, frameTimer.getDeltaTime());
    if (keys[SDL_SCANCODE_S])
      camera.processKeyboard(BACKWARD, frameTimer.getDeltaTime());
    if (keys[SDL_SCANCODE_A])
      camera.processKeyboard(LEFT, frameTimer.getDeltaTime());
    if (keys[SDL_SCANCODE_D])
      camera.processKeyboard(RIGHT, frameTimer.getDeltaTime());
    if (keys[SDL_SCANCODE_LSHIFT])
      camera.processKeyboard(UP, frameTimer.getDeltaTime());
    if (keys[SDL_SCANCODE_LCTRL] || keys[SDL_SCANCODE_RCTRL])
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
