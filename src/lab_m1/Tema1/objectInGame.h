#pragma once

#include <string>
#include "components/simple_scene.h"


class ObjectInGame : public gfxc::SimpleScene
 {
 public:
    std::string name;
    bool inScene = false;
    bool collision = false;
    float translateX, translateY;
    float scaleX = 1, scaleY = 1;
    float radius;
    unsigned int color;
 };
    

