#pragma once
#include "GameObject.h"
#include "Bullet.h"

class Weapon :
	public GameObject
{
public:
		Weapon(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float fr, int a, int c, std::string bt);
		Weapon(Weapon& w);

		void fire();
private:
	float fireRate;
	int ammo;
	int cost;
	std::string bulletType;


};

