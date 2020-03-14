#include "Enemy.h"
#include "Window.h"


Enemy::Enemy(GameObjectHandler* newh, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType,float newHealth, float newDamage, int newLevel,float newSpottingRange)
	: AliveGameObject(newh, entityPos, entityTexture, entityNumElements, myType, newHealth, newDamage, newLevel) {
	
	spottingRange = newSpottingRange;
}

void Enemy::update(double deltaTime) 
{
	if (hp <= 0) {
		active = false;
	}
	AliveGameObject::update(deltaTime);
}

void Enemy::targetPlayer()
{
}
