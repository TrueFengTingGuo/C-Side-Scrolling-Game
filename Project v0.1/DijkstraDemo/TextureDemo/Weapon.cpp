#include "Weapon.h"

Weapon::Weapon(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType)
	: GameObject(entityPos, entityTexture, entityNumElements,newType)
{
}

//copy weapon object from stroe to player
Weapon::Weapon(Weapon& w)
	: GameObject(w.position, w.texture, w.numElements,w.type)
{

}
