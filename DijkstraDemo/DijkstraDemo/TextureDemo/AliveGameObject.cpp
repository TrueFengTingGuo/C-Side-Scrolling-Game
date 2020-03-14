#include "AliveGameObject.h"


#include "GameObject.h"


AliveGameObject::AliveGameObject(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string myType,float newHealth,float newDamage, int newLevel)
	: GameObject(h, entityPos, entityTexture, entityNumElements, myType) {
	level = newLevel;
	hp = newHealth + newLevel * growingHealth;
	damage = newDamage + newLevel * growingDamage;
}

void AliveGameObject::hurt(float d) {
	if (damageTimer == 0) {
		hp -= d;
		damageTimer = damageCooldown;
	}
}
//reverse the velocity and update the position
void AliveGameObject::reverseVelocity(double deltaTime)
{
	setVelocity(getVelocity() * (-1.0f));
	GameObject::update(deltaTime);
}

void AliveGameObject::update(double deltaTime)
{
	if (damageTimer > 0) damageTimer--;
	GameObject::update(deltaTime);
}

void AliveGameObject::render(Shader& shader)
{
	GameObject::render(shader);
}

void AliveGameObject::addWeapon(Weapon* w) {
	weapons.push_back(w);
	handler->add(w);
}