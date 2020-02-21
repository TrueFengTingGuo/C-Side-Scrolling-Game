#pragma once
#include "GameObject.h"
class AliveGameObject :
	public GameObject
{
public:

	AliveGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType,float newHealth, float newDamage, int newLevel);


	void setLevel(int newLevel) {
		hp += newLevel * growingHealth;
		damage += newLevel * growingDamage;
	}

private:
	float growingHealth = 17.0f;
	float growingDamage = 2.0f;

protected:
	
	float hp;
	float damage;
	int level;
};

