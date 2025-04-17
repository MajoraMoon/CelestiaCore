#pragma once

/**
 *
 * The Renderer class is really only responsible to render the graphical part of
 * this application. It manages the Shader, Texture and mesh classes. Takes a
 * reference to the Scene class
 *
 */

#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

namespace Celestia {

class EventBus;
class Scene;
class WindowSDLGL;

class Renderer {

public:
  Renderer(WindowSDLGL &window, EventBus &eventBus, Scene &scene);
  ~Renderer();
  void renderFrame();

private:
  Shader shader;
  Texture texture1;
  Texture texture2;
  Mesh cubeMesh;
  Camera camera;

  Scene &scene;
  EventBus &eventBus;
  WindowSDLGL &window;

  int m_width;
  int m_height;
};

} // namespace Celestia
