#include "scene.h"
#include "explosion.h"
#include "explosion_keyframe.h"

#include "explosion_vert.h"
#include "explosion_frag.h"


Explosion::Explosion() {

    maxAge = 0.6f;
    age = 0;

    rotation = glm::vec3(Rand(-PI, PI), Rand(-PI, PI), Rand(-PI, PI));
    rotMomentum = glm::vec3(Rand(-PI, PI), Rand(-PI, PI), Rand(-PI, PI))*3.0f;
    speed = glm::vec3(0.0f);

    if (!shader){
        shader = ShaderPtr(new Shader{explosion_vert, explosion_frag});
    }
    if (!texture){
        texture = TexturePtr(new Texture{"explosion.rgb", 512, 512});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "asteroid.obj"});
    }
}

Explosion::~Explosion() {
}


void Explosion::Render(Scene &scene) {

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


bool Explosion::Update(Scene &scene, float dt) {

    scale = scale * ( 1.0f + dt * 5.0f);
    rotation += rotMomentum * dt;
    position += speed * dt;

    //    auto keyframes = ExplosionKeyframePtr(new ExplosionKeyframe(speed));
    //    auto keyframe_speed = keyframes->Update(dt);
    //    position += keyframe_speed;

    age += dt;
    if (age > maxAge){
        return false;
    }
    GenerateModelMatrix();
    return true;
}

ShaderPtr Explosion::shader;
TexturePtr Explosion::texture;
MeshPtr Explosion::mesh;
