#pragma once

#include "GameObject.h"
#include "PlayerGameObject.h"
#include <vector>
#include "Weapon.h"


class Store :
	public GameObject
{
public:
	Store(GLuint newStoredTex[],GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string newType);
	
	//getter
	Weapon* buyWeapon(std::string weaponName);
	//

private:
	std::vector<Weapon> weaponCollection;
	std::vector<std::string> weaponName;
	void levelup();
	void buyAmmo();
	void update(double deltaTime) override;
	GLuint *storedTex;

};

