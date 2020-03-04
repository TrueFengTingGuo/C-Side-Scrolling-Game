#pragma once
#include "GameObject.h"

class Bullet :
	public GameObject
{
public:
	Bullet(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float d, std::string bt);

private:
	float damage;
	std::string bulletType;


};
