#pragma once
#include "GameObject.h"

class Bullet :
	public GameObject
{
public:
	Bullet(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, float d, std::string bt);

	void render(Shader& shader) override;
	void update(double deltaTime)override;
	// Getters
	inline float getDamage() { return damage; }

private:
	float damage;
	std::string bulletType;
	float explosionCountdown = 2.0f;

};
