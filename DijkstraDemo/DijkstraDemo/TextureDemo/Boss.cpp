#include "Boss.h"
Boss::Boss(Map* map, GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType, newHealth, newDamage, newLevel, newSpottingRange) {

	graph = new Graph(h->getPlayer()->getPosition(), map->getaLevelMap());

}


void Boss::update(double deltaTime)
{
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
		velocity = glm::normalize(nextDest - position) * 0.5f;
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
	if (distanceToShoot < 3.0f) { // if distance to the next node is far enough

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