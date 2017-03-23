#ifndef _SPACE_H
#define _SPACE_H

#include "mesh.h"
#include "object.h"


class Space : public Object {

public:
    Space();
    Space(int,int);
    ~Space();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:
    float offset;
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};

typedef std::shared_ptr< Space > SpacePtr;

#endif //_SPACE_H
