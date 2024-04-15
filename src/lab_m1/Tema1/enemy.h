#pragma once

#include "components/simple_scene.h"
#include "ObjectInGame.h"

class Enemy : public ObjectInGame
 {
 public:
    bool notInScene = true;
    int row = 0;
    int numberOfCollisions = 0;
    Enemy() {
        this->name = "hexagons";
        this->radius = 40;
    }
};
    


        
