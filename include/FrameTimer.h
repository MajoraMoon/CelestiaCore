#pragma once

#include <SDL3/SDL.h>

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
