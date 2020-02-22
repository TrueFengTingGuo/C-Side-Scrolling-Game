#pragma once

#include "GameObject.h"
#include "PlayerGameObject.h"
#include <vector>
#include "Weapon.h"


class Store :
	public GameObject
{
public:

	//need player gameobject when user buys items
	Store(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string newType, PlayerGameObject* playerReference);
	
	//but a weapon from store, return back a reference so the player can use copy constructor to construct the exact same
	//weapon
	Weapon& buyWeapon(std::string& weaponName);
	//

private:
	std::vector<Weapon*> weaponCollection;
	PlayerGameObject* playerGameObjectReference; // getcurrency, and position of player to move the store's position with player
	
	void levelup();
	void buyAmmo();
	void update(double deltaTime) override;

};

