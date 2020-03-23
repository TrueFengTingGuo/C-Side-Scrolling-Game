#pragma once

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

	Map(string fileName_number);
	~Map();
	bool loadPartialMap(glm::vec3 playerPosition);

	vector<vector<string>> getPartialMap() { return twoDTemp; }
	vector<vector<string>> getaLevelMap() { return aLevelMap; }

	glm::vec2 getParitalLoadedMap_colRange() { return paritalLoadedMap_colRange; }


	//getter

private:
	vector<vector<string>> aLevelMap;
	int map_height= 0; // table 
	int map_width = 0;// table 

	//for partial map
	vector<vector<string>> twoDTemp;


	glm::vec2 paritalLoadedMap_colRange = glm::vec2(-1.0f, -1.0f); //init value

};

