#include "Rock.h"


Rock::Rock(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType,newMass, newHealth, newDamage, newLevel, newSpottingRange) {


	objectRadius = 0.5f;
}

void Rock::update(double deltaTime)
{

	
	glm::vec3 playerPosition = glm::vec3(handler->getPlayer()->getPosition().x, handler->getPlayer()->getPosition().y, 0.0f);
	float distanceToShoot = glm::length(position - playerPosition);
	//gravity
	glm::vec3 Accel = glm::vec3(0.0f, -0.98f, 0.0f);
	glm::vec3 newVel = getVelocity() + Accel * (float)deltaTime;
	setVelocity(newVel);


	AliveGameObject::update(deltaTime);
}

void Rock::render(Shader& shader)
{
	GameObject::render(shader);
}



