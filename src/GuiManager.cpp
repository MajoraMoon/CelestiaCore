// clang-format off
#include "pch.h"
#include "GuiManager.h"
// clang-format on

GuiManager::GuiManager(WindowSDLGL &window, FrameTimer &frameTimer)
    : window(window), frameTimer(frameTimer) {

  float scaleFactor = SDL_GetWindowDisplayScale(window.getSDLGLWindow());

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.FontGlobalScale = scaleFactor;
  ImGui::GetStyle().ScaleAllSizes(scaleFactor);

  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForOpenGL(window.getSDLGLWindow(), window.getGLContext());
  ImGui_ImplOpenGL3_Init("#version 460");
}

GuiManager::~GuiManager() {

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
}

void GuiManager::processGUIEvent(const SDL_Event *event) {
  ImGui_ImplSDL3_ProcessEvent(event);
}

void GuiManager::newFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void GuiManager::render() {

  // dear ImGui needs to end the rendering even if nothing is displayed. So only
  // if Visibility is toggled on, the private functions from imgui are shown
  if (visible) {
    showShortcutsWindow();
    showStatsWindow();
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GuiManager::toggleVsync(bool vsyncEnabled) {
  m_CurrentVsyncMode = vsyncEnabled ? VsyncMode::On : VsyncMode::Off;
  SDL_GL_SetSwapInterval(static_cast<int>(m_CurrentVsyncMode));
}

// actual window to render. This can be extended with other functions later if
// needed. Just using Imgui::Begin and end
void GuiManager::showStatsWindow() {
  ImGui::Begin("Extra Information");

  // I think packing this code to visual the time better into another function
  // is more verbose than just letting it in here.
  float currentTime = frameTimer.getCurrentTime();
  int totalSeconds = static_cast<int>(currentTime);
  int milliseconds = static_cast<int>((currentTime - totalSeconds) * 1000);

  int hours = totalSeconds / 3600;
  int minutes = (totalSeconds % 3600) / 60;
  int seconds = totalSeconds % 60;

  ImGui::Text("Runtime: %02d:%02d:%02d.%03d", hours, minutes, seconds,
              milliseconds);
  ImGui::Text("Simulation Runtime (seconds): %.2f",
              frameTimer.getSimulationTime());
  ImGui::Text("Delta time: %.3f", frameTimer.getDeltaTime());
  ImGui::Text("FPS (average): %f", frameTimer.getAverageFPS());
  ImGui::Spacing();
  ImGui::Text("Resolution: %ix%i", window.getSDLGLWindowWidth(),
              window.getSDLGLWindowHeight());

  // VSync Combo Box
  const char *vsyncOptions[] = {"VSync Off", "VSync On"};
  int currentVsyncIndex = static_cast<int>(m_CurrentVsyncMode);

  if (ImGui::Combo("VSync Mode", &currentVsyncIndex, vsyncOptions, 2)) {
    toggleVsync(currentVsyncIndex == 1);
  }

  ImGui::End();
}

void GuiManager::showShortcutsWindow() {
  ImGui::Begin("Hotkeys");
  ImGui::Text("Press 'M' to show/hide the mouse cursor.");
  ImGui::Text("Press 'F' to maximize the window");
  ImGui::Text("Press 'F1' to hide the gui window.");
  ImGui::End();
}