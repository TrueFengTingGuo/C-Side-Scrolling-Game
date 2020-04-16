#pragma once

#include "AliveGameObject.h"

// Inherits from GameObject
class PlayerGameObject : public AliveGameObject {
public:

	PlayerGameObject(GameObjectHandler* h, glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, GLuint allStoredTex[], std::string newType, float newMass, float newHealth, float newDamage, int newLevel);


	// Update function for moving the player object around
	virtual void update(double deltaTime) override;
	void render(Shader& shader) override;

	void switchWeapon();
	void addExperience(int tempExperience);

	
	//getter
	int getCurrency() { return currency; }

	//setter
	void setCurrency(int changes) {  currency = changes; }
	void setSpeedBuffTime(float changes) { speedBuffTime = changes; }

private:
	
	int experience;
	int neededExperience = 5;
	int currency;
	GLuint* storedTex; //stored textures
	glm::vec3 displayIconStartFrom; // (0,0) cood of the screen

	//power up buff
	float speedBuffVolumn = 3.9f; //percentage
	float currentSpeedBuffVolumn = 1.0f; //percentage
	float speedBuffTime = 0.0f;

	//switchWeapon cd
	float switchWeaponCD = 0.1f;
	float cuurentSwitchWeaponCD = 0.0f;


	//dodge cd
	float dodgeCD = 1.0f;
	float currentdodgeCD = 0.0f;

	//FIRE Amp partical timing
	bool isAmped = false;
	Partical* fireAmpPartical = NULL;
};

