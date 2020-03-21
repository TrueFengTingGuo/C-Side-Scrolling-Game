#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h> // window management library
#include <GL/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> //
#include <SOIL/SOIL.h> // read image file
#include <chrono>
#include <thread>

#include "Shader.h"
#include "common.h"
#include "Window.h"
#include "PlayerGameObject.h"
#include "GameObjectHandler.h"
#include "Graph.h"
#include "Node.h"
#include "Store.h"
#include "Map.h"
#include "mapBlock.h"
#include "Enemy.h"
#include "EnemyHelicopter.h"
#include "Boss.h"

float mult = 2.75; //play with this if you want a bigger or smaller graph but still framed the same

// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Pathfinding Demo";

extern int window_width_g  = 720;
extern int window_height_g = 980;
extern float cameraZoom    = mult * 0.05f;
extern float aspectRatio   = (float)window_height_g / (float)window_width_g;
//extern GLFWwindow* window;


const glm::vec3 viewport_background_color_g(0.15, 0.17, 0.21);


// Global texture info
GLuint tex[20];

// Global game object info
GameObjectHandler* gameObjectHandler;


// Create the geometry for a square (with two triangles)
// Return the number of array elements that form the square
int CreateSquare(void) {
	// The face of the square is defined by four vertices and two triangles

	// Number of attributes for vertices and faces
//	const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[]  = {
		//  square (two triangles)
		   //  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	// Return number of elements in array buffer (6 in this case)
	return sizeof(face) / sizeof(GLuint);
}


