#ifndef _OBJECT_H
#define _OBJECT_H

#include <memory>
#include <list>
#include <map>
#include <cmath>

#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/detail/type_vec3.hpp>

#define PI M_PI

class Scene;

class Object {

public:
    Object();
    virtual ~Object();

    virtual bool Update(Scene &scene, float dt) = 0;
    virtual void Render(Scene &scene) = 0;

    bool player;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 modelMatrix;

protected:
    void GenerateModelMatrix();
    float Rand(float min, float max);
};

typedef std::shared_ptr<Object> ObjectPtr;

#endif //_OBJECT_H
