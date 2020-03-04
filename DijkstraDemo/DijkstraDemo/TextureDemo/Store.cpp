#include "Store.h"



Store::Store(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, PlayerGameObject* newPlayerReference)
	: GameObject(h, entityPos, entityTexture, entityNumElements, myType) {
	playerGameObjectReference = newPlayerReference;
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

