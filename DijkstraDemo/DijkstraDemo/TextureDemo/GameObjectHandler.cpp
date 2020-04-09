#include "GameObjectHandler.h"
#include "PlayerGameObject.h"
#include "Enemy.h"
#include "Map.h"
#include "Partical.h"


GameObjectHandler::GameObjectHandler(GLuint newSavedTex[]) {
	savedTex = newSavedTex;
}

// Updates all game objects
void GameObjectHandler::update(double deltaTime) {

	std::vector<int> inactiveObjectsIndex;
	int gameObjectsListSize = gameObjects.size(); //size may change during the collision dectection

	for (int i = 0; i < gameObjectsListSize; i++) {

		// Get the current object
		GameObject* currentGameObject = gameObjects[i];
		

		//if current gameobject is active
		if (currentGameObject->getActive()) {

			// Updates game objects
			currentGameObject->update(deltaTime);

			//gameobjects Collision
			for (int j = 0; j < gameObjects.size(); j++) {
				GameObject* otherGameObject = gameObjects[j];
				float distance = glm::length(currentGameObject->getPosition() - otherGameObject->getPosition());
				if (distance < 0.8f) {

					//player bullet
					if (currentGameObject->getType().compare("PlayerBullet") == 0) {

						//bullet vs Enemy
						if ((otherGameObject->getType().compare("EnemyHelicopter") == 0|| otherGameObject->getType().compare("Turret") == 0) && otherGameObject->getActive() == true) {
							
							gameObjects.erase(gameObjects.begin() + i); // remove bullet
							 collisionReslove(currentGameObject, otherGameObject);
   							((Enemy*)otherGameObject)->hurt(((Bullet*)currentGameObject)->getDamage());
							particals.push_back(new Partical(this, currentGameObject->getPosition(), savedTex[24], 6, "Partical",0.0f, glm::vec4(0.2f, 1.0f, 1.0f, 1.0f)));
							

							// enemy dies 
							if (((AliveGameObject*)otherGameObject)->getHealth() <= 0) {
								otherGameObject->setActive(false);
								player->setCurrency(player->getCurrency() + 2); //earn money
								player->addExperience(10); //earn Experience
							}
							
							break;
						}

						//bullet vs Rock
						if (otherGameObject->getType().compare("Rock") == 0 && otherGameObject->getActive() == true) {
							gameObjects.erase(gameObjects.begin() + i); // remove bullet

							((Enemy*)otherGameObject)->hurt(((Bullet*)currentGameObject)->getDamage());

							// enemy dies 
							if (((AliveGameObject*)otherGameObject)->getHealth() <= 0) {
								otherGameObject->setActive(false);
								player->setCurrency(player->getCurrency() + 10); //earn money
								player->addExperience(10); //earn Experience
							}

							break;
						}

						//bullet vs Boss
						if (otherGameObject->getType().compare("Boss") == 0 && otherGameObject->getActive() == true) {
							gameObjects.erase(gameObjects.begin() + i); // remove bullet

							collisionReslove(currentGameObject, otherGameObject);
							((Enemy*)otherGameObject)->hurt(((Bullet*)currentGameObject)->getDamage());

							// enemy dies 
							if (((AliveGameObject*)otherGameObject)->getHealth() <= 0) {
								otherGameObject->setActive(false);
								player->setCurrency(player->getCurrency() + 15); //earn money
								player->addExperience(10); //earn Experience
							}

							break;
						}

						if (otherGameObject->getType().compare("mapBlock") == 0) {

							gameObjects.erase(gameObjects.begin() + i);
							particals.push_back(new Partical(this, currentGameObject->getPosition(), savedTex[22], 6, "Partical",0.0f, glm::vec4(0.2f, 1.0f, 1.0f, 1.0f)));
							break;
						}
					}

					//all Player
					if (currentGameObject->getType().compare("Player") == 0) {

						if (otherGameObject->getType().compare("mapBlock") == 0) {

							//set to reversed velcoity
							collisionReslove(currentGameObject, otherGameObject);
							//((PlayerGameObject*)currentGameObject)->reverseVelocity(deltaTime);
							
						}

						if (otherGameObject->getType().compare("endBlock") == 0) {

							currentGameObject->setActive(false);
							loadMapAgain = true;

						}

						if (otherGameObject->getType().compare("powerUp") == 0) {

							((PlayerGameObject*)currentGameObject)->setSpeedBuffTime(1.0f);

						}

						if (otherGameObject->getType().compare("Rock") == 0|| otherGameObject->getType().compare("EnemyHelicopter") == 0 || otherGameObject->getType().compare("Turret") == 0) {

							collisionReslove(currentGameObject, otherGameObject);
						}
					}

					//all EnemyBullet
					if (currentGameObject->getType().compare("EnemyBullet") == 0) {
						if (otherGameObject->getType().compare("mapBlock") == 0) {

							gameObjects.erase(gameObjects.begin() + i);
							
							break;
						}

						if (otherGameObject->getType().compare("Player") == 0) {

							collisionReslove(currentGameObject, otherGameObject);
							gameObjects.erase(gameObjects.begin() + i);
							particals.push_back(new Partical(this, currentGameObject->getPosition(), savedTex[23], 6, "Partical",0.0f, glm::vec4(0.2f, 1.0f, 1.0f, 1.0f)));
							
							((AliveGameObject*)otherGameObject)->hurt(((Bullet*)currentGameObject)->getDamage());
							// Player dies 
							if (((AliveGameObject*)otherGameObject)->getHealth() <= 0) {
								otherGameObject->setActive(false);
								exit(0);
							}
							break;
						}
					}

					//all boss
					if (currentGameObject->getType().compare("Boss") == 0) {
						if (otherGameObject->getType().compare("mapBlock") == 0) {

							//set to reversed velcoity
							collisionReslove(currentGameObject, otherGameObject);
						}
					}
					
					//all Enmey
					if (currentGameObject->getType().compare("EnemyHelicopter") == 0 || currentGameObject->getType().compare("Turret") == 0){
						if (otherGameObject->getType().compare("mapBlock") == 0) {

							//set to reversed velcoity
							collisionReslove(currentGameObject, otherGameObject);
						}
					}

				}

			}
		}
		gameObjectsListSize = gameObjects.size(); //refresh
	}


	CleanOutOfRangeGameObject();
	
}

