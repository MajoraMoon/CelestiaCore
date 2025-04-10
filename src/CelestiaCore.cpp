// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
// clang-format on

CelestiaCore::CelestiaCore()
    : window("CelestiaCore", "0.3", eventBus), frameTimer(eventBus),
      scene(frameTimer, eventBus), guiManager(window, eventBus),
      inputManger(eventBus), renderer(scene) {}

void CelestiaCore::run() {

  if (!SDL_SetWindowRelativeMouseMode(window.getSDLGLWindow(), true)) {

    std::cerr << "Unable to set Mouse to relative Mode: " << SDL_GetError()
              << std::endl;
  }

  eventBus.subscribe<QuitEvent>([this](const Event &e) { quitCelestiaCore(); });

  SDL_Event event;

  // main loop
  while (running) {

    // main FrameTimer --> publish frametimer events
    frameTimer.update();

    while (SDL_PollEvent(&event)) {

      inputManger.processEvent(event);

      if (guiManager.IsVisible() && window.mouseIsVisible()) {
        guiManager.processGUIEvent(&event);
      }
      if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.key == SDLK_SPACE) {
        }
      }
    }

    scene.update();

    renderer.renderFrame(window.getSDLGLWindowWidth(),
                         window.getSDLGLWindowHeight());

    // dear ImGui-rendering
    guiManager.newFrame();
    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }
}
