#pragma once

#include "EventBus.h"
#include "Events.h"

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
  RIGHT,
  UP,
  DOWN
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

  Camera(EventBus &eventBus, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
         float pitch = PITCH);

  glm::mat4 getViewMatrix();

private:
  EventBus &eventBus;

  const SDL_Scancode MOVE_FRONT = SDL_SCANCODE_W;
  const SDL_Scancode MOVE_LEFT = SDL_SCANCODE_A;
  const SDL_Scancode MOVE_BACK = SDL_SCANCODE_S;
  const SDL_Scancode MOVE_RIGHT = SDL_SCANCODE_D;
  const SDL_Scancode MOVE_UP = SDL_SCANCODE_SPACE;
  const SDL_Scancode MOVE_DOWN = SDL_SCANCODE_LCTRL;
  const SDL_Scancode MOVE_FAST = SDL_SCANCODE_LSHIFT;

  std::unordered_map<SDL_Scancode, Camera_Movement> movementKeys;
  std::unordered_map<SDL_Scancode, bool> activeKeys;

  void updateCameraVectors();
  void handleKeyInput(const KeyEvent &event);
  void updateMovement();

  void processKeyboard(Camera_Movement direction, float deltaTime);
  void processMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true);
  void processMouseScroll(float yoffset);

  float m_deltaTime = 0.0f;
  bool m_mouseVisible = false;
};