// Renders all game objects
void GameObjectHandler::render(Shader& shader) {

	for (int i = 0; i < gameObjects.size(); i++) {
		// Get the current object
		GameObject* currentGameObject = gameObjects[i];
		if (currentGameObject->getActive()) {
			//reset color uniform.
			GLint color_loc = glGetUniformLocation(shader.getShaderID(), "colorMod");
			glUniform3f(color_loc, 0.0f, 0.0f, 0.0f);

			// Render game objects
			currentGameObject->render(shader);
		}
		
	}
}

// Renders all game objects
void GameObjectHandler::renderPSS(Shader& shader, double deltaTime) {

	for (int i = 0; i < particals.size(); i++) {
		// Get the current object
		Partical* currentGameObject = particals[i];


		// Render game objects
		currentGameObject->render(shader, deltaTime);

	}
}
void GameObjectHandler::add(GameObject* go) {
	if (go->getType().compare("Player") == 0){ 
		player = ((PlayerGameObject*)go);
		std::cout << "player added" << std::endl;
	}

	if (go->getType().compare("Store") == 0) {
		store = ((Store*)go);
		std::cout << "store added" << std::endl;
	}
	gameObjects.push_back(go);

}


void GameObjectHandler::setActiveByType(std::string type,bool setBoolVar)
{

	for (int i = 0; i < gameObjects.size(); i++) {
		GameObject* currentGameObject = gameObjects[i];
		if (currentGameObject->getType().compare(type) == 0) {
			currentGameObject->setActive(setBoolVar);
		}
	}
}

