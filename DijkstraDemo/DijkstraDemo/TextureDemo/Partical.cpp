#include "Partical.h"

Partical::Partical(GameObjectHandler* h, glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::string newType, float newMass, glm::vec4 newps_color)
	: GameObject(h, entityPosition, entityTexture, entityNumElements, newType, newMass) {

	ps_color = newps_color;
}

void Partical::render(Shader& shader, double deltaTime){
	
	
	mytime += (float)deltaTime;

	// Bind the particle texture
	glBindTexture(GL_TEXTURE_2D, texture);

	shader.enable();
	shader.SetAttributes_particle();


	// Set the transformation matrix for the shader
	glm::mat4 scaling = glm::scale(glm::mat4(1.0), glm::vec3(0.2, 0.2, 0.2));
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);


	// Set the transformation matrix in the shader
	// TODO: Multiply your new transformations to make the transformationMatrix
	glm::mat4 transformationMatrix = translationMatrix * scaling;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	shader.setUniform4f("ps_color", ps_color);
	shader.setUniform1f("time", mytime);
	// Draw the entity
	glDrawElements(GL_TRIANGLES, 204000, GL_UNSIGNED_INT, 0);

}