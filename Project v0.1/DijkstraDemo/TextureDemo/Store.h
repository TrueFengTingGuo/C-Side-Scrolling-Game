#pragma once
#include "GameObject.h"
#include "PlayerGameObject.h"
#include <vector>
#include "Weapon.h"

class Store :
	public GameObject
{
public:
	Store(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string newType, PlayerGameObject* playerReference);
	
	//getter
	Weapon& buyWeapon(std::string& weaponName);
	//

private:
	std::vector<Weapon*> weaponCollection;
	PlayerGameObject* playerGameObjectReference; // getcurrency, and position of player to move the store's position with player
};

