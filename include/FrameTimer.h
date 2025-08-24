#pragma once

/**
 *
 * FrameTimer delivers useful information such as deltaTime for physics,
 * Framerates for performance testing and so on.
 *
 * Theoretically, this class can be used in any other class. If there are more
 * dynamic Objects instantiated on the heap, it might be useful to share this
 * class via a shared smart pointer...
 *
 */

namespace Celestia {

// forward declarations
class EventBus;
class AppState;

class FrameTimer {

public:
  FrameTimer(EventBus &eventBus, AppState &appState);
  void update();

  float getSimulationDeltaTime() { return m_simulationDeltaTime; }
  float getSimulationTime() { return m_simulationTime; }

private:
  EventBus &eventBus;
  AppState &appState;

  void setupEventSubscriptions();

  float m_deltaTime;
  float m_lastTime;
  float m_simulationTime;
  float m_simulationDeltaTime;

  float m_fps;
  float m_stableFPS;
  float m_timeAccumulator;
  int m_frameCount;
};

} // namespace Celestia
