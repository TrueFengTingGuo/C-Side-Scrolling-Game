#include "Store.h"



Store::Store(GLuint newStoredTex[], GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType)
	: GameObject(h, entityPos, entityTexture, entityNumElements, myType) {
	storedTex = newStoredTex;
	glm::vec3 DefaultPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	//add Pistol
	weaponCollection.push_back(Weapon(h, DefaultPosition, storedTex[4], 6, "Weapon", storedTex[6], 60.0f, 5, 0, "TestBullet", h->getPlayer()));
	weaponName.push_back("Pistol");
}

Weapon* Store::buyWeapon(std::string weaponName)
{	
	Weapon *newWeapon;
	for (int count = 0 < weaponName.size(); count++;) {
		if (weaponName.compare(weaponName[weaponName.begin+count])) {
			newWeapon = new Weapon(weaponCollection[weaponCollection.begin + count]);
		}
	}
	return newWeapon;
}

void Store::levelup()
{
}

void Store::buyAmmo()
{

}

void Store::update(double deltaTime)
{
}

