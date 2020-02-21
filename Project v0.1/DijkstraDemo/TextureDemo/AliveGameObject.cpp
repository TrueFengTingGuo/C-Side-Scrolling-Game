#include "AliveGameObject.h"


#include "GameObject.h"


AliveGameObject::AliveGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string myType,float newHealth,float newDamage, int newLevel)
	: GameObject(entityPos, entityTexture, entityNumElements, myType) {

	hp = newHealth + newLevel * growingHealth;
	damage = newDamage + newLevel * growingDamage;
}
