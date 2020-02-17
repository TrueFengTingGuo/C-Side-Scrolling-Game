#include "AliveGameObject.h"

#include "GameObject.h"

AliveGameObject::AliveGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,float newHealth,float newDamage, int newLevel)
	: GameObject(entityPos, entityTexture, entityNumElements) {
	hp = newHealth + newLevel * growingHealth;
	damage = newDamage + newLevel * growingDamage;
}
