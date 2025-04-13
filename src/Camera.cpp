// clang-format off
#include "pch.h"
#include "Camera.h"
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

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 4.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

Camera::Camera(EventBus &eventBus, glm::vec3 position, glm::vec3 up, float yaw,
               float pitch, CameraInputConfig inputConfig)
    : eventBus(eventBus), position(position), worldUp(up), yaw(yaw),
      pitch(pitch), inputConfig(inputConfig), movementSpeed(SPEED),
      mouseSensitivity(SENSITIVITY), zoom(ZOOM) {

  front = glm::vec3(0.0f, 0.0f, -1.0f);
  updateCameraVectors();
  setupEventSubscriptions();
}

void Camera::setupEventSubscriptions() {
  // Frame updates
  eventBus.subscribe<FrameUpdateEvent>(
      // not saving deltaTime here in a member variable because only the
      // movement uses it, no other possible caclulations inside the camera
      // class
      [this](const FrameUpdateEvent &ev) { processMovement(ev.deltaTime); });

  // Keyboard input
  eventBus.subscribe<KeyEvent>([this](const KeyEvent &ev) {
    if (!m_mouseVisible) {

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

  eventBus.subscribe<MouseMoveEvent>([this](const MouseMoveEvent &ev) {
    if (!m_mouseVisible) {
      handleMouseMovement(ev.xrel, ev.yrel);
    }
  });

  // Mouse visibility for deactivating movement
  eventBus.subscribe<MouseVisibilityChanged>(
      [this](const MouseVisibilityChanged &ev) {
        m_mouseVisible = ev.mouseVisible;
      });

  eventBus.subscribe<MouseScrollEvent>([this](const MouseScrollEvent &ev) {
    zoom -= ev.yoffset;
    zoom = glm::clamp(zoom, 1.0f, 45.0f);
  });

  eventBus.subscribe<MouseSensitivityChanged>(
      [this](const MouseSensitivityChanged &ev) {
        mouseSensitivity = ev.sensitivity;
      });
}

void Camera::processMovement(float deltaTime) {
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
  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  yaw += xoffset;
  pitch -= yoffset;

  if (constrainPitch) {
    pitch = glm::clamp(pitch, -89.0f, 89.0f);
  }

  updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors() {
  glm::vec3 newFront;
  newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  newFront.y = sin(glm::radians(pitch));
  newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  front = glm::normalize(newFront);
  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}