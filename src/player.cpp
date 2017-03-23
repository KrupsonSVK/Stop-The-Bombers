#include "player.h"
#include "scene.h"
#include "enemy.h"
#include "projectile.h"
#include "explosion.h"

#include "object_frag_nophong.h"
#include "object_vert_nophong.h"

#include <GLFW/glfw3.h>

Player::Player() {

    //eyes = new Eyes();
    speed = 0;

    fireDelay = 0;
    fireRate = 0.3f;

    scale *= 1.2f;

    angle = flat_angle;
    rotation.z = -1.5f;
    scale.y *= 1.2f;
    dp=0.f;

    if (!shader){
        shader = ShaderPtr(new Shader{object_vert_nophong, object_frag_nophong});
    }
    if (!texture){
        texture = TexturePtr(new Texture{"f4phantom.rgb", 512, 512});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "f4phantom.obj"});
    }
}

Player::~Player() {
}


bool Player::Update(Scene &scene, float dt) {

    fireDelay += dt;
    player = true;

    for ( auto obj : scene.objects ) {

        if (obj.get() == this){
            continue;
        }

        auto enemy = std::dynamic_pointer_cast<Enemy>(obj);
        if (!enemy){
            continue;
        }

        if (glm::distance(position, enemy->position) < enemy->scale.y) {

            auto explosion = ExplosionPtr(new Explosion{});
            explosion->position = position;
            explosion->scale = scale * 3.0f;

            scene.objects.push_back(explosion);
            return false;
        }
    }

    if(scene.keyboard[GLFW_KEY_UP]) {

        if( angle > min_angle){
            angle-=dt;
        }
        if (dp < max_position){
            speed +=  0.1f;
        }
    }

    else if(scene.keyboard[GLFW_KEY_DOWN]) {
        if(angle < max_angle){
            angle+=dt;
        }
        if(dp > -max_position){
            speed -=  0.1f ;
        }
    }

    else{
        if( angle-0.01f > flat_angle){
            angle-=dt;
        }
        else if (angle+0.1f < flat_angle){
            angle+=dt;
        }
        if(dp-1.f > max_position){
            dp-=speed*dt;
        }
        else if(dp+1.f < -max_position){
            dp+=speed*dt;
        }
        speed = speed > .0f ? speed-=0.1f : speed < -.0f ? speed+=0.1f : .0f;
    }

    dp+=speed*dt;

    auto cam = scene.camera;

    if(dp>max_position){
        (*cam).position.y -= speed * dt;
    }
    if(dp<-max_position){
        (*cam).position.y += speed * dt;
    }
    rotation.x = angle;
    position.y = dp;

    if(scene.keyboard[GLFW_KEY_SPACE] && fireDelay > fireRate) {
        fireDelay = 0;

        auto projectile = ProjectilePtr(new Projectile{});
        projectile->position = position + glm::vec3(0.0f, 0.0f, 0.3f);

        scene.objects.push_back(projectile);
    }
    GenerateModelMatrix();
    return true;
}


void Player::Render(Scene &scene) {

    shader->Use();

    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "Texture");

    mesh->Render();
}

MeshPtr Player::mesh;
ShaderPtr Player::shader;
TexturePtr Player::texture;
