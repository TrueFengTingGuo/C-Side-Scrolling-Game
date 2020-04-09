#pragma once
#include "GameObject.h"
class Partical :
	public GameObject
{
public:
	Partical(GameObjectHandler* h, glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, glm::vec4 newps_color);

	void render(Shader& shader, double deltaTime);


private:
	glm::vec4 ps_color;
	float mytime = 0.0;
};

