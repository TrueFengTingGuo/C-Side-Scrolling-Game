#include "EnemyHelicopter.h"


EnemyHelicopter::EnemyHelicopter(Map *map,GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType,newMass, newHealth, newDamage, newLevel, newSpottingRange) {

	graph = new Graph(h->getPlayer()->getPosition(), map->getaLevelMap());
	objectRadius = 0.5f;
}

void EnemyHelicopter::update(double deltaTime)
{

	//set path start
	glm::vec2 inGameWallSize = glm::vec2(1.0f, 1.0f);
	glm::vec3 enemyPositionOnTheTable = getPosition();
	enemyPositionOnTheTable.x = round(enemyPositionOnTheTable.x / inGameWallSize.x);
	enemyPositionOnTheTable.y = -round(enemyPositionOnTheTable.y / inGameWallSize.y);
	int n = graph->selectNodeUsingTable(enemyPositionOnTheTable.x, enemyPositionOnTheTable.y);

	graph->setStart(n);	//set path start

	/*if (currenStartNodeId != graph->getStartId()) {
		currenStartNodeId = graph->getStartId();
		if (graph->sizeOfPathNodes() > 0) {
			nextDest = graph->popNodeFromPath(); //get next node
		}

	}*/


	//set path end
	glm::vec3 playerPositionOnTheTable = handler->getPlayer()->getPosition();
	playerPositionOnTheTable.x = round(playerPositionOnTheTable.x / inGameWallSize.x);
	playerPositionOnTheTable.y = -round(playerPositionOnTheTable.y / inGameWallSize.y);

	n = graph->selectNodeUsingTable(playerPositionOnTheTable.x, playerPositionOnTheTable.y);
	//cout << "target position" << graph->getNode(n).getX() << " ," << graph->getNode(n).getY() << endl;

	graph->setEnd(n);
	if (currenEndtNodeId != graph->getEndId()) {
		findPlayer();
		currenEndtNodeId = graph->getEndId();
		if (graph->sizeOfPathNodes() > 0) {//take out the starting Node
			nextDest = graph->popNodeFromPath(); //get the next position where the enemy should go
		}
		if (graph->sizeOfPathNodes() > 0) {
			nextDest = graph->popNodeFromPath(); //get the next position where the enemy should go
		}

	}
	//set path end 

	float distanceToNextNode = glm::length(position - nextDest);
	if (distanceToNextNode > 0.1f) { // if distance to the next node is far enough
		//cout << "next  dest" << graph->getNode(graph->getEndId()).getX() << " ," << graph->getNode(graph->getEndId()).getY() << endl;
		velocity += glm::normalize(nextDest - position) * (float)deltaTime;
	}
	else {
		if (graph->sizeOfPathNodes() > 0) {
			nextDest = graph->popNodeFromPath();
			//exit(0);
		}
		else
		{
			velocity = glm::vec3(0.0f);
		}
	}

	weapons[currentWeapon]->setPosition(position);
	//fire
	glm::vec3 playerPosition = glm::vec3(handler->getPlayer()->getPosition().x, handler->getPlayer()->getPosition().y, 0.0f);
	float distanceToShoot = glm::length(position - playerPosition);
	if (distanceToShoot < 4.0f) { // if distance to the next node is far enough

		weapons[currentWeapon]->setOrientation(-360.0f / 3.14159265 / 2.0f * atan2(position[1] - playerPosition.y, playerPosition.x - position[0]));
		weapons[currentWeapon]->fire();
	}

	//ability one/////////////
	for each (GameObject * aGameObject in handler->getGameobjects())
	{

		if (aGameObject->getType().compare("mapBlock") == 0 || aGameObject->getType().compare("endBlock") == 0) {

			glm::vec3 directionToDodge = aGameObject->getPosition() - position;
			float distanceToDodge = glm::length(aGameObject->getPosition() - position);
			float speedToDodgeBasedOnDistance = -1.0f * (distanceToDodge - 0.2f);
			if (distanceToDodge < 2.0f) {

				velocity += directionToDodge * (-0.3f) * glm::abs((glm::pow(2.0f, speedToDodgeBasedOnDistance))) * (float)deltaTime;

			}

		}
	}
	AliveGameObject::update(deltaTime);
}


void EnemyHelicopter::render(Shader& shader)
{
	if(weapons[currentWeapon]->getFireCooldown() < 0.5f) {

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

	//std::cout << "hELICOPTER rendered  " << position.x << " , "<< position.y << std::endl;

	AliveGameObject::render(shader);

}
void EnemyHelicopter::findPlayer()
{

	if (graph->getEndId() == graph->getStartId()) {

	}
	else {
		graph->pathfind();
	}

}



