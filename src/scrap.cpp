#include "scrap.h"
#include "projectile.h"
#include "explosion.h"

#include "object_frag_nophong.h"
#include "object_vert_nophong.h"

Scrap::Scrap() {

    age = 0; //reset

    if (!shader){
        shader = ShaderPtr(new Shader{object_vert_nophong, object_frag_nophong});
    }
    if (!texture){
        texture = TexturePtr(new Texture{"asteroid.rgb", 512, 512});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "asteroid.obj"});
    }
}

Scrap::~Scrap() {
}


bool Scrap::Update(Scene &scene, float dt) {

    age += dt;
    position += speed * dt;

    if (age > max_age){
        return false;
    }
    for (auto obj : scene.objects) {

        if (obj.get() == this){
            continue;
        }
        auto scrap = std::dynamic_pointer_cast<Scrap>(obj);

        if (!scrap || (scrap && age < 0.5f)){
            continue;
        }
        if (glm::distance(position, obj->position) < (obj->scale.x + scale.x)*0.7f) {

            int pieces = (scale.x < 0.5) ? 0 : 4;
            Explode(scene,(obj->position+position)/2.0f, (obj->scale+scale)/2.0f, pieces);

            return false;
        }
    }
    GenerateModelMatrix();
    return true;
}


void Scrap::Explode(Scene &scene, glm::vec3 explPosition, glm::vec3 explScale, int pieces) {

    auto explosion = ExplosionPtr(new Explosion{});
    explosion->position = explPosition;
    explosion->scale = explScale;
    explosion->speed = speed/2.0f;

    scene.objects.push_back(explosion);

    for (auto i = 0; i < pieces; i++) {

        auto scrap = ScrapPtr(new Scrap());
        scrap->speed = speed + glm::vec3(Rand(-3.0f, 3.0f), Rand(0.0f, -5.0f), 0.0f);;
        scrap->position = position;
        scrap->rotMomentum = rotMomentum;

        float factor = (float)pieces/2.0f;
        scrap->scale = scale / factor;
        scene.objects.push_back(scrap);
    }
}


void Scrap::Render(Scene &scene) {
    shader->Use();

    shader->SetFloat(1.0f-age/max_age, "Transparency");

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

MeshPtr Scrap::mesh;
ShaderPtr Scrap::shader;
TexturePtr Scrap::texture;
