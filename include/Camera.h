#pragma once

/**
 *
 * This is a central Camera Class. At the moment, it is implementing a simple
 * flying camera which should be enough for this Project.
 *
 * A Camera Object is handled by a Scene Class.
 *
 */

namespace Celestia {

// forward declarations
class EventBus;

struct CameraInputConfig {
  SDL_Scancode moveForward = SDL_SCANCODE_W;
  SDL_Scancode moveBackward = SDL_SCANCODE_S;
  SDL_Scancode moveLeft = SDL_SCANCODE_A;
  SDL_Scancode moveRight = SDL_SCANCODE_D;
  SDL_Scancode moveUp = SDL_SCANCODE_SPACE;
  SDL_Scancode moveDown = SDL_SCANCODE_LCTRL;
  SDL_Scancode boostSpeed = SDL_SCANCODE_LSHIFT;
};

class Camera {
public:
  Camera(EventBus &eventBus, CameraInputConfig inputConfig = {},
         glm::vec3 position = glm::vec3(0.0f),
         glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f,
         float pitch = 0.0f);

  glm::mat4 getViewMatrix() const;
  void updateCameraVectors();

  // Camera state
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;

  // Camera parameters
  float movementSpeed;
  float mouseSensitivity;
  float zoom;

private:
  EventBus &eventBus;
  CameraInputConfig inputConfig;

  struct InputState {
    bool forward = false;
    bool backward = false;
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool boost = false;
  } inputState;

  void setupEventSubscriptions();
  void processMovement(float deltaTime);
  void applyMovement(glm::vec3 direction, float velocity);

  void handleMouseMovement(float xoffset, float yoffset,
                           bool constrainPitch = true);

  // Rotation angles
  float m_yaw;
  float m_pitch;

  // Internal state
  bool m_mouseVisible;
};

} // namespace Celestia
