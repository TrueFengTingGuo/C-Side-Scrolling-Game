#pragma once

#include "AliveGameObject.h"

// Inherits from GameObject
class PlayerGameObject : public AliveGameObject {
public:

	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newHealth, float newDamage, int newLevel);


	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
private:
	int currentWeapon;
	int experience;
	int currency;
};
