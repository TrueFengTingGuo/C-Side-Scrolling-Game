#include "Bullet.h"
#include "Partical.h"
Bullet::Bullet(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, float d, std::string bt)
	: GameObject(h, entityPos, entityTexture, entityNumElements, newType,newMass)
{
	damage = d;
	bulletType = bt;
	restitution = 0.0f;
	objectRadius = 0.2f;
}

void Bullet::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	shader.enable();
	shader.SetAttributes_sprite();

	orientation = 360.0f / 3.14159265 / 2.0f * atan2(velocity.y, velocity.x);
	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.1f, 0.3f));


	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

void Bullet::update(double deltaTime)
{
	//gravity
	glm::vec3 Accel = glm::vec3(0.0f, -0.38f, 0.0f);
	glm::vec3 newVel = getVelocity() + Accel * (float)deltaTime;
	setVelocity(newVel);
	GameObject::update(deltaTime);
}
