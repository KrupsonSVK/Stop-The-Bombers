#ifndef _EXPLOSION_KEYFRAME_H
#define _EXPLOSION_KEYFRAME_H

#include <texture.h>
#include <shader.h>
#include <mesh.h>

#include "object.h"
#include "shader.h"
#include "scene.h"
#include "object_vert_nophong.h"
#include "object_vert_nophong.h"
#include "keyframe.h"


class ExplosionKeyframe {

public:
    ExplosionKeyframe(auto);
    ~ExplosionKeyframe();
    glm::vec3 Update(float dt);

private:
    Keyframe *frames[4];
    float elapsed_time = 0;
    int index = 1;
};

typedef std::shared_ptr< ExplosionKeyframe > ExplosionKeyframePtr;

#endif //_EXPLOSION_KEYFRAME_H
