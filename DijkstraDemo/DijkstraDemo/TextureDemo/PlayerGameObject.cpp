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
	//velocity[0] = 0;
	//velocity[1] = 0;
	/////////////////////////////// we shouldn't reset it, cause we may setVelcoity some everyelse///////////////////////

	// Checking for player input and changing velocity
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		setVelocity(glm::vec3(0.0f, 0.5f, 0.0f));
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		setVelocity(glm::vec3(0.0f, -0.5f, 0.0f));
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		setVelocity(glm::vec3(0.5f, 0.0f, 0.0f));
		// rotate player to face right
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		setVelocity(glm::vec3(-0.5f, 0.0f, 0.0f));
		// rotate player to face left
	}

	if (weapons.size() > 0) {
		// Aim weapon
		// get mouse input
		double mouseX, mouseY;
		glfwGetCursorPos(Window::getWindow(), &mouseX, &mouseY);

		mouseX = (mouseX - window_width_g / 2) * cameraZoom;
		mouseY = (mouseY - window_height_g / 2) * cameraZoom;

		// set orientation based on mouse position
		weapons[currentWeapon]->setOrientation(-360.0f / 3.14159265 / 2.0f * atan2(mouseY - position[1], mouseX - position[0]));

		// Fire weapon
		if (glfwGetKey(Window::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
			weapons[currentWeapon]->fire();
		}
	}

	AliveGameObject::update(deltaTime);
}
