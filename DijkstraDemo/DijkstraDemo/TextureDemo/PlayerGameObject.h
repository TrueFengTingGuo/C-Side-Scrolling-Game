#pragma once

#include "AliveGameObject.h"

// Inherits from GameObject
class PlayerGameObject : public AliveGameObject {
public:

	PlayerGameObject(GameObjectHandler* h, glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, GLuint allStoredTex[], std::string newType, float newHealth, float newDamage, int newLevel);


	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	void switchWeapon();
	void render(Shader& shader) override;
	
	//getter
	int getCurrency() { return currency; }
	//setter
	void setCurrency(int changes) {  currency = changes; }
private:
	
	int experience;
	int currency;
	GLuint* storedTex; //stored textures
	glm::vec3 displayIconStartFrom; // (0,0) cood of the screen
};

