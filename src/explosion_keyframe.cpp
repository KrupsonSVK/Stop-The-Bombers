
#include "explosion_keyframe.h"

ExplosionKeyframe::ExplosionKeyframe(auto this_speed) {

    elapsed_time=0.0f;

    auto frame = new Keyframe();
    frame->time = 1.0f;
    frame->position = this_speed * frame->time;
    frames[0] = frame;

    frame = new Keyframe();
    frame->time = 2.0f;
    frame->position = this_speed * frame->time;
    frames[1] = frame;

    frame = new Keyframe();
    frame->time = 2.5f;
    frame->position = this_speed * frame->time;
    frames[2] = frame;

    frame = new Keyframe();
    frame->time = 3.f;
    frame->position = this_speed * frame->time;
    frames[3] = frame;
}

ExplosionKeyframe::~ExplosionKeyframe() {
}


glm::vec3 ExplosionKeyframe::Update(float dt) {

    elapsed_time += dt;

    glm::vec3 speed;

    if (elapsed_time > frames[index]->time) {
        elapsed_time -= frames[index]->time;

        if (++index == 4)
            index = 1;
    }
    speed.z = Keyframe::calculate(elapsed_time / frames[index]->time, frames[index - 1]->rotation.y,frames[index]->rotation.y);
    speed.x = Keyframe::calculate(elapsed_time / frames[index]->time, frames[index - 1]->position.x, frames[index]->position.x);
    speed.y = Keyframe::calculate(elapsed_time / frames[index]->time, frames[index - 1]->position.y, frames[index]->position.y);

    return speed;
}
