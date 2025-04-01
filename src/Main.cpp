// clang-format off

#include <iostream>

#include <SDL3/SDL.h>

#include "FrameTimer.h"
#include "Renderer.h"
#include "WindowSDLGL.h"

// clang-format on

// Vsync stuff
typedef enum { VSyncOFF = 0, VSyncON = 1 } VsyncMode;
static VsyncMode currentVsyncMode = VSyncOFF;

static void activateVsync(VsyncMode mode) {

  if (SDL_GL_SetSwapInterval(static_cast<int>(mode)) == false) {
    SDL_Log("Could not set Swap-Interval (VSync) correctly: %s\n",
            SDL_GetError());
  } else {
    currentVsyncMode = mode;
  }
}

// Dear ImGui window with some information
void ShowInformationWindow(FrameTimer &frameTimer, WindowSDLGL &window) {
  ImGui::Begin("some Information");
  ImGui::Text("FPS (average): %.5f", frameTimer.getAverageFPS());
  ImGui::Text("Resolution: %ix%i", window.getSDLGLWindowWidth(),
              window.getSDLGLWindowHeight());
  const char *vsyncOptions[] = {"VSync Off", "VSync On"};
  int selectedVSyncIndex = static_cast<int>(currentVsyncMode);

  if (ImGui::Combo("VSync Mode", &selectedVSyncIndex, vsyncOptions,
                   IM_ARRAYSIZE(vsyncOptions))) {
    VsyncMode newMode = static_cast<VsyncMode>(selectedVSyncIndex);

    if (newMode != currentVsyncMode) {
      activateVsync(newMode);
    }
  }

  ImGui::End();
}

int main(int argc, char *argv[]) {

  // the dear imgui window can be disabled too
  WindowSDLGL window("LunaCore", "0.1");

  if (!window.getSDLGLWindow() || !window.getGLContext()) {
    std::cerr << "Failed to initialize Window or OpenGL context." << std::endl;

    return -1;
  }

  bool running = true;
  SDL_Event event;

  FrameTimer frameTimer;
  Renderer renderer(frameTimer);

  // main loop
  while (running) {

    // the first thing to do in the main while loop is to update the frame
    // information
    frameTimer.update();

    while (SDL_PollEvent(&event)) {
      if (ImGui::GetCurrentContext() != nullptr) {
        ImGui_ImplSDL3_ProcessEvent(&event);
      }

      if (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
      // Event when a key is pressed
      if (event.type == SDL_EVENT_KEY_DOWN) {

        if (event.key.key == SDLK_ESCAPE) {
          running = false;
        }
      }
      // adjust the resolution to provide openGL correct data
      if (event.window.type == SDL_EVENT_WINDOW_RESIZED) {

        window.setSDLGLWindowSize(event.window.data1, event.window.data2);
      }
    }

    // acutal rendering in this single function. (making it more abstact later)
    renderer.renderFrame(window.getSDLGLWindowWidth(),
                         window.getSDLGLWindowHeight());

    if (ImGui::GetCurrentContext() != nullptr) {

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      ImGui::NewFrame();

      ShowInformationWindow(frameTimer, window);
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    SDL_GL_SwapWindow(window.getSDLGLWindow());
  }

  return 0;
}
