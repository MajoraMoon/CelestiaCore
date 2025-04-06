#include "CelestiaCore.h"

// testtttttttt
CelestiaCore::CelestiaCore()
    : window("CelestiaCore", "0.2"), frameTimer(), scene(frameTimer),
      guiManager(window, frameTimer), inputManger(frameTimer, guiManager),
      renderer(scene) {}

void CelestiaCore::run() {

  SDL_SetWindowRelativeMouseMode(window.getSDLGLWindow(), true);

  bool running = true;
  SDL_Event event;

  // main loop
  while (running) {

    frameTimer.update();
    float deltaTime = frameTimer.getDeltaTime();

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_WINDOW_RESIZED) {
        handleWindowResize(event.window.data1, event.window.data2);
      }

      inputManger.processEvent(event, window);

      if (guiManager.IsVisible()) {
        guiManager.processGUIEvent(&event);
      }
    }

    inputManger.updateCamera(scene.camera);

    scene.update();
    renderer.renderFrame(window.getSDLGLWindowWidth(),
                         window.getSDLGLWindowHeight());

    // dear ImGui-rendering
    guiManager.newFrame();
    guiManager.render();

    SDL_GL_SwapWindow(window.getSDLGLWindow());

    running = !inputManger.quitRequested;
  }
}

void CelestiaCore::handleWindowResize(int width, int height) {
  window.setSDLGLWindowSize(width, height);
  glViewport(0, 0, width, height);
}