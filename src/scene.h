#ifndef _SCENE_H
#define _SCENE_H

#include <memory>
#include <map>
#include <list>

#include "camera.h"
#include "object.h"

typedef struct mouse{
    double x, y;
    bool left, right;
} Mouse;


class Scene {

public:
    Scene();
    ~Scene();

    bool Update(float);
    void Render();

    CameraPtr camera;
    std::list< ObjectPtr > objects;
    std::map< int, int > keyboard;
    Mouse mouse;
};

typedef std::shared_ptr< Scene > ScenePtr;

#endif // _SCENE_H
