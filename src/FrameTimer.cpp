#include <FrameTimer.h>

FrameTimer::FrameTimer() {

  deltaTime = 0.0f;
  // in seconds
  lastFrame = SDL_GetTicks() / 1000.0f;
  fps = 0.0f;
  stableFPS = 0.0f;
  timeAccumulator = 0.0f;
  frameCount = 0;
}

void FrameTimer::update() {
  float currentFrame = SDL_GetTicks() / 1000.0f;
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  // preventing it to devide with zero. So...if delta time is ever zero for some
  // reason
  if (deltaTime > 0.0f) {
    fps = 1.0f / deltaTime;
  }

  timeAccumulator += deltaTime;
  frameCount++;

  if (timeAccumulator >= 1.0f) {
    //  calculates the average framerate over a second. The current framerate
    //  can vary strongly if delta time is getting smaller
    stableFPS = frameCount / timeAccumulator;
    frameCount = 0;
    timeAccumulator = 0.0f;
  }
}