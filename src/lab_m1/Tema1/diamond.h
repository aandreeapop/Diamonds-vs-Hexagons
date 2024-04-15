#pragma once

#include "components/simple_scene.h"
#include "ObjectInGame.h"
#include "projectile.h"

class Diamond : public ObjectInGame
{
public:
	int row, column;
	int enemyOnRow = -1;
	std::vector<int> enemiesOnRow;
	Projectile star;
	bool startShooting = false;
	float lastShotTime = 0;

	Diamond() {
		this->radius = 60;
		this->star.hasStartedMoving = false;
	}
};