#include "generator.h"
#include "enemy.h"

bool Generator::Update(Scene &scene, float dt) {

    if (time > 4.f) {
        auto enemy = EnemyPtr(new Enemy());
        enemy->position = this->position;
        enemy->position.y += Rand(-15, 10);

        scene.objects.push_back(enemy);

        time = 0;
    }
    else{
        time += dt;
    }
    return true;
}

void Generator::Render(Scene &scene) {
}


Generator::~Generator() {
}


Generator::Generator() {
    time = 0;
}
