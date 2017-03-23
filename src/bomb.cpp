#include "scene.h"
#include "bomb.h"

#include "object_vert_nophong.h"
#include "object_frag_nophong.h"

ShaderPtr Bomb::shader;
MeshPtr Bomb::mesh;
TexturePtr Bomb::texture;

Bomb::Bomb(glm::vec3 thisSpeed) {

    age = 0;
    rotation.y = -1.5f;
    speed = thisSpeed;

    if (!shader){
        shader = ShaderPtr(new Shader{object_vert_nophong, object_frag_nophong});
    }
    if (!texture){
        texture = TexturePtr(new Texture{"nuclear.rgb", 512, 512});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "nuclear.obj"});
    }
}

Bomb::~Bomb() {
}


bool Bomb::Update(Scene &scene, float dt) {

    age += dt;
    speed += glm::vec3( 0.01f ,-0.05f , 0.0f);

    if(rotation.y < 0.f){
        rotation.y += dt;
    }
    position += speed * dt;

    if (age > 5.0f){
        return false;
    }
    GenerateModelMatrix();
    return true;
}


void Bomb::Render(Scene &scene) {

    shader->Use();

    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");

    mesh->Render();
}


void Bomb::Destroy() {
    age = 6.0f;
}
