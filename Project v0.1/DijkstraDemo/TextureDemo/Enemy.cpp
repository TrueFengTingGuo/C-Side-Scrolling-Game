#include "Enemy.h"
#include "Window.h"


Enemy::Enemy(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType,float newHealth, float newDamage, int newLevel,float newSpottingRange,PlayerGameObject* playerReference)
	: AliveGameObject(entityPos, entityTexture, entityNumElements, myType, newHealth, newDamage, newLevel) {
	
	playerGameObjectReference = playerReference;
	spottingRange = newSpottingRange;

}

void Enemy::update(double deltaTime)
{
}

void Enemy::targetPlayer()
{
}
