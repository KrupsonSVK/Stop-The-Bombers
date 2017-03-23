#ifndef _SMOKE_H
#define _SMOKE_H

#include "shader.h"
#include "mesh.h"
#include "object.h"

class Smoke : public Object {

public:
    Smoke();
    ~Smoke();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

    void Destroy();
private:
    float age;
    float maxAge;
    glm::vec3 speed;

    static ShaderPtr shader;
    static MeshPtr mesh;
    static TexturePtr texture;
};

typedef std::shared_ptr< Smoke > SmokePtr;

#endif //_SMOKE_H
