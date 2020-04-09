#pragma once

#include "GameObject.h"
#include "Weapon.h"
using namespace std;

class AliveGameObject :
	public GameObject
{
public:

	AliveGameObject(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, float newHealth, float newDamage, int newLevel);


	void setLevel(int newLevel) {
		hp += newLevel * growingHealth;
		damage += newLevel * growingDamage;
	}

	virtual void update(double deltaTime) override;
	virtual void render(Shader& shader) override;

	bool addWeapon(Weapon* w);
	Weapon* findAWeapon(string weaponName);
	void cleanWeapons();
	void hurt(float d);

	//reverse the velocity and update the position
	void reverseVelocity(double deltaTime);
	// Getters
	inline float getHealth() { return hp; }

	// Setters
	inline void setHealth(float newHp) { hp = newHp; }
	inline void setCurrentWeaponActiveTo(bool change) { weapons[currentWeapon]->setActive(change);}

private:
	float growingHealth = 5.0f;
	float growingDamage = 1.0f;

	int damageCooldown = 60, damageTimer = damageCooldown;

protected:
	
	float hp;
	float damage;
	int level = 0;
	std::vector<Weapon*> weapons;
	int currentWeapon;
	
};


