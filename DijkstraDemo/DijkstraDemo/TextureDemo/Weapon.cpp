#include "Weapon.h"
#include "AliveGameObject.h"

Weapon::Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float fr, int a, int c, std::string bt, AliveGameObject* o)
	: GameObject(h, entityPos, entityTexture, entityNumElements, newType)
{
	fireRate = fr;
	cooldown = fr;
	ammo = a;
	cost = c;
	bulletType = bt;
	owner = o;
}

//copy weapon object from store to player
Weapon::Weapon(Weapon& w)
	: GameObject(w.handler, w.position, w.texture, w.numElements,w.type)
{
	fireRate = w.fireRate;
	ammo = w.ammo;
	cost = w.cost;
	bulletType = w.bulletType;
}

void Weapon::update(double deltaTime) {
	if(cooldown > 0) cooldown--;
	position = owner->getPosition();
}


void Weapon::fire() {
	if (cooldown > 0) {
		//std::cout << "Weapon cooling down." << std::endl;
		return;
	}
	if (ammo == 0) {
		//std::cout << "Weapon out of ammo." << std::endl;
		return;
	}
	//std::cout << "Weapon fired." << std::endl;
	GLuint bulletTexture = texture; // temp bullet texture (how will the weapon know which bullet texture to use? Maybe in Bullet, choose a texture based on the type?)
	int bulletDamage = 1; // temp bullet damage (same problem as texture)
	glm::vec3 bulletPosition = glm::vec3(position + rotation);

	Bullet* newBullet = new Bullet(handler, bulletPosition, bulletTexture, numElements, "Bullet", bulletDamage, bulletType);

	// Bullet velocity
	float bulletSpeed = 10.0f;
	newBullet->setVelocity(bulletSpeed * glm::vec3(cos(3.14159265 / 360 * 2 * orientation), sin(3.14159265 / 360 * 2 * orientation), 0.0f));

	handler->add(newBullet);

	cooldown = fireRate;
	ammo--;
}
