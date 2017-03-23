#include "scene.h"
#include "smoke.h"

#include "object_vert_nophong.h"
#include "object_frag_nophong.h"

ShaderPtr Smoke::shader;
MeshPtr Smoke::mesh;
TexturePtr Smoke::texture;


Smoke::Smoke() {

    maxAge = 1.5f;
    age = 0;
    scale *= .2f;

    if (!shader){
        shader = ShaderPtr(new Shader{object_vert_nophong, object_frag_nophong});
    }
    if (!texture){
        texture = TexturePtr(new Texture{"cloud.rgb", 512, 512});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "smoke.obj"});
    }
}

Smoke::~Smoke() {
}


bool Smoke::Update(Scene &scene, float dt) {

    age += dt;
    speed += glm::vec3(0.01f, 0.01f ,0.01f);
    scale += speed * dt/6.f;

    if (age > maxAge){
        return false;
    }

    GenerateModelMatrix();
    return true;
}


void Smoke::Render(Scene &scene) {

    shader->Use();

    shader->SetFloat(1.0f-age/maxAge, "Transparency");

    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    mesh->Render();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}


void Smoke::Destroy() {
    age = 3.0f;
}
