#include "space.h"
#include "scene.h"

#include "space_vert.h"
#include "space_frag.h"


MeshPtr Space::mesh;
ShaderPtr Space::shader;
TexturePtr Space::texture;


Space::Space(int width,int height) {

    offset = 0;
    position.z = 1;

    if (!shader){
        shader = ShaderPtr(new Shader{space_vert, space_frag});
    }
    if (!mesh){
        mesh = MeshPtr(new Mesh{shader, "quad.obj"});
    }
}


Space::~Space() {
}


bool Space::Update(Scene &scene, float dt) {
    // offset += dt/5;

    GenerateModelMatrix();
    return true;
}


void Space::Render(Scene &scene) {

    shader->Use();

    shader->SetMatrix(modelMatrix, "ModelMatrix");

    mesh->Render();
}
