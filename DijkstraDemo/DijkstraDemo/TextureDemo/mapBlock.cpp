#include "mapBlock.h"

mapBlock::mapBlock(GameObjectHandler* h, glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType, int rowOrderInMap, int colOrderInMap)
	: GameObject(h, entityPosition, entityTexture, entityNumElements, newType)
{
	rowOrder = rowOrderInMap;
	colOrder = colOrderInMap;
	position = entityPosition + glm::vec3(rowOrder,colOrder,0.f);
}

void mapBlock::update(double deltaTime)
{
}
