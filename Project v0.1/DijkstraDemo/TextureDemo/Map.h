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
	vector<vector<string>> loadPartialMap();

	//getter

private:
	vector<vector<string>> aLevelMap;
};

