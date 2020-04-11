#pragma once
#include "Enemy.h"
#include "Graph.h"
#include "Map.h"

class Rock :
	public Enemy
{
public:
	Rock( GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange);

	void update(double deltaTime) override;
	void render(Shader& shader) override;
	void restPosition(float DeltaTime);

	float RockDouncingTime= 0;
private:
	glm::vec3 orignLocation;
	int currenEndtNodeId = 0;
	int currenStartNodeId = 0;
	float rockMass = 0.07f;
};

