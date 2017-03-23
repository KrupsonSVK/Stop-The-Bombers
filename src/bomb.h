#ifndef _BOMB_H
#define _BOMB_H

#include "shader.h"
#include "mesh.h"
#include "object.h"

class Bomb : public Object {

public:
    Bomb(glm::vec3);
    ~Bomb();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

    void Destroy();

private:
    float age;
    glm::vec3 speed;

    static ShaderPtr shader;
    static MeshPtr mesh;
    static TexturePtr texture;
};

typedef std::shared_ptr< Bomb > BombPtr;

#endif //_BOMB_H
