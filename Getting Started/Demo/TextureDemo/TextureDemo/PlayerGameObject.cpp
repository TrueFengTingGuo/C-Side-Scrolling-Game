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

	// special player updates go here

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::update(deltaTime);
}
