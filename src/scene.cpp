#include "scene.h"
#include "camera.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

Scene::Scene() {
}

Scene::~Scene() {
}


bool Scene::Update(float dt) {

    if(this->keyboard[GLFW_KEY_RIGHT]) {
        //        (*camera).angle +=  3 * dt;
        //        (*camera).position += glm::vec3(sin(),0.0f,cos((angle)*camera).angle)*5.f;
        //        (*camera).viewMatrix=glm::lookAt(position,scene->position,up);
        (*camera).position.z -= 3 * dt;
        (*camera).position.x -= 2.5 *  dt;
    }
    else if(this->keyboard[GLFW_KEY_LEFT]) {
        //        (*camera).angle +=  3 * dt;
        //        (*camera).position = glm::vec(sin(),0.0f,cos(angle))*5.f;
        //        (*camera).viewMatrix=glm::lookAt(pos,scene->position,up);
        (*camera).position.z += 3 * dt;
        (*camera).position.x += 2.5 *  dt;
    }

    camera->Update();

    auto iterator = std::begin(objects);

    while (iterator != std::end(objects)) {

        auto obj = iterator->get();

        if (!obj->Update(*this, dt)){
            iterator = objects.erase(iterator);

            if ((*iterator)->player){
                return false;
            }
        }
        else ++iterator;
    }
    return true;
}


void Scene::Render() {

    for (auto obj : objects ){
        obj->Render(*this);
    }
}

