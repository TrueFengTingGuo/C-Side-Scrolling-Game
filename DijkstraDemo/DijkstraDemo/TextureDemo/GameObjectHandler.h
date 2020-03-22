#pragma once

#include <vector>
#include <string>

class Map;
class PlayerGameObject;
class GameObject;
class Shader;
class mapBlock;
class Store;

class GameObjectHandler {
public:
	GameObjectHandler();

	void update(double deltaTime);

	void render(Shader& shader);
	
	void add(GameObject* go);
	void setActiveByType(std::string type, bool setBoolVar);
	void deleteByType(std::string type);
	void restMap();
	void setActiveByTableCol(Map* map,int colStart, int colEnd);
	
	// Getters
	inline PlayerGameObject* getPlayer() { return player; }

	//this store all gameobbject in the map table
	std::vector<std::vector<GameObject*>> gameObjectInTableOrder;

	bool loadMapAgain = false;
	int mapLevel = 1;

private:
	PlayerGameObject* player;
	Store* store;

	std::vector<GameObject*> gameObjects;
	void CleanOutOfRangeGameObject();
	
};
