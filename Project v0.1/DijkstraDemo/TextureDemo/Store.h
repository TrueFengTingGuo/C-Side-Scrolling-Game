#pragma once

#include "GameObject.h"

#include "PlayerGameObject.h"

class Store :
	public GameObject
{
public:
	Store (glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, PlayerGameObject* newPlayerReference);
	void levelup();
	void buyAmmo();
	void update(double deltaTime) override;

private:
	PlayerGameObject* playerReference;

};

