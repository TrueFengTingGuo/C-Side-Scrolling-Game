#include "Boss.h"
Boss::Boss(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newMass, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType,newMass, newHealth, newDamage, newLevel, newSpottingRange) {

	graph = new Graph(h->getPlayer()->getPosition(), map->getaLevelMap());
	objectRadius = 0.5f;
}


void Boss::update(double deltaTime)
{
	velocity[0] *= 0.998;
	velocity[1] *= 0.998;

	//set path start
	glm::vec2 inGameWallSize = glm::vec2(1.0f, 1.0f);
	glm::vec3 enemyPositionOnTheTable = getPosition();
	enemyPositionOnTheTable.x = round(enemyPositionOnTheTable.x / inGameWallSize.x);
	enemyPositionOnTheTable.y = -round(enemyPositionOnTheTable.y / inGameWallSize.y);
	int n = graph->selectNodeUsingTable(enemyPositionOnTheTable.x, enemyPositionOnTheTable.y);

	graph->setStart(n);	//set path start

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


	//ability one/////////////
	if (distanceToShoot < 10.0f) { // if distance to the next node is far enough

		//ability one
		if (contiuneShootingCurrentCD < 0 && contiuneShootingTimeCurrent > 0) {
			weapons[currentWeapon]->setOrientation(-360.0f / 3.14159265 / 2.0f * atan2(position[1] - playerPosition.y, playerPosition.x - position[0]));
			weapons[currentWeapon]->fire();
			contiuneShootingTimeCurrent -= deltaTime;
		}
		else {
			contiuneShootingCurrentCD -= deltaTime;
			if (contiuneShootingTimeCurrent < 0) {
				contiuneShootingCurrentCD = contiuneShootingCD;
				contiuneShootingTimeCurrent = contiuneShootingTime;
			}

			//ability two/////////////
			for each (GameObject * aGameObject in handler->getGameobjects())
			{
				if (aGameObject->getType().compare("PlayerBullet") == 0) {

					glm::vec3 directionToDodge = aGameObject->getPosition() - position;
					float distanceToDodge = glm::length(aGameObject->getPosition() - position);
					float speedToDodgeBasedOnDistance = -1.0f * (distanceToDodge - 0.2f);
					if (distanceToDodge < 4.0f) {

						velocity += directionToDodge * (-5.0f) * glm::abs((glm::pow(2.0f, speedToDodgeBasedOnDistance)))* (float)deltaTime;

					}

				}

				if (aGameObject->getType().compare("mapBlock") == 0 ||aGameObject->getType().compare("endBlock") == 0) {

					glm::vec3 directionToDodge = aGameObject->getPosition() - position;
					float distanceToDodge = glm::length(aGameObject->getPosition() - position);
					float speedToDodgeBasedOnDistance = -1.0f * (distanceToDodge - 0.2f);
					if (distanceToDodge < 2.5f) {

						velocity += directionToDodge * (-0.4f) * glm::abs((glm::pow(2.0f, speedToDodgeBasedOnDistance))) * (float)deltaTime;

					}

				}
			}

		}
		
	}
	
	

	AliveGameObject::update(deltaTime);
}

void Boss::findPlayer()
{

	if (graph->getEndId() == graph->getStartId()) {

	}
	else {
		graph->pathfind();
	}

}