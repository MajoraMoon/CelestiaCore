#pragma once
// clang-format off

#include "EventBus.h"
#include "Events.h"

#include "Shader.h"
#include "Resources.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Scene.h"
#include "WindowSDLGL.h"

// clang-format on

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

  Scene &scene;
  EventBus &eventBus;
  WindowSDLGL &window;

  int width;
  int height;
};
