// clang-format off
#include "pch.h"
#include "FrameTimer.h"
// clang-format on

FrameTimer::FrameTimer(EventBus &eventBus) : eventBus(eventBus) {

  lastTime = SDL_GetTicks() / 1000.0f;
  deltaTime = 0.0f;
  simulationTime = 0.0f;
  simulationDeltaTime = 0.0f;
  simulationPaused = false;

  fps = 0.0f;
  stableFPS = 0.0f;
  timeAccumulator = 0.0f;
  frameCount = 0;

  eventBus.subscribe<SimulationPaused>([this](const Event &e) {
    const auto &ev = static_cast<const SimulationPaused &>(e);
    simulationPaused = ev.simulationPaused;
  });
}

void FrameTimer::update() {
  float currentTime = SDL_GetTicks() / 1000.0f;
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;

  if (!simulationPaused) {
    simulationDeltaTime = deltaTime;
    simulationTime += simulationDeltaTime;
  } else {
    simulationDeltaTime = 0.0f;
  }

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

  // publish events from EventTimer here, because they are not part of any
  // SDL_EVENTS. SDL_EVENTS, so keyboard and mouse events
  eventBus.publish(FrameUpdateEvent(deltaTime, lastTime, simulationTime,
                                    simulationDeltaTime, stableFPS,
                                    simulationPaused));
}