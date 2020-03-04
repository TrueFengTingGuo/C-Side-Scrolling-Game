#include "GameObjectHandler.h"
#include "PlayerGameObject.h"



GameObjectHandler::GameObjectHandler(PlayerGameObject* p) {
	player = p;

}

// Updates all game objects
void GameObjectHandler::update(double deltaTime) {

	// update player
	player->update(deltaTime);

	std::vector<int> inactiveObjectsIndex;

	for (int i = 0; i < gameObjects.size(); i++) {
		// Get the current object
		GameObject* currentGameObject = gameObjects[i];

		if (!currentGameObject->getActive()) {
			inactiveObjectsIndex.push_back(i);
			continue;
		}

		// Updates game objects
		currentGameObject->update(deltaTime);

		//gameobjects Collision
		for (int j = 0; j < gameObjects.size(); j++) {
			GameObject* otherGameObjects = gameObjects[j];
			float distance = glm::length(currentGameObject->getPosition() - otherGameObjects->getPosition());
			if (distance < 1.0f) {

			}

		}
	}

	// remove inactive objects
	for (int i = 0; i < inactiveObjectsIndex.size(); i++) {
		gameObjects.erase(gameObjects.begin() + inactiveObjectsIndex[i]);
	}
}

// Renders all game objects
void GameObjectHandler::render(Shader& shader) {
	player->render(shader);

	for (int i = 0; i < gameObjects.size(); i++) {
		// Get the current object
		GameObject* currentGameObject = gameObjects[i];

		//reset color uniform.
		GLint color_loc = glGetUniformLocation(shader.getShaderID(), "colorMod");
		glUniform3f(color_loc, 0.0f, 0.0f, 0.0f);

		// Render game objects
		currentGameObject->render(shader);
	}
}

void GameObjectHandler::add(GameObject* go) {
	gameObjects.push_back(go);
}
