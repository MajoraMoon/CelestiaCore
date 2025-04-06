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

class FrameTimer {

public:
  FrameTimer();
  void update();
  float getDeltaTime() const { return deltaTime; }
  float getAverageFPS() const { return stableFPS; }
  float getCurrentFPS() const { return fps; }
  float getCurrentTime() const { return lastFrame; }

private:
  float deltaTime;
  float lastFrame;
  float fps;
  float stableFPS;
  float timeAccumulator;
  int frameCount;
};
