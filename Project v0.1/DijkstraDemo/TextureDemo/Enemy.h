#pragma once
#include "AliveGameObject.h"
#include "PlayerGameObject.h"

class Enemy :public AliveGameObject
{

public:
	Enemy(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float newHealth, float newDamage, int newLevel, float newSpottingRange, PlayerGameObject* playerReference);

protected:
	float spottingRange;
	PlayerGameObject* playerGameObjectReference; // needs the  position

private:
	void targetPlayer();
};

