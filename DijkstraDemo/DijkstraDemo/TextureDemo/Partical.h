#pragma once

#include "GameObject.h"
class Partical :
	public GameObject
{
public:
	Partical(GameObjectHandler* h, glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, glm::vec4 newps_color);

	Partical(GameObjectHandler* h, glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, glm::vec4 newps_color, GameObject* newAttachedGameObject, float offestDistance);

	void update(double deltaTime) override;

	void render(Shader& shader, double deltaTime);

	//setter
	void setDontDestroyOnTime(bool boolVal) { dontDestroyOnTime = boolVal; }

private:
	glm::vec4 ps_color;
	float mytime = 0.0;
	float destroyingTime = 3.0f;
	GameObject* attachedGameObject;
	float offestDistance;
	bool dontDestroyOnTime = false;
};

