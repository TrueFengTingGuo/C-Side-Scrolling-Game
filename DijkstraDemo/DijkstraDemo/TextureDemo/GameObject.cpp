#include "GameObject.h"

/*
	GameObject is responsible for handling the rendering and updating of objects in the game world
	The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
*/

GameObject::GameObject(GameObjectHandler* h, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass) {

	handler = h;

	position = entityPosition;
	initPosition = position;
	texture = entityTexture;
	numElements = entityNumElements;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	mass = newMass;

	//calcualting reverseMass
	if (mass == 0) {
		reverseMass = 0;
	}
	else {
		reverseMass = 1 / mass;
	}


	type = newType;

	active = true;

}

// Updates the GameObject's state. Can be overriden for children
void GameObject::update(double deltaTime) {
	// Update object position
	position += velocity * (float)deltaTime;
}

// Renders the GameObject using a shader
void GameObject::render(Shader &shader) {

	shader.enable();
	shader.SetAttributes_sprite();

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	

	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.0f,1.0f));


	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

bool GameObject::isCollided(GameObject* comparedObject)
{

	float distance = glm::length(comparedObject->getPosition() - getPosition());
	if (distance < comparedObject->getObjectRadius() + getObjectRadius()) {
		return true;
	}
	return false;


	
}
