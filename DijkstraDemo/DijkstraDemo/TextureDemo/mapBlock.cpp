#include "mapBlock.h"

mapBlock::mapBlock(GameObjectHandler* h, glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, int rowOrderInMap, int colOrderInMap)
	: GameObject(h, entityPosition, entityTexture, entityNumElements, newType,newMass)
{
	rowOrder = rowOrderInMap;
	colOrder = colOrderInMap;
	objectRadius = 0.5f;
}

void mapBlock::update(double deltaTime)
{
	GameObject::update(deltaTime);
}
