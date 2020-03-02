#include "PlayerGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(GameObjectHandler* h, glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType,float newHealth, float newDamage, int newLevel)
	: AliveGameObject(h, entityPos, entityTexture, entityNumElements,newType,newHealth,newDamage,newLevel) {
	currentWeapon = 0;
	experience = 0;
	currency = 0;
}

// Update function for moving the player object around
void PlayerGameObject::update(double deltaTime) {

	// reset velocity
	velocity[0] = 0;
	velocity[1] = 0;
	// Checking for player input and changing velocity
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		velocity[1] = 1.0f;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		velocity[1] = -1.0f;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		velocity[0] = 1.0f;
		// rotate player to face right
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		velocity[0] = -1.0f;
		// rotate player to face left
	}

	// Fire weapon
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (weapons.size() > 0)
			weapons[currentWeapon]->fire();
	}

	// Call the parent's update method to move the object
	GameObject::update(deltaTime);
}
