#pragma once
#include "GameObject.h"
#include "Window.h"
class Weapon :
	public GameObject
{
public:
		Weapon(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType,float damage,float firerate,float bulletSpeed,int ammo, int prize,float fireRange);
		Weapon(Weapon& w);

		void update(double deltaTime);
		

private:
	float damage;
	float firerate;
	float bulletSpeed;
	int ammo;
	int prize;
	float fireRange;
	float curfirerateTimer;

};

