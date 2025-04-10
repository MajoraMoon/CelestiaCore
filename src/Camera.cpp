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
Camera::Camera(EventBus &eventBus, glm::vec3 position, glm::vec3 up, float yaw,
               float pitch)
    : eventBus(eventBus), position(position), worldUp(up), yaw(yaw),
      pitch(pitch), front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED),
      mouseSensitivity(SENSITIVITY), zoom(ZOOM) {

  eventBus.subscribe<FrameUpdateEvent>([this](const Event &e) {
    const auto &ev = static_cast<const FrameUpdateEvent &>(e);
    deltaTime = ev.deltaTime;
    updateMovement();
  });

  movementKeys = {{SDL_SCANCODE_W, FORWARD}, {SDL_SCANCODE_S, BACKWARD},
                  {SDL_SCANCODE_A, LEFT},    {SDL_SCANCODE_D, RIGHT},
                  {SDL_SCANCODE_SPACE, UP},  {SDL_SCANCODE_LCTRL, DOWN}};

  eventBus.subscribe<KeyEvent>([this](const Event &e) {
    const auto &ev = static_cast<const KeyEvent &>(e);
    handleKeyInput(ev);
  });

  eventBus.subscribe<MouseMoveEvent>([this](const Event &e) {
    const auto &ev = static_cast<const MouseMoveEvent &>(e);
    processMouseMovement(ev.xrel, ev.yrel);
  });

  eventBus.subscribe<MouseScrollEvent>([this](const Event &e) {
    const auto &ev = static_cast<const MouseScrollEvent &>(e);
    processMouseScroll(ev.yoffset);
  });

  updateCameraVectors();
}

Camera::Camera(EventBus &eventBus, float posX, float posY, float posZ,
               float upX, float upY, float upZ, float yaw, float pitch)
    : eventBus(eventBus), position(glm::vec3(posX, posY, posZ)),
      worldUp(glm::vec3(upX, upY, upZ)), yaw(yaw), pitch(pitch),
      front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED),
      mouseSensitivity(SENSITIVITY), zoom(ZOOM) {

  movementKeys = {{SDL_SCANCODE_W, FORWARD}, {SDL_SCANCODE_S, BACKWARD},
                  {SDL_SCANCODE_A, LEFT},    {SDL_SCANCODE_D, RIGHT},
                  {SDL_SCANCODE_SPACE, UP},  {SDL_SCANCODE_LCTRL, DOWN}};

  eventBus.subscribe<FrameUpdateEvent>([this](const Event &e) {
    const auto &ev = static_cast<const FrameUpdateEvent &>(e);
    deltaTime = ev.deltaTime;
  });

  eventBus.subscribe<KeyEvent>([this](const Event &e) {
    const auto &ev = static_cast<const KeyEvent &>(e);
    handleKeyInput(ev);
  });

  eventBus.subscribe<MouseMoveEvent>([this](const Event &e) {
    const auto &ev = static_cast<const MouseMoveEvent &>(e);
    processMouseMovement(ev.xrel, ev.yrel);
  });

  eventBus.subscribe<MouseScrollEvent>([this](const Event &e) {
    const auto &ev = static_cast<const MouseScrollEvent &>(e);
    processMouseScroll(ev.yoffset);
  });

  updateCameraVectors();
}

void Camera::handleKeyInput(const KeyEvent &event) {

  auto it = movementKeys.find(event.scancode);
  if (it != movementKeys.end()) {
    activeKeys[event.scancode] = event.pressed;
  }
}

void Camera::updateMovement() {
  for (const auto &key : activeKeys) {
    if (key.second) { // If the key is pressed
      processKeyboard(movementKeys[key.first], movementSpeed * deltaTime);
    }
  }
}

glm::mat4 Camera::getViewMatrix() {
  return glm::lookAt(position, position + front, up);
}

/**
 * Movements speed is multiplied with deltaTime to garanty a smooth movement
 * indepented from the framerate. If not multiplied with deltaTime, this camera
 * would be either hella fast or a diashow, depending on the framerate
 */

void Camera::processKeyboard(Camera_Movement direction, float velocity) {

  if (direction == FORWARD)
    position += front * velocity;
  if (direction == BACKWARD)
    position -= front * velocity;
  if (direction == LEFT)
    position -= right * velocity;
  if (direction == RIGHT)
    position += right * velocity;
  if (direction == UP)
    position += worldUp * velocity;
  if (direction == DOWN)
    position -= worldUp * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset,
                                  bool constrainPitch) {

  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  yaw += xoffset;
  pitch -= yoffset;

  if (constrainPitch) {
    if (pitch > 89.0f)
      pitch = 89.0f;
    if (pitch < -89.0f)
      pitch = -89.0f;
  }

  updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {

  zoom -= (float)yoffset;
  if (zoom < 1.0f)
    zoom = 1.0f;
  if (zoom > 45.0f)
    zoom = 45.0f;
}

// magic math to update the cameras view
void Camera::updateCameraVectors() {
  glm::vec3 Front;
  Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  Front.y = sin(glm::radians(pitch));
  Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  front = glm::normalize(Front);

  right = glm::normalize(glm::cross(front, worldUp));
  up = glm::normalize(glm::cross(right, front));
}
