#pragma once
#include "GameObject.h"
#include "Bullet.h"

class AliveGameObject;

class Weapon :
	public GameObject
{
public:
		Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, std::string newWeaponName, GLuint newBulletTexture, float fr, int a, int c, std::string bt,float newBulletSpeed, AliveGameObject* o);
		Weapon(Weapon& w);

		virtual void update(double deltaTime) override;

		void render(Shader& shader);

		void fire();

		//getter
		std::string getName() { return weaponName; }
		int getCost() { return cost; }
		int getAmmo() { return ammo; }

		//setter
		void setAmmo(int newAmmo) { ammo = newAmmo; }


		AliveGameObject* owner;
private:
	
	float fireRate;
	float bulletSpeed;
	float cooldown;
	int ammo;
	int cost;
	std::string bulletType;
	GLuint BulletTexture;
	std::string weaponName;
	
	
};

