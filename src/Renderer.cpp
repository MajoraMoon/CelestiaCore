// clang-format off

#include "pch.h"
#include "Renderer.h"
#include "Scene.h"
#include "WindowSDLGL.h"
#include "Resources.h"

// clang-format on

namespace Celestia {

Renderer::Renderer(WindowSDLGL &window, EventBus &eventBus, Scene &scene)
    : window(window), eventBus(eventBus), scene(scene),
      camera(eventBus, glm::vec3(0.0f, 0.0f, 6.0f)),
      shader("../shader/vertexShader.vert", "../shader/fragmentShader.frag"),
      texture1("../assets/textures/rocky_terrain_diff_4k.jpg"),
      texture2("../assets/textures/awesomeface.png"),
      cubeMesh({

          // clang-format off
  // Vertex-Data: position, texture position (6 times a single plain for representing a cube)
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f})

// clang-format on
{
  // Turn off VSync
  SDL_GL_SetSwapInterval(0);
  glEnable(GL_DEPTH_TEST);

  shader.use();
  shader.setInt("texture1", 0);
  shader.setInt("texture2", 1);
}

// I am trying to really only render the graphics in the renderer, not the logic
// for movements or anything similar. The logic needs still be passed over to
// the renderer so it can render the changing graphics of course. But it's a
// pass-through, not the actual calculation

void Renderer::renderFrame() {

  m_width = window.getWidth();
  m_height = window.getHeight();

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  texture1.bind(0);
  texture2.bind(1);
  shader.use();

  glm::mat4 view = camera.getViewMatrix();
  glm::mat4 projection =
      glm::perspective(glm::radians(camera.zoom),
                       static_cast<float>(m_width) / m_height, 0.1f, 100.0f);

  shader.setMat4("view", view);
  shader.setMat4("projection", projection);

  // Render using precomputed transforms from Scene
  for (const auto &model : scene.cubeTransforms) {
    shader.setMat4("model", model);
    cubeMesh.draw();
  }
}

Renderer::~Renderer() {}

} // namespace Celestia
