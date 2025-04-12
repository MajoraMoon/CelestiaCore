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

  float deltaTime;
  float lastTime;
  float simulationTime;
  float simulationDeltaTime;

  float fps;
  float stableFPS;
  float timeAccumulator;
  int frameCount;

  bool simulationPaused;
};
