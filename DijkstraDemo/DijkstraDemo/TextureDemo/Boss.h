#pragma once
#include "Enemy.h"
#include "Graph.h"
#include "Map.h"
class Boss :
	public Enemy
{
public:
	Boss(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange);
	void update(double deltaTime) override;
	void findPlayer();

private:
	glm::vec3 nextDest;
	int currenEndtNodeId = 0;
	int currenStartNodeId = 0;
	Graph* graph;



	//ability Cooldown
	float contiuneShootingCD = 15.0f;
	float contiuneShootingCurrentCD = 15.0f;
	float contiuneShootingTime = 10.0f;
	float contiuneShootingTimeCurrent =10.0f;
};

