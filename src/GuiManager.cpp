// clang-format off
#include "pch.h"
#include "GuiManager.h"
#include "WindowSDLGL.h"
#include "EventSystem.h"
// clang-format on

namespace Celestia
{

GuiManager::GuiManager(WindowSDLGL &window, EventBus &eventBus, AppState &appState)
    : window(window), eventBus(eventBus), appState(appState)
{

    float scaleFactor = SDL_GetWindowDisplayScale(window.getSDLGLWindow());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.FontGlobalScale = scaleFactor;
    io.Fonts->AddFontFromFileTTF("../assets/fonts/Roboto/static/Roboto-Regular.ttf", 17.0);
    ImGui::GetStyle().ScaleAllSizes(scaleFactor);

    ImGui::StyleColorsDark();

    ImGui_ImplSDL3_InitForOpenGL(window.getSDLGLWindow(), window.getGLContext());
    ImGui_ImplOpenGL3_Init("#version 460");

    setupEventSubscriptions();
}

GuiManager::~GuiManager()
{

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void GuiManager::processGUIEvent(const SDL_Event *event)
{

    if (m_mouseVisible)
    {
        ImGui_ImplSDL3_ProcessEvent(event);
    }
}

void GuiManager::render()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    // dear ImGui needs to end the rendering even if nothing is displayed. So only
    // if Visibility is toggled on, the private functions from imgui are shown
    if (m_guiVisible)
    {
        showShortcutsWindow();
        showStatsWindow();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

// FUNCTION CREATION FOR IMGUI WINDOWS

// actual window to render. This can be extended with other functions later if
// needed. Just using Imgui::Begin and end
void GuiManager::showStatsWindow()
{
    ImGui::Begin("Extra Information");

    // I think packing this code to visual the time better into another function
    // is more verbose than just letting it in here.

    int totalSeconds = static_cast<int>(m_currentTime);
    int milliseconds = static_cast<int>((m_currentTime - totalSeconds) * 1000);

    int hours = totalSeconds / 3600;
    int minutes = (totalSeconds % 3600) / 60;
    int seconds = totalSeconds % 60;

    ImGui::Text("Runtime: %02d:%02d:%02d.%03d", hours, minutes, seconds, milliseconds);
    ImGui::Text("Simulation Runtime (seconds): %.2f", m_simulationTime);
    ImGui::Text("Delta time: %.3f", m_deltaTime);
    ImGui::Text("FPS (average): %.3f", m_stableFPS);
    ImGui::Spacing();
    ImGui::Text("Resolution: %ix%i", m_width, m_height);
    ImGui::Text("Simulation paused: %s", m_simulationPaused ? "True" : "False");

    // VSync Combo Box
    const char *vsyncModes[] = {"VSync Off", "VSync On"};
    int currentVsyncMode = static_cast<int>(window.getVsyncMode());
    if (ImGui::Combo("VSync Mode", &currentVsyncMode, vsyncModes, IM_ARRAYSIZE(vsyncModes)))
    {
        window.setVsyncMode(static_cast<WindowSDLGL::VsyncMode>(currentVsyncMode));
    }

    // Fullscreen mode selector
    const char *screenModes[] = {"Windowed", "Fullscreen"};
    int currentScreenMode = static_cast<int>(m_windowFullscreen);
    if (ImGui::Combo("Display Mode", &currentScreenMode, screenModes, IM_ARRAYSIZE(screenModes)))
    {
        eventBus.publish(SetFullscreenModeEvent{static_cast<bool>(currentScreenMode)});
    }

    // mouse sensitivity slider
    if (ImGui::SliderFloat("Mouse Sensitivity", &m_mouseSensitivity, 0.001f, 1.0f, "%.3f"))
    {
        eventBus.publish(SetMouseSensitivityEvent{m_mouseSensitivity});
    }

    if (ImGui::Button("Close CelestiaCore", ImVec2(-1, 0)))
    {
        eventBus.publish(QuitEvent{});
    }

    ImGui::End();
}

void GuiManager::showShortcutsWindow()
{
    ImGui::Begin("Hotkeys");
    ImGui::Text("Press 'M' to show/hide the mouse cursor.");
    ImGui::Text("Press 'F' to maximize the window.");
    ImGui::Text("Press 'F1' to hide the gui window.");
    ImGui::Text("Press 'P' to pause the simulation");
    ImGui::Text("Press 'Q + Shift + CTRL' to close the application");

    ImGui::End();
}

void GuiManager::setupEventSubscriptions()
{
    eventBus.subscribe<GuiVisibilityChanged>([this](const GuiVisibilityChanged &ev) { m_guiVisible = ev.visible; });

    eventBus.subscribe<MouseVisibilityChanged>(
        [this](const MouseVisibilityChanged &ev) { m_mouseVisible = ev.visible; });

    eventBus.subscribe<MouseSensitivityChanged>(
        [this](const MouseSensitivityChanged &ev) { m_mouseSensitivity = ev.sensitivity; });

    eventBus.subscribe<SimulationPausedChanged>(
        [this](const SimulationPausedChanged &ev) { m_simulationPaused = ev.paused; });

    eventBus.subscribe<WindowFullscreenChanged>(
        [this](const WindowFullscreenChanged &ev) { m_windowFullscreen = ev.fullscreen; });

    eventBus.subscribe<FrameUpdateEvent>([this](const FrameUpdateEvent &ev) {
        m_currentTime = ev.lastTime;
        m_simulationTime = ev.simulationTime;
        m_deltaTime = ev.deltaTime;
        m_stableFPS = ev.stableFPS;
    });

    eventBus.subscribe<WindowResizeEvent>([this](const WindowResizeEvent &ev) {
        m_width = ev.width;
        m_height = ev.height;
    });
}

} // namespace Celestia
