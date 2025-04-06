#pragma once
// clang-format off

#include "Shader.h"
#include "Resources.h"
#include "Camera.h"
#include "Texture.h"
#include "Mesh.h"
#include "Scene.h"

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
  Renderer(Scene &scene);
  ~Renderer();
  void renderFrame(unsigned int width, unsigned int height);

private:
  Shader shader;
  Texture texture1;
  Texture texture2;
  Mesh cubeMesh;
  Scene &scene;
};
