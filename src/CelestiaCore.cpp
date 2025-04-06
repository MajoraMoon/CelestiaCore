// clang-format off
#include "pch.h"
#include "CelestiaCore.h"
// clang-format on

CelestiaCore::CelestiaCore()
    : window("CelestiaCore", "0.2"), frameTimer(), scene(frameTimer),
      guiManager(window, frameTimer),
      inputManger(window, frameTimer, guiManager), renderer(scene) {}

void CelestiaCore::run() {

  SDL_SetWindowRelativeMouseMode(window.getSDLGLWindow(), true);

  bool running = true;
  SDL_Event event;

  // main loop
  while (running) {

    // main FrameTimer
    frameTimer.update();

    while (SDL_PollEvent(&event)) {

      inputManger.processEvent(event, window);
      inputManger.updateCamera(scene.camera);

      if (guiManager.IsVisible()) {
        guiManager.processGUIEvent(&event);
      }
    }

    scene.update();
    renderer.renderFrame(window.getSDLGLWindowWidth(),
                         window.getSDLGLWindowHeight());

    // dear ImGui-rendering
    guiManager.newFrame();
    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());

    // so running is "true". When the quitRequest is also true, running turns
    // false to stop the render loop. I know it would be easier to change the
    // running variable, but for me it is better to a default true value instead
    // of a false value lol
    running = !inputManger.quitRequested;
  }
}
