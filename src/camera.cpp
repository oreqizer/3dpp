#include "camera.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float znear, float zfar) {
    m_perspective = glm::perspective(fov, aspect, znear, zfar);
    m_position = pos;

    // HARDCODED
    m_forward = glm::vec3(0, 0, 1);
    m_up = glm::vec3(0, 1, 0);
}

glm::mat4 Camera::GetViewProjection() const {
    return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
}
