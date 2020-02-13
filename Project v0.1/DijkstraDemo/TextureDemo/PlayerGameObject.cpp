#include "PlayerGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements)
	: GameObject(entityPos, entityTexture, entityNumElements) {}

// Update function for moving the player object around
void PlayerGameObject::update(double deltaTime) {

	// Checking for player input and changing velocity
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		// This is where you should change the velocity vector of the player
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		// This is where you should change the velocity vector of the player
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		// This is where you should change the velocity vector of the player
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		// This is where you should change the velocity vector of the player
	}

	// Call the parent's update method to move the object
	GameObject::update(deltaTime);
}
