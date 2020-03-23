#pragma once
#include "Enemy.h"
#include "Graph.h"
#include "Map.h"

class Rock :
	public Enemy
{
public:
	Rock(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newHealth, float newDamage, int newLevel, float newSpottingRange);

	void update(double deltaTime) override;

private:
	glm::vec3 nextDest;
	int currenEndtNodeId = 0;
	int currenStartNodeId = 0;
	Graph* graph;
	float rockMass = 0.07f;
};

