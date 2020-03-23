#pragma once
#include "AliveGameObject.h"
#include "PlayerGameObject.h"

class Enemy :public AliveGameObject
{

public:
	Enemy(GameObjectHandler* newh, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType,float newHealth, float newDamage, int newLevel, float newSpottingRange);


protected:
	float spottingRange;
	void update(double deltaTime) override;
private:
	void targetPlayer();
	
};

