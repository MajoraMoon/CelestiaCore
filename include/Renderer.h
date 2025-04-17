#pragma once
// clang-format off

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"

// clang-format on

class EventBus;
class Scene;
class WindowSDLGL;

/**
 *
 * The Renderer class is really only responsible to render the graphical part of
 * this application. It manages the Shader, Texture and mesh classes. Takes a
 * reference to the Scene class
 *
 */

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
