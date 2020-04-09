#pragma once

#include <vector>
#include <string>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "GameObjectHandler.h"


class Map;
class PlayerGameObject;
class GameObject;
class Shader;
class mapBlock;
class Store;
class Partical;

class GameObjectHandler {
public:
	GameObjectHandler(GLuint newSavedTex[]);

	void update(double deltaTime);

	void render(Shader& shader);
	
	void renderPSS(Shader& shader, double deltaTime);

	void add(GameObject* go);
	void setActiveByType(std::string type, bool setBoolVar);
	void deleteByType(std::string type);
	void restMap();
	void setActiveByTableCol(Map* map,int colStart, int colEnd);
	
	// Getters
	inline PlayerGameObject* getPlayer() { return player; }
	inline std::vector<GameObject*> getGameobjects() {	return  gameObjects;}

	//this store all gameobbject in the map table
	std::vector<std::vector<GameObject*>> gameObjectInTableOrder;

	bool loadMapAgain = false;
	int mapLevel = 1;

	GLuint *savedTex;

private:
	PlayerGameObject* player;
	Store* store;

	std::vector<GameObject*> gameObjects;
	std::vector<Partical*> particals;
	void CleanOutOfRangeGameObject();

	float collisionReslove(GameObject* objectA, GameObject* objectB);
	
};
