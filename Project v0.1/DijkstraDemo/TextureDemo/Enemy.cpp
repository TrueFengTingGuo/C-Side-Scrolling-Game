#include "Enemy.h"
#include "Window.h"

Enemy::Enemy(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float newHealth, float newDamage, int newLevel,float newSpottingRange,PlayerGameObject* playerReference)
	: AliveGameObject(entityPos, entityTexture, entityNumElements, newHealth, newDamage, newLevel) {
	playerGameObjectReference = playerReference;
	spottingRange = newSpottingRange;
}
