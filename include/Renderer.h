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

// forward declarations
class WindowSDLGL;
class EventBus;
class Scene;

class Renderer {

public:
  Renderer(WindowSDLGL &window, EventBus &eventBus, Scene &scene);
  ~Renderer();
  void renderFrame();

private:
  WindowSDLGL &window;
  EventBus &eventBus;
  Scene &scene;

  Camera camera;
  Shader shader;

  Mesh cubeMesh;
  Texture texture1;
  Texture texture2;

  int m_width;
  int m_height;
};

} // namespace Celestia
