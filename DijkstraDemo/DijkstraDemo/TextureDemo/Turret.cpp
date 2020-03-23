#include "Turret.h"


Turret::Turret(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType, newHealth, newDamage, newLevel, newSpottingRange) {

	graph = new Graph(h->getPlayer()->getPosition(), map->getaLevelMap());

}

void Turret::update(double deltaTime)
{
	
	weapons[currentWeapon]->setPosition(position);
	//fire
	glm::vec3 playerPosition = glm::vec3(handler->getPlayer()->getPosition().x, handler->getPlayer()->getPosition().y, 0.0f);
	float distanceToShoot = glm::length(position - playerPosition);
	if (distanceToShoot < 4.0f) { // if distance to the next node is far enough

		weapons[currentWeapon]->setOrientation(-360.0f / 3.14159265 / 2.0f * atan2(position[1] - playerPosition.y, playerPosition.x - position[0]));
		weapons[currentWeapon]->fire();
	}

	AliveGameObject::update(deltaTime);
}



