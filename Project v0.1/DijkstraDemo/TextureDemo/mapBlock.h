#pragma once
#include "GameObject.h"
class mapBlock :
	public GameObject
{
public:
	mapBlock(GameObjectHandler* h, glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType,int rowOrderInMap,int colOrderInMap);
	void update(double deltaTime) override;
private:
	int rowOrder;
	int colOrder;
};

