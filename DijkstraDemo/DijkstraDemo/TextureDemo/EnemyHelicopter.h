#pragma once
#include "Enemy.h"
class EnemyHelicopter :
	public Enemy
{
public:
	EnemyHelicopter(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newHealth, float newDamage, int newLevel, float newSpottingRange);
	
	void update(double deltaTime) override;
	void findPlayer();
};

