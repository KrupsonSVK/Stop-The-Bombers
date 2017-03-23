#ifndef _PLAYER_H
#define _PLAYER_H

#include <texture.h>
#include <shader.h>
#include <mesh.h>

#include "object.h"

class Player : public Object {

public:
    Player();
    ~Player();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:
    float fireDelay;
    float fireRate;
    float angle;
    float speed ;
    float dp;

    const float flat_angle = .0f;
    const float max_angle = flat_angle + 0.5f;
    const float min_angle = flat_angle - 0.5f;
    const float max_position = 10.f;

    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};

typedef std::shared_ptr< Player > PlayerPtr;

#endif //_PLAYER_H
