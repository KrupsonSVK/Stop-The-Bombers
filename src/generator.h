#ifndef _GENERATOR_H
#define _GENERATOR_H

#include <random>
#include "object.h"
#include "scene.h"

class Generator : public Object {

public:
    Generator();
    ~Generator();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

    float time;
};

typedef std::shared_ptr< Generator > GeneratorPtr;

#endif //_GENERATOR_H
