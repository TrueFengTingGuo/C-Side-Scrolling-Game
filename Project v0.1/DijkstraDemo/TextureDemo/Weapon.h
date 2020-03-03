#pragma once
#include "GameObject.h"
#include "Bullet.h"

class AliveGameObject;

class Weapon :
	public GameObject
{
public:
		Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float fr, int a, int c, std::string bt, AliveGameObject* o);
		Weapon(Weapon& w);

		virtual void update(double deltaTime) override;

		void fire();
private:
	AliveGameObject* owner;
	float fireRate;
	float cooldown;
	int ammo;
	int cost;
	std::string bulletType;


};

