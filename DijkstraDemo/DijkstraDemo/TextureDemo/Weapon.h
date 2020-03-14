#pragma once
#include "GameObject.h"
#include "Bullet.h"

class AliveGameObject;

class Weapon :
	public GameObject
{
public:
		Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, std::string newWeaponName, GLuint newBulletTexture, float fr, int a, int c, std::string bt, AliveGameObject* o);
		Weapon(Weapon& w);

		virtual void update(double deltaTime) override;

		void render(Shader& shader);

		void fire();

		//getter
		std::string getName() { return weaponName; }

private:
	AliveGameObject* owner;
	float fireRate;
	float cooldown;
	int ammo;
	int cost;
	std::string bulletType;
	GLuint BulletTexture;
	std::string weaponName;
	
	
};

