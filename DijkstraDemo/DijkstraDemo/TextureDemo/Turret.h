#pragma once
#include "Enemy.h"
#include "Graph.h"
#include "Map.h"

class Turret :
	public Enemy
{
public:
	Turret(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange);

	void update(double deltaTime) override;


private:
	glm::vec3 nextDest;
	int currenEndtNodeId = 0;
	int currenStartNodeId = 0;
	Graph* graph;
};

