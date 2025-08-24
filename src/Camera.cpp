// clang-format off
#include "pch.h"
#include "Camera.h"
#include "EventSystem.h"
// clang-format on

/**
 *
 * Position: Where the camera is in space. The starting point can be set in the
 * constructor as well.
 *
 * Front: This points to the negative z axis. Looking at OpenGL's coordinate
 * system, it can be seen, that the positive z axis, is showing "out of the
 * monitor" to the viewer.
 *
 * Up: A vector whichs tell the camera where "upwards" is
 *
 * Right: A vector which is orthogonal to the front and "worldUp" vectors.
 *
 * WorldUp: This is a Vector which indicates where the global "up" state is.
 * Normally it is the positive y direction.
 *
 * Yaw: The angle, which describes the rotation around the y-axis (horizontal)
 * If the starting value is -90 degrees, it looks into the negative z direction,
 * where the front is facing too.
 *
 * Pitch: The angle, which describes the rotation around the x-axis (vertical)
 */

namespace Celestia {
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

Camera::Camera(EventBus &eventBus, AppState &appState,
               CameraInputConfig inputConfig, glm::vec3 position, glm::vec3 up,
               float yaw, float pitch)
    : position(position), worldUp(up), movementSpeed(SPEED),
      mouseSensitivity(SENSITIVITY), zoom(ZOOM), eventBus(eventBus),
      appState(appState), inputConfig(inputConfig), m_yaw(yaw), m_pitch(pitch) {
  setupEventSubscriptions();

  front = glm::vec3(0.0f, 0.0f, -1.0f);
  updateCameraVectors();
}

void Camera::processMovement(float deltaTime) {

  // This check is not really necessary, but an extra safety check for not
  // processing any Movement
  if (appState.window.mouseVisible)
    return;

  float velocity = movementSpeed * deltaTime;
  if (inputState.boost)
    velocity = velocity * 2.5f;

  if (inputState.forward)
    applyMovement(front, velocity);
  if (inputState.backward)
    applyMovement(-front, velocity);
  if (inputState.left)
    applyMovement(-right, velocity);
  if (inputState.right)
    applyMovement(right, velocity);
  if (inputState.up)
    applyMovement(worldUp, velocity);
  if (inputState.down)
    applyMovement(-worldUp, velocity);
}

void Camera::applyMovement(glm::vec3 direction, float velocity) {
  position += glm::normalize(direction) * velocity;
}

void Camera::handleMouseMovement(float xoffset, float yoffset,
                                 bool constrainPitch) {
  xoffset *= appState.camera.mouseSensitivity;
  yoffset *= appState.camera.mouseSensitivity;

  m_yaw += xoffset;
  m_pitch -= yoffset;

  if (constrainPitch) {
    m_pitch = glm::clamp(m_pitch, -89.0f, 89.0f);
  }

  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors() {
  glm::vec3 newFront;
  newFront.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
  newFront.y = sin(glm::radians(m_pitch));
  newFront.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

  front = glm::normalize(newFront);
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}

void Camera::setupEventSubscriptions() {
  // Frame updates
  eventBus.on<FrameUpdateEvent>(
      // not saving deltaTime here in a member variable because only the
      // movement uses it, no other possible caclulations inside the camera
      // class
      [this](const auto &ev) { processMovement(ev.deltaTime); });

  // Keyboard input
  eventBus.on<KeyEvent>([this](const auto &ev) {
    if (!appState.window.mouseVisible) {

      // pressing w (trying to work with more structs)
      inputState.forward = (ev.scancode == inputConfig.moveForward)
                               ? ev.pressed
                               : inputState.forward;
      // pressing s
      inputState.backward = (ev.scancode == inputConfig.moveBackward)
                                ? ev.pressed
                                : inputState.backward;
      // pressing a
      inputState.left =
          (ev.scancode == inputConfig.moveLeft) ? ev.pressed : inputState.left;
      // pressing d
      inputState.right = (ev.scancode == inputConfig.moveRight)
                             ? ev.pressed
                             : inputState.right;
      // pressing space
      inputState.up =
          (ev.scancode == inputConfig.moveUp) ? ev.pressed : inputState.up;

      // pressing ctrl
      inputState.down =
          (ev.scancode == inputConfig.moveDown) ? ev.pressed : inputState.down;

      // pressing shift
      inputState.boost = (ev.scancode == inputConfig.boostSpeed)
                             ? ev.pressed
                             : inputState.boost;
    }
  });

  eventBus.on<MouseMoveEvent>([this](const auto &ev) {
    if (!appState.window.mouseVisible) {
      handleMouseMovement(ev.xrel, ev.yrel);
    }
  });

  eventBus.on<ToggleMouseVisibilityEvent>(
      [this](const auto &) { // Reset input state when mouse becomes visible
        // Important for stopping any old movement which was done before the
        // mouse was visible
        if (appState.window.mouseVisible) {
          inputState = {};
        }
      });

  eventBus.on<MouseScrollEvent>([this](const auto &ev) {
    if (!appState.window.mouseVisible) {
      zoom -= ev.yoffset;
      zoom = glm::clamp(zoom, 1.0f, 45.0f);
    }
  });
}
} // namespace Celestia
