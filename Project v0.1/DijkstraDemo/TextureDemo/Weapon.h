#pragma once
#include "GameObject.h"
class Weapon :
	public GameObject
{
public:
		Weapon(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType);
		Weapon(Weapon& w);
};

