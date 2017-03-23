#include "scene.h"
#include "projectile.h"

#include "object_vert_nophong.h"
#include "object_frag_nophong.h"

ShaderPtr Projectile::shader;
MeshPtr Projectile::mesh;
TexturePtr Projectile::texture;


Projectile::Projectile() {

    age = 0;

    smokeDelay = 0;
    smokeRate = 0.02f;

    rotation.y = 1.5f;
    speed = glm::vec3(0.0f, -5.0f, 0.0f);
    rotMomentum = glm::vec3(Rand(-PI/4.0f, PI/4.0f),0.0f,  0.0f);

    if (!shader){
        shader = ShaderPtr(new Shader{object_vert_nophong, object_frag_nophong});
    }
    if (!texture){
        texture = TexturePtr(new Texture{"missile.rgb", 512, 512});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "missile.obj"});
    }
}

Projectile::~Projectile() {
}


bool Projectile::Update(Scene &scene, float dt) {

    smokeDelay += dt;
    age += dt;
    speed += glm::vec3(-0.2f, 0.f ,0.0f);
    rotation += rotMomentum;
    position += speed * dt;

    if (age > 5.0f){
        return false;
    }

    if(smokeDelay > smokeRate) {
        smokeDelay = 0;

        auto smoke = SmokePtr(new Smoke{});
        smoke->position = position + glm::vec3(1.0f, 0.0f, 0.0f);

        scene.objects.push_back(smoke);
    }
    GenerateModelMatrix();
    return true;
}


void Projectile::Render(Scene &scene) {

    shader->Use();

    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");

    mesh->Render();
}


void Projectile::Destroy() {
    age = 6.0f;
}
