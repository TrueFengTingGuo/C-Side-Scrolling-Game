#ifndef GAMEOBJECTHANDLER_H
#define GAMEOBJECTHANDLER_H

#include <vector>

class PlayerGameObject;
class GameObject;
class Shader;

class GameObjectHandler {
public:
	GameObjectHandler(PlayerGameObject* p);

	void update(double deltaTime);

	void render(Shader& shader);
	
	void add(GameObject* go);


	// Getters
	inline PlayerGameObject* getPlayer() { return player; }

private:
	PlayerGameObject* player;
	std::vector<GameObject*> gameObjects;
};

#endif