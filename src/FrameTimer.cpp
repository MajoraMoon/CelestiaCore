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
  fps = 1.0f / deltaTime;

  timeAccumulator += deltaTime;
  frameCount++;

  if (timeAccumulator >= 1.0f) {
    stableFPS = frameCount / timeAccumulator;
    frameCount = 0;
    timeAccumulator = 0.0f;
  }
}