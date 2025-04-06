#pragma once

// clang-format off

#include <cmath>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// clang-format on

/**
 *
 * This is a central Camera Class. At the moment, it is implementing a simple
 * flying camera which should be enough for this Project.
 *
 * A Camera Object is handled by a Scene Class.
 *
 */

enum Camera_Movement {

  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;
  float yaw;
  float pitch;
  float movementSpeed;
  float mouseSensitivity;
  float zoom;

  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);
  Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
         float yaw, float pitch);

  glm::mat4 getViewMatrix();
  void processKeyboard(Camera_Movement direction, float deltaTime);
  void processMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true);
  void processMouseScroll(float yoffset);

private:
  void updateCameraVectors();
};
