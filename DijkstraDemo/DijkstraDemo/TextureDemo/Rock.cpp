#include "Rock.h"


Rock::Rock(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType,newMass, newHealth, newDamage, newLevel, newSpottingRange) {

	orignLocation = entityPos;
	objectRadius = 0.5f;
}

void Rock::update(double deltaTime)
{

	//gravity
	glm::vec3 Accel = glm::vec3(0.0f, -0.98f, 0.0f);
	glm::vec3 newVel = getVelocity() + Accel * (float)deltaTime;
	setVelocity(newVel);


	AliveGameObject::update(deltaTime);
}

void Rock::render(Shader& shader)
{
	shader.enable();
	shader.SetAttributes_sprite();

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(RockDouncingTime /4.0f, RockDouncingTime / 4.0f, RockDouncingTime / 4.0f));


	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

void Rock::restPosition(float DeltaTime)
{

	if (RockDouncingTime > 0) {
		RockDouncingTime -= DeltaTime;
	}
	else {
		position = orignLocation;
		RockDouncingTime = 3;
		setVelocity(glm::vec3(0.0f));
	}
	
}




