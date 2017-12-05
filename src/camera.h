#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera {
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float znear, float zfar);

    glm::mat4 GetViewProjection() const;
protected:
private:
    glm::mat4 m_perspective;
    glm::vec3 m_position;

    // Used for rotation:
    glm::vec3 m_forward; // where's forward from our POV
    glm::vec3 m_up;      // where's up from our POV
};

#endif // CAMERA_H
