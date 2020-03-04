#include<iostream>
#include<fstream>
#include<string>
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>

using namespace std;

class Map
{

public:
	Map();
	bool loadPartialMap(glm::vec3 playerPosition);
	vector<vector<string>> getPartialMap() { return twoDTemp; }
	//getter

private:
	vector<vector<string>> aLevelMap;
	int map_height; // table 
	int map_width;// table 

	//for partial map
	vector<vector<string>> twoDTemp;


	glm::vec2 paritalLoadedMap_topLeft = glm::vec2(-1.0f,-1.0f); //init value
	glm::vec2 paritalLoadedMap_botRight = glm::vec2(-1.0f, -1.0f);//init value
};
