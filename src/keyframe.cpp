#include "keyframe.h"


Keyframe::Keyframe(){
    position = glm::vec3(0,0,0);
    scale = glm::vec3(1,1,1);
    rotation = glm::vec3(0,0,0);
}

Keyframe::~Keyframe(){}


float  Keyframe::calculate(float val, float b, float a){

    return a * val + b * (1 - val);
}
