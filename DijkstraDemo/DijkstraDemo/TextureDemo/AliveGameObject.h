#ifndef ALIVEGAMEOBJECT_H
#define ALIVEGAMEOBJECT_H


#include "GameObject.h"
#include "Weapon.h"

class AliveGameObject :
	public GameObject
{
public:

	AliveGameObject(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType,float newHealth, float newDamage, int newLevel);


	void setLevel(int newLevel) {
		hp += newLevel * growingHealth;
		damage += newLevel * growingDamage;
	}

	void addWeapon(Weapon* w);

private:
	float growingHealth = 17.0f;
	float growingDamage = 2.0f;

protected:
	
	float hp;
	float damage;
	int level;
	std::vector<Weapon*> weapons;
};

#endif
