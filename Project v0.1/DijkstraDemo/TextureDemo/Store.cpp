#include "Store.h"

Store::Store(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, PlayerGameObject* newPlayerReference)
	: GameObject(entityPos, entityTexture, entityNumElements, myType) {
	playerReference = newPlayerReference;
}

void Store::levelup()
{
}

void Store::buyAmmo()
{
}

void Store::update(double deltaTime)
{
}
