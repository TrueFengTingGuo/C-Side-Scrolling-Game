#include "GameObjectHandler.h"
#include "PlayerGameObject.h"
#include "Enemy.h"
#include "Map.h"


GameObjectHandler::GameObjectHandler(PlayerGameObject* p) {
	player = p;
	gameObjects.push_back(p);
}

// Updates all game objects
void GameObjectHandler::update(double deltaTime) {

	std::vector<int> inactiveObjectsIndex;

	for (int i = 0; i < gameObjects.size(); i++) {

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
				if (distance < 1.0f) {
					if (currentGameObject->getType().compare("Bullet") == 0) {

						if (otherGameObject->getType().compare("Enemy") == 0) {
							((Enemy*)otherGameObject)->hurt(((Bullet*)currentGameObject)->getDamage());
						}
					}
					if (currentGameObject->getType().compare("Player") == 0) {
						if (otherGameObject->getType().compare("mapBlock") == 0) {

							//set to reversed velcoity
							((PlayerGameObject*)currentGameObject)->reverseVelocity(deltaTime);

						}
					}

				}

			}
		}
		
	}

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

void GameObjectHandler::add(GameObject* go) {
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
	deleteByType("mapBlock");
	deleteByType("Enemy");
	gameObjectInTableOrder.clear();

}


void GameObjectHandler::setActiveByTableCol(Map* map,int colStart, int colEnd)
{
	std::cout << map->getaLevelMap().size();
	int activeCount = 0;
	for (int col = 0; col < map->getaLevelMap().size(); col++) {
		
		for (int row = 0; row < map->getaLevelMap()[col].size(); row++) {

			if (map->getaLevelMap()[col][row].compare(" ") == 0 || gameObjectInTableOrder[col][row] == NULL) {
				
			}
			else {
				
				if (col > colStart && col < colEnd) {
					gameObjectInTableOrder[col][row]->setActive(true);
					activeCount += 1;
				}
				else {
					gameObjectInTableOrder[col][row]->setActive(false);
					//activeCount -= 1;
				}
			}
		}
		
		//std::cout << activeCount <<" , " << map->getParitalLoadedMap_colRange().y<<  std::endl;
		
	}
}






