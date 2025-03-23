#ifndef FRAMETIMER_H
#define FRAMETIMER_H

#include <SDL3/SDL.h>

class FrameTimer {

public:
  FrameTimer();
  void update();
  float getDeltaTime() const { return deltaTime; }
  float getFPS() const { return stableFPS; }

private:
  float deltaTime;
  float lastFrame;
  float fps;
  float stableFPS;
  float timeAccumulator;
  int frameCount;
};

#endif