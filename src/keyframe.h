#ifndef _KEYFRAME_H
#define _KEYFRAME_H

#include <glm/vec3.hpp>

class Keyframe {

public:
    Keyframe();
    ~Keyframe();
    static float calculate(float a, float b, float val);

    float time;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif //_KEYFRAME_H
