#include "Weapon.h"

Weapon::Weapon(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType)
	: GameObject(entityPos, entityTexture, entityNumElements,newType)
{

}

//copy weapon object from stroe to player
Weapon::Weapon(Weapon& w)
	: GameObject(w.position, w.texture, w.numElements,w.type)
{

}

void Weapon::update(double deltaTime) {

	if (curfirerateTimer > 0) { 
		curfirerateTimer -= 1; 
	}
	else {
		if (glfwGetKey(Window::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
			curfirerateTimer = firerate;
		}
	}

}

