#include "Camera.h"


Camera::Camera() {
}

Camera::Camera(const glm::vec3& pos, const glm::vec3& worldUp, float pitch, float yaw) {
    this->Position = pos;
    this->WorldUp = worldUp;
    this->Pitch = pitch;
    this->Yaw = yaw;
    UpdateCameraRotation();

    MovementSpeed = 10.0f;
    MouseSensitivity = 1.0f;
    Fov = 45.0f;
}

glm::mat4 Camera::GetMatrix() const {
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == Direction::Forward)
        Position += Front * velocity;
    if (direction == Direction::Backward)
        Position -= Front * velocity;
    if (direction == Direction::Left)
        Position -= Right * velocity;
    if (direction == Direction::Right)
        Position += Right * velocity;
}

void Camera::ProcessMouse(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    UpdateCameraRotation();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Fov -= yoffset;
    if (Fov < 1.0f)
        Fov = 1.0f;
    if (Fov > 45.0f)
        Fov = 45.0f;
}

float Camera::GetFov() const {
    return Fov;
}

void Camera::UpdateCameraRotation() {
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
