#include "EnemyHelicopter.h"


EnemyHelicopter::EnemyHelicopter(Map *map,GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newHealth, float newDamage, int newLevel, float newSpottingRange)
	: Enemy(h, entityPos, entityTexture, entityNumElements, myType, newHealth, newDamage, newLevel, newSpottingRange) {

	graph = new Graph(h->getPlayer()->getPosition(), map->getaLevelMap());

}

void EnemyHelicopter::update(double deltaTime)
{
	//set path start
	glm::vec2 inGameWallSize = glm::vec2(1.0f, 1.0f);
	glm::vec3 enemyPositionOnTheTable = getPosition();
	enemyPositionOnTheTable.x = round(enemyPositionOnTheTable.x / inGameWallSize.x);
	enemyPositionOnTheTable.y = -round(enemyPositionOnTheTable.y / inGameWallSize.y);
	int n = graph->selectNodeUsingTable(enemyPositionOnTheTable.x, enemyPositionOnTheTable.y);

	graph->setStart(n);

	if (currenStartNodeId != graph->getStartId()) {
		currenStartNodeId = graph->getStartId();
		findPlayer();
		if (graph->sizeOfPathNodes() > 0) {
			nextDest = graph->popNodeFromPath();
		}

	}
	//set path start ---- Endhere

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
		if (graph->sizeOfPathNodes() > 0) {
			nextDest = graph->popNodeFromPath();
		}

	}
	//set path end  --- end  here	

	float distanceToNextNode = glm::length(position - nextDest);
	if (distanceToNextNode > 0.1f) {
		//cout << "next  dest" << graph->getNode(graph->getEndId()).getX() << " ," << graph->getNode(graph->getEndId()).getY() << endl;
		velocity = glm::normalize(nextDest - position) * 1.0f;
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
	
	
	GameObject::update(deltaTime);
}

void EnemyHelicopter::findPlayer()
{
	
	if (graph->getEndId() == graph->getStartId()) {
		
	}
	else {
		graph->pathfind();
	}

}


