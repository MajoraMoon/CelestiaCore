#pragma once
#include "EventBus.h"
#include "Events.h"

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

class FrameTimer {

public:
  FrameTimer(EventBus &eventBus);
  void update();

private:
  EventBus &eventBus;

  float m_deltaTime;
  float m_lastTime;
  float m_simulationTime;
  float m_simulationDeltaTime;

  float m_fps;
  float m_stableFPS;
  float m_timeAccumulator;
  int m_frameCount;

  bool m_simulationPaused;
};
