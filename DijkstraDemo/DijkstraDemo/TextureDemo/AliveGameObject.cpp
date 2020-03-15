#include "AliveGameObject.h"


#include "GameObject.h"


AliveGameObject::AliveGameObject(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string myType,float newHealth,float newDamage, int newLevel)
	: GameObject(h, entityPos, entityTexture, entityNumElements, myType) {
	level = newLevel;
	hp = newHealth + newLevel * growingHealth;
	damage = newDamage + newLevel * growingDamage;
}

void AliveGameObject::hurt(float d) {

		hp -= d;
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
	
	for each (Weapon* weapon in weapons)
	{
		if (weapon->getActive()) {
			weapon->update(deltaTime);
		}
		
	}
	GameObject::update(deltaTime);
}

void AliveGameObject::render(Shader& shader)
{
	
	for each (Weapon * weapon in weapons)
	{
		if (weapon->getActive()) {
			weapon->render(shader);
		}

	}
	GameObject::render(shader);
}

//fail when the weapon is not new
bool AliveGameObject::addWeapon(Weapon* w) {
	for (int count = 0; count < weapons.size(); count++) {
		if (weapons.at(count)->getName().compare(w->getName()) == 0) {
			
			return false;// add weapon failed
		}
	}
	//if there is no same weapon
	weapons.push_back(w);
	std::cout << "new Weapon added" << std::endl;
	return true; // add weapon successed
	
}

void AliveGameObject::cleanWeapons() {

	weapons.clear();
}