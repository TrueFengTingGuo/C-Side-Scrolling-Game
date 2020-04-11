#include "Turret.h"


Turret::Turret(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType, newMass, newHealth, newDamage, newLevel, newSpottingRange) {

	graph = new Graph(h->getPlayer()->getPosition(), map->getaLevelMap());
	objectRadius = 0.5f;
}

void Turret::update(double deltaTime)
{
	
	weapons[currentWeapon]->setPosition(position);
	//fire
	glm::vec3 playerPosition = glm::vec3(handler->getPlayer()->getPosition().x, handler->getPlayer()->getPosition().y, 0.0f);
	float distanceToShoot = glm::length(position - playerPosition);
	if (distanceToShoot < 10.0f) { // if distance to the next node is far enough

		weapons[currentWeapon]->setOrientation(-360.0f / 3.14159265 / 2.0f * atan2(position[1] - playerPosition.y, playerPosition.x - position[0]));
		weapons[currentWeapon]->fire();
	}

	AliveGameObject::update(deltaTime);
}

void Turret::render(Shader& shader)
{
	if (weapons[currentWeapon]->getFireCooldown() < 0.5f) {

		shader.enable();
		shader.SetAttributes_sprite();

		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, handler->savedTex[26]);

		// Setup the transformation matrix for the shader
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), getPosition());
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));


		// Set the transformation matrix in the shader
		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
		shader.setUniformMat4("transformationMatrix", transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	}

	AliveGameObject::render(shader);

}

