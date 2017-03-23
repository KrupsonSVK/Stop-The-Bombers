#ifndef _SCRAP_H
#define _SCRAP_H

#include <memory>

#include <GL/glew.h>

#include "scene.h"
#include "object.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"

class Scrap : public Object {

public:
    Scrap();
    ~Scrap();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

    glm::vec3 speed;
    glm::vec3 rotMomentum;

private:  
    void Explode(Scene &scene, glm::vec3 explPosition, glm::vec3 explScale, int pieces);

    float age;
    const float max_age = 5.f;

    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};

typedef std::shared_ptr<Scrap> ScrapPtr;

#endif //_SCRAP_H
