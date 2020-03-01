#include "Weapon.h"

Weapon::Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float fr, int a, int c, std::string bt)
	: GameObject(h, entityPos, entityTexture, entityNumElements, newType)
{
	fireRate = fr;
	ammo = a;
	cost = c;
	bulletType = bt;
}

//copy weapon object from stroe to player
Weapon::Weapon(Weapon& w)
	: GameObject(w.handler, w.position, w.texture, w.numElements,w.type)
{
	fireRate = w.fireRate;
	ammo = w.ammo;
	cost = w.cost;
	bulletType = w.bulletType;
}

void Weapon::fire() {
}