void setthisTexture(GLuint w, char *fname){
	glBindTexture(GL_TEXTURE_2D, w);

	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void setallTexture(void){
	glGenTextures(15, tex);
	setthisTexture(tex[0], "orb.png");
	setthisTexture(tex[1], "helicopter.jpg");
	setthisTexture(tex[2], "bullet.png");
	setthisTexture(tex[3], "Brick_1.png");
	setthisTexture(tex[4], "pistol.png");
	setthisTexture(tex[5], "small_bullet.png");
	setthisTexture(tex[6], "number_png/0-Number-PNG.png");
	setthisTexture(tex[7], "number_png/1-Number-PNG.png");
	setthisTexture(tex[8], "number_png/2-Number-PNG.png");
	setthisTexture(tex[9], "number_png/3-Number-PNG.png");
	setthisTexture(tex[10], "number_png/4-Number-PNG.png");
	setthisTexture(tex[11], "number_png/5-Number-PNG.png");
	setthisTexture(tex[12], "number_png/6-Number-PNG.png");
	setthisTexture(tex[13], "number_png/7-Number-PNG.png");
	setthisTexture(tex[14], "number_png/8-Number-PNG.png");
	setthisTexture(tex[15], "number_png/9-Number-PNG.png");

	glBindTexture(GL_TEXTURE_2D, tex[0]);
}

void loadMap(Map* map) {
	//////////////////////////////must use EnemyBullet (collide with itself)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	//reset
	gameObjectHandler->restMap();

	for (int col = 0; col < map->getaLevelMap().size(); col++) {

		std::vector<GameObject*> tempBlock;
		for (int row = 0; row < map->getaLevelMap()[col].size(); row++) {


			//create map
			if (map->getaLevelMap()[col][row].compare("W") == 0) {
				mapBlock* newBlock = new mapBlock(gameObjectHandler, glm::vec3(row, -col,0.f), tex[3], 6, "mapBlock", row, col);
				gameObjectHandler->add(newBlock);
				tempBlock.push_back(newBlock);

			}
			else if (map->getaLevelMap()[col][row].compare("H") == 0) {
				EnemyHelicopter* newEnemyHelicopter = new EnemyHelicopter(map,gameObjectHandler, glm::vec3(row, -col, 0.0f), tex[1], 6, "Enemy", 1.0, 1, 0, 10.0f);
				Weapon* testWeapon = new Weapon(gameObjectHandler, newEnemyHelicopter->getPosition(), tex[4], 6, "Weapon", "Pistol", tex[6], 100.0f, 999999, 0, "EnemyBullet", newEnemyHelicopter);
				gameObjectHandler->add(newEnemyHelicopter);
				newEnemyHelicopter->addWeapon(testWeapon);
				tempBlock.push_back(newEnemyHelicopter);
			}
			else if (map->getaLevelMap()[col][row].compare("B") == 0) {
				Boss* newBoss = new Boss(map, gameObjectHandler, glm::vec3(row, -col, 0.0f), tex[1], 6, "Enemy", 1.0, 1, 30, 10.0f);
				Weapon* testWeapon = new Weapon(gameObjectHandler, newBoss->getPosition(), tex[4], 6, "Weapon", "Pistol", tex[6], 100.0f, 999999, 0, "EnemyBullet", newBoss);
				gameObjectHandler->add(newBoss);
				newBoss->addWeapon(testWeapon);
				tempBlock.push_back(newBoss);
			}
			else {
				tempBlock.push_back(NULL);
			}

		}
		gameObjectHandler->gameObjectInTableOrder.push_back(tempBlock); // this will store all gameobject in the order of a table
	}

}
// Main function that builds and runs the game
int main(void){
	try {
		// Seed for generating random numbers with rand()
		srand((unsigned int)time(0));

		// Setup window
		Window window(window_width_g, window_height_g, window_title_g);


		// Set up z-buffer for rendering
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Enable Alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create geometry of the square
		int size = CreateSquare();

		// Set up shaders
		Shader shader("shader.vert", "shader.frag");

		// Set up the textures
		setallTexture();

		//Setup widxheight graph
		float mod = 13 / mult;  //allows you to play with the size of the graph by changing mult before running
		int wid = 4 * mod;
		int height = 3 * mod;



		////////////////////////////These will be implemented ////////////////////////////
		Map *gameMap = new Map();	
		gameObjectHandler = new GameObjectHandler();

		//adding player
		glm::vec3 playerDefaultPosition = glm::vec3(0.0f, 0.0f, 0.0f);
		PlayerGameObject* player = new PlayerGameObject(gameObjectHandler, playerDefaultPosition, tex[1], 6, tex, "Player", 1, 1, 1);
		gameObjectHandler->add(player);
		Weapon* testWeapon = new Weapon(gameObjectHandler, playerDefaultPosition, tex[4], 6, "Weapon", "Pistol", tex[5], 60.0f, 100000, 0, "PlayerBullet", player);
		player->addWeapon(testWeapon);

		//adding store (store must init after the player)
		Store* gameStore = new Store(tex, gameObjectHandler, glm::vec3(0.0f, 0.0f, 0.0f), tex[0], 6, "Store");
		gameObjectHandler->add(gameStore);

		//loading map
		loadMap(gameMap);
		

		//set player location
		for (int col = gameMap->getaLevelMap().size() - 1; col > 0; col--) {

			for (int row = 0; row < gameMap->getaLevelMap()[col].size(); row++) {

				//create map
				//cout << gameMap->getPartialMap()[col][row];
				if (gameMap->getaLevelMap()[col][row].compare("S") == 0) {
					//cout << "Start "<< row << " , " << col << endl;
					player->setPosition(glm::vec3(row, - col, 0.0f));
				}

			}
		}



		// Run the main loop
		double lastTime = glfwGetTime();
		while (!glfwWindowShouldClose(window.getWindow())) {

			// Clear background
			window.clear(viewport_background_color_g);

			// Calculate delta time
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// Select proper shader program to use
			shader.enable();

			// Setup camera to focus on (0, 0)
			glm::vec3 cameraPosition = player->getPosition();
			//cout << "Player is at " << cameraPosition.x << "  ,  " << cameraPosition.y << endl;

			glm::mat4 cameraTranslatePos = glm::translate(glm::mat4(1.0f), -cameraPosition);
			glm::mat4 window_scale = glm::scale(glm::mat4(1.0f), glm::vec3(aspectRatio, 1.0f, 1.0f));
			glm::mat4 camera_zoom = glm::scale(glm::mat4(1.0f), glm::vec3(cameraZoom, cameraZoom, cameraZoom));

			glm::mat4 viewMatrix = window_scale * camera_zoom * cameraTranslatePos;
			shader.setUniformMat4("viewMatrix", viewMatrix);
			//user input

			cameraZoom = mult * 0.05f;
			mod = 13 / mult;  //allows you to play with the size of the graph by changing mult before running
			wid = 4 * mod - 1;
			height = 3 * mod - 1;
					
			//only update the gameobjects that are colser to player		
			if (gameMap->loadPartialMap(player->getPosition())) {

				gameObjectHandler->setActiveByTableCol(gameMap,gameMap->getParitalLoadedMap_colRange().x, gameMap->getParitalLoadedMap_colRange().y);

			}
			
			
			// Update and render all GameObjects
			gameObjectHandler->update(deltaTime);
			gameObjectHandler->render(shader);

			// Update other events like input handling
			glfwPollEvents();

			// Push buffer drawn in the background onto the display
			glfwSwapBuffers(window.getWindow());
		}

	}
	catch (std::exception &e){
		// print exception and sleep so error can be read
		PrintException(e);
		std::this_thread::sleep_for(std::chrono::milliseconds(100000));
	}

	return 0;
}
