#pragma once

#include "components/simple_scene.h"
#include "ObjectInGame.h"

class Projectile : public ObjectInGame
{
public:
    float angularStep = 0;
    bool hasStartedMoving = false;
    float lastShootTime = 0;
    float shootInterval = 5;
    Projectile(float translateX, float translateY) {
        this->name = "star";
        this->radius = 40;
        this->translateX = translateX;
        this->translateY = translateY;
    }
    Projectile(){
        this->name = "star";
        this->radius = 35.2f;
    }
};