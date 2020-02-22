#include "PlayerGameObject.h"

#include "Window.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType,float newHealth, float newDamage, int newLevel)
	: AliveGameObject(entityPos, entityTexture, entityNumElements,newType,newHealth,newDamage,newLevel) {}

// Update function for moving the player object around
void PlayerGameObject::update(double deltaTime) {

	//gravity
	velocity.y -= 0.001f;
	//air Resistance
	velocity.x *= 0.9998f;

	// Checking for player input and changing velocity
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		velocity.y += 0.002f;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		velocity.y -= 0.002f;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		velocity.x += 0.005f;
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		velocity.x -= 0.005f;
	}

	// Call the parent's update method to move the object
	GameObject::update(deltaTime);
}
