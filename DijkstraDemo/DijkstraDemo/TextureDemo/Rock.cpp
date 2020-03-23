#include "Rock.h"


Rock::Rock(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType, newHealth, newDamage, newLevel, newSpottingRange) {

	graph = new Graph(h->getPlayer()->getPosition(), map->getaLevelMap());

}

void Rock::update(double deltaTime)
{

	
	glm::vec3 playerPosition = glm::vec3(handler->getPlayer()->getPosition().x, handler->getPlayer()->getPosition().y, 0.0f);
	float distanceToShoot = glm::length(position - playerPosition);
	if (distanceToShoot < 3.0f) { // if distance to the next node is far enough

		// set velocity
		velocity.y -= 0.98 * rockMass;
	}

	AliveGameObject::update(deltaTime);
}



