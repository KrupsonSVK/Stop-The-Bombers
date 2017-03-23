#ifndef _CAMERA_H
#define _CAMERA_H

#include <memory>

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/detail/type_vec3.hpp>
#include <GL/glew.h>
#include <GL/gl.h>

class Camera {

public:
    Camera(float fow = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f);
    ~Camera();

    void Update();

    glm::vec3 up;
    glm::vec3 position;
    glm::vec3 back;
    float angle;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
};
typedef std::shared_ptr< Camera > CameraPtr;

#endif //_CAMERA_H
