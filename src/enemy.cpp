#include "enemy.h"
#include "scrap.h"
#include "bomb.h"
#include "projectile.h"
#include "explosion.h"

#include "object_frag_nophong.h"
#include "object_vert_nophong.h"


Enemy::Enemy() {

    age = 0;
    bombDelay = 0;
    bombRate = 1.1f;

    scale *= 1.8f;
    speed = glm::vec3(Rand(5.0f, 6.0f), 0.0f, 0.0f);
    rotation ={-1.5f, 0.f,1.5f};

    if (!shader){
        shader = ShaderPtr(new Shader{object_vert_nophong, object_frag_nophong});
    }
    if (!texture){
        texture = TexturePtr(new Texture{"c17globemaster.rgb", 512, 512});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "c17globemaster.obj"});
    }
}

Enemy::~Enemy() {
}


bool Enemy::Update(Scene &scene, float dt) {

    age += dt;
    position += speed * dt;
    bombDelay += dt;

    if (age > 10.0f || position.x > 20){
        return false;
    }
    if (position.x > -6.f && position.x < 1.f && bombDelay > bombRate) {
        bombDelay = 0;

        auto bomb = BombPtr(new Bomb{speed});
        bomb->position = position + glm::vec3(0.0f, 0.0f, 0.3f);

        scene.objects.push_back(bomb);
    }

    for (auto obj : scene.objects) {

        if (obj.get() == this){
            continue;
        }

        auto enemy = std::dynamic_pointer_cast<Enemy>(obj);
        auto projectile = std::dynamic_pointer_cast<Projectile>(obj);

        if (!enemy && !projectile){
            continue;
        }
        if (enemy && age < 0.5f){
            continue;
        }
        if (glm::distance(position, obj->position) < (obj->scale.x + scale.x)*0.7f) {

            int pieces = 6;

            if (scale.x < 0.8f){
                pieces = 0;
            }
            if (projectile){
                projectile->Destroy();
            }
            Explode(scene, (obj->position+position)/2.0f, (obj->scale+scale)/2.0f, pieces);
            return false;
        }
    }
    GenerateModelMatrix();
    return true;
}


void Enemy::Explode(Scene &scene, glm::vec3 explPosition, glm::vec3 explScale, int pieces) {

    auto explosion = ExplosionPtr(new Explosion{});

    explosion->position = explPosition;
    explosion->scale = explScale;
    explosion->speed = speed/2.0f;

    scene.objects.push_back(explosion);

    for (auto i = 0; i < pieces; i++) {

        auto enemy = ScrapPtr(new Scrap());
        enemy->speed = speed + glm::vec3(Rand(-3.0f, 3.0f), Rand(0.0f, -5.0f), 0.0f);;
        enemy->position = position;
        enemy->rotMomentum = rotMomentum;

        auto factor = (GLfloat)pieces/2.0f;
        enemy->scale = scale / factor;

        scene.objects.push_back(enemy);
    }
}


void Enemy::Render(Scene &scene) {

    shader->Use();

    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");

    mesh->Render();
}


MeshPtr Enemy::mesh;
ShaderPtr Enemy::shader;
TexturePtr Enemy::texture;
