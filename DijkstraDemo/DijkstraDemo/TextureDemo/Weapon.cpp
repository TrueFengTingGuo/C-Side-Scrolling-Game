#include "Weapon.h"
#include "AliveGameObject.h"

Weapon::Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, std::string newWeaponName,GLuint newBulletTexture, float fr, int a, int c, std::string bt, float newBulletSpeed, AliveGameObject* o)
	: GameObject(h, entityPos, entityTexture, entityNumElements, newType)
{
	fireRate = fr;
	cooldown = fr;
	ammo = a;
	cost = c;
	bulletType = bt;
	owner = o;
	BulletTexture = newBulletTexture;
	weaponName = newWeaponName;
	bulletSpeed = newBulletSpeed;

}

//copy weapon object from store to player
Weapon::Weapon(Weapon& w)
	: GameObject(w.handler, w.position, w.texture, w.numElements,w.type)
{
	fireRate = w.fireRate;
	cooldown = w.cooldown;
	ammo = w.ammo;
	cost = w.cost;
	bulletType = w.bulletType;
	owner = w.owner;
	BulletTexture = w.BulletTexture;
	weaponName = w.weaponName;
	bulletSpeed = w.bulletSpeed;
}

void Weapon::update(double deltaTime) {

	if(cooldown > 0) cooldown--;
	position = owner->getPosition();
	
}

void Weapon::render(Shader &shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	
	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 0.5f));


	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
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
	// temp bullet texture (how will the weapon know which bullet texture to use? Maybe in Bullet, choose a texture based on the type?)
	int bulletDamage = 2; // temp bullet damage (same problem as texture)
	glm::vec3 bulletPosition = glm::vec3(position + rotation);

	Bullet* newBullet = new Bullet(handler, bulletPosition, BulletTexture, numElements, bulletType, bulletDamage, bulletType);

	// Bullet velocity
	newBullet->setVelocity(bulletSpeed * glm::vec3(cos(3.14159265 / 360 * 2 * orientation), sin(3.14159265 / 360 * 2 * orientation), 0.0f));
	newBullet->setOrientation(orientation);
	handler->add(newBullet);

	cooldown = fireRate;
	ammo--;
}
