#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <vector>
#include <string>

class Map;
class PlayerGameObject;
class GameObject;
class Shader;
class mapBlock;

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

private:
	PlayerGameObject* player;
	std::vector<GameObject*> gameObjects;
	void CleanOutOfRangeGameObject();
};

#endif