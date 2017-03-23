#ifndef _PROJECTILE_H
#define _PROJECTILE_H

#include "shader.h"
#include "mesh.h"
#include "object.h"
#include "smoke.h"

class Projectile : public Object {

public:
    Projectile();
    ~Projectile();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

    void Destroy();

private:
    float age;
    glm::vec3 speed;
    glm::vec3 rotMomentum;

    float smokeDelay;
    float smokeRate;

    static ShaderPtr shader;
    static MeshPtr mesh;
    static TexturePtr texture;
};

typedef std::shared_ptr< Projectile > ProjectilePtr;

#endif //_PROJECTILE_H
