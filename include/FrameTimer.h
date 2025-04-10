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
  void setPaused(bool isPaused) { paused = isPaused; }
  bool isPaused() const { return paused; }

  float getDeltaTime() const { return deltaTime; }
  float getCurrentTime() const { return lastTime; }

  float getSimulationDeltaTime() const { return simulationDeltaTime; }
  float getSimulationTime() const { return simulationTime; }

  float getAverageFPS() const { return stableFPS; }
  float getCurrentFPS() const { return fps; }

private:
  EventBus &eventBus;

  float deltaTime;
  float lastTime;
  float simulationTime;
  float simulationDeltaTime;
  bool paused;

  float fps;
  float stableFPS;
  float timeAccumulator;
  int frameCount;
};