void GameObjectHandler::deleteByType(std::string type)
{

	for (int i = 0; i < gameObjects.size(); i++) {
		GameObject* currentGameObject = gameObjects[i];
		if (currentGameObject->getType().compare(type) == 0) {
			gameObjects.erase(gameObjects.begin() + i);
		}
	}

	
}


void GameObjectHandler::restMap()
{
	gameObjects.clear();
	gameObjectInTableOrder.clear();
	

}


void GameObjectHandler::setActiveByTableCol(Map* map,int colStart, int colEnd)
{
	
	for (int col = 0; col < map->getaLevelMap().size(); col++) {
		
		for (int row = 0; row < map->getaLevelMap()[col].size(); row++) {

			if (map->getaLevelMap()[col][row].compare(" ") == 0 || gameObjectInTableOrder[col][row] == NULL) {
				
			}
			else {
				
				if (col > colStart && col < colEnd) {
					GameObject* tempGameObject = gameObjectInTableOrder[col][row];
					
					tempGameObject->setActive(true);
					
					if (tempGameObject->getType().compare("EnemyHelicopter") == 0|| tempGameObject->getType().compare("Boss") == 0|| tempGameObject->getType().compare("Turret") == 0) {
						Enemy* tempEnemy = ((Enemy*)tempGameObject);
						tempEnemy->setCurrentWeaponActiveTo(true);
						tempEnemy->setHealth(tempEnemy->getInitHP());
					}

				}
				else {
					GameObject* tempGameObject = gameObjectInTableOrder[col][row];
					
					tempGameObject->setActive(false);
					if (tempGameObject->getType().compare("EnemyHelicopter") == 0 || tempGameObject->getType().compare("Boss") == 0 || tempGameObject->getType().compare("Turret") == 0) {
						Enemy* tempEnemy = ((Enemy*)tempGameObject);
						tempEnemy->setCurrentWeaponActiveTo(false);
						tempEnemy->setPosition(glm::vec3(row, -col, 0.0f));
					}
					//activeCount -= 1;
				}
			}
		}
		

		
	}

}

void GameObjectHandler::CleanOutOfRangeGameObject() {

	float max_x = gameObjectInTableOrder[1].size() + 2.0f;
	float max_y = -1.0f *(gameObjectInTableOrder.size()) -2.0f;
	

	for (int count = 0; count < gameObjects.size(); count++) {
		glm::vec3 gameobjectPosition = gameObjects[count]->getPosition();
		if (gameobjectPosition.x < -2 || gameobjectPosition.x > max_x || gameobjectPosition.y < max_y || gameobjectPosition.y > 2) {//max_y is negative number
			if (gameObjects.at(count)->getType().compare("Player") == 0) {
				
			}
			else {
				gameObjects.erase(gameObjects.begin() + count);
			}
			
		}
	}
}

float GameObjectHandler::collisionReslove(GameObject* objectA, GameObject* objectB) {

	glm::vec3 relativeV = objectB->getVelocity() - objectA->getVelocity();
	glm::vec3 normal = objectB->getPosition() - objectA->getPosition();
	float velN = glm::dot(relativeV, normal);


	if (velN > 0.0f) {
		return 0;
	}

	float e = glm::min(objectA->getRestitution(), objectB->getRestitution());
	//float e = objectA->getRestitution()+ objectB->getRestitution();
	float j = -(1 + e) * velN;

	float objectA_reverseMass = objectA->getReverseMass();
	float objectB_reverseMass = objectB->getReverseMass();

	float sumOfReverseMass = objectA_reverseMass + objectB_reverseMass;
	if (sumOfReverseMass != 0) {
		j /= sumOfReverseMass;
	}

	glm::vec3 impluse = j * normal;
	objectA->setVelocity(objectA->getVelocity() - impluse * objectA_reverseMass);
	objectB->setVelocity(objectB->getVelocity() + impluse * objectB_reverseMass);

	return j;
}



