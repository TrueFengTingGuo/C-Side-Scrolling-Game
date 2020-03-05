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

	virtual void update(double deltaTime) override;

	void addWeapon(Weapon* w);
	void hurt(float d);

	// Getters
	inline float getHealth() { return hp; }

	// Setters
	inline void setHealth(float newHp) { hp = newHp; }

private:
	float growingHealth = 17.0f;
	float growingDamage = 2.0f;

	int damageCooldown = 60, damageTimer = damageCooldown;

protected:
	
	float hp;
	float damage;
	int level;
	std::vector<Weapon*> weapons;
};

#endif
