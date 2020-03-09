#include "EnemyHelicopter.h"


EnemyHelicopter::EnemyHelicopter(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType, newHealth, newDamage, newLevel, newSpottingRange) {



}

void EnemyHelicopter::update(double deltaTime)
{
}

void EnemyHelicopter::findPlayer()
{
}


