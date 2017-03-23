#ifndef _ENEMY_H
#define _ENEMY_H

#include <memory>

#include <GL/glew.h>

#include "scene.h"
#include "object.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"


class Enemy : public Object {

public:
    Enemy();
    ~Enemy();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:  
    void Explode(Scene &scene, glm::vec3 explPosition, glm::vec3 explScale, int pieces);

    float age;
    float bombDelay;
    float bombRate;
    glm::vec3 speed;
    glm::vec3 rotMomentum;

    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};

typedef std::shared_ptr<Enemy> EnemyPtr;

#endif //_ENEMY_H
