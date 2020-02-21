#pragma once
#include "AliveGameObject.h"
#include "PlayerGameObject.h"

class Enemy :public AliveGameObject
{

public:
	Enemy(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType,float newHealth, float newDamage, int newLevel, float newSpottingRange, PlayerGameObject* playerReference);


protected:
	float spottingRange;
	PlayerGameObject* playerGameObjectReference; // needs the  position
	virtual void update(double deltaTime) override;

private:
	void targetPlayer();
};

