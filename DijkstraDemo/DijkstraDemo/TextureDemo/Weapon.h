#pragma once
#include "GameObject.h"
#include "Bullet.h"

class AliveGameObject;

class Weapon :
	public GameObject
{
public:
		Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, std::string newWeaponName, GLuint newBulletTexture, float fr, int a, int c, int weaponDamage,std::string bt,float newBulletSpeed, AliveGameObject* o);
		Weapon(Weapon& w);

		virtual void update(double deltaTime) override;

		void render(Shader& shader);

		void fire();

		//getter
		std::string getName() { return weaponName; }
		int getCost() { return cost; }
		int getAmmo() { return ammo; }
		float getFireRate() { return fireRate; }

		//setter
		void setAmmo(int newAmmo) { ammo = newAmmo; }
		void setFireRateAmp(float newFireRate) { fireRateAmp = newFireRate; }

		AliveGameObject* owner;
private:
	
	float fireRate;
	float fireRateAmp = 1;
	float bulletSpeed;
	float cooldown;
	int bulletDamage = 2;
	int ammo;
	int cost;
	std::string bulletType;
	GLuint BulletTexture;
	std::string weaponName;
	
	
};

