#pragma once
#include "AliveGameObject.h"
#include "PlayerGameObject.h"

class Enemy :public AliveGameObject
{

public:
	Enemy(GameObjectHandler* newh, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass,float newHealth, float newDamage, int newLevel, float newSpottingRange);
	glm::vec3 reflectWhenTouchWalls(GameObject* wall);

protected:
	float spottingRange;
	void update(double deltaTime) override;
private:
	void targetPlayer();

	
	
};

