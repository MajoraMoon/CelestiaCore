#pragma once

namespace Celestia {

// forward declarations
class EventBus;
class FrameTimer;

class Scene {

public:
  Scene(EventBus &eventBus, FrameTimer &frameTimer);

  // logic update for rendered objects (e.g. physics)
  void update();

  std::vector<glm::mat4> cubeTransforms;

private:
  EventBus &eventBus;
  FrameTimer &frameTimer;
  std::vector<glm::vec3> cubePositions;

  float m_simulationDeltaTime;
  float m_simulationTime;
};

} // namespace Celestia
