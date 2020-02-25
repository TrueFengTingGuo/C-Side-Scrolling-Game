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
#include "Graph.h"
#include "Node.h"
#include "Store.h"

float mult = 2.75; //play with this if you want a bigger or smaller graph but still framed the same

// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Pathfinding Demo";

extern int window_width_g  = 800;
extern int window_height_g = 600;
extern float cameraZoom    = mult * 0.05f;
extern float aspectRatio   = (float)window_height_g / (float)window_width_g;
//extern GLFWwindow* window;


const glm::vec3 viewport_background_color_g(0.15, 0.17, 0.21);


// Global texture info
GLuint tex[1];

// Global game object info
std::vector<GameObject*> gameObjects;


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
	glGenTextures(1, tex);
	setthisTexture(tex[0], "orb.png");

	glBindTexture(GL_TEXTURE_2D, tex[0]);
}

//set all starting gameobjects which will not be deleted after refreshing the map
void setAllStartingGameObject() {

	PlayerGameObject* player = new PlayerGameObject(glm::vec3(0.0f), tex[0], 6, "Player", 100.0f, 10.0f, 0);
	gameObjects.push_back(player);
	gameObjects.push_back(new Store(glm::vec3(0.0f), tex[0], 6,"Store", player));

}

//this function should reload the map depends on the player gameobject
//do nothing if there is no need to reload
void ReloadingMap() {

	/////////////////////////// implement plz ////////////////////////////////
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
		//Map gameMap;
		

		//inital all gameobjects
		setAllStartingGameObject();



		// Run the main loop
		double lastTime = glfwGetTime();
		while (!glfwWindowShouldClose(window.getWindow())) {
			
			//reloading the gameObjects vector array if it is necessary
			ReloadingMap();

			// Clear background
			window.clear(viewport_background_color_g);

			// Calculate delta time
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			// Select proper shader program to use
			shader.enable();

			// Setup camera to focus on (0, 0)
			glm::mat4 cameraTranslatePos = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f));

			glm::mat4 window_scale = glm::scale(glm::mat4(1.0f), glm::vec3(aspectRatio, 1.0f, 1.0f));
			glm::mat4 camera_zoom = glm::scale(glm::mat4(1.0f), glm::vec3(cameraZoom, cameraZoom, cameraZoom));

			glm::mat4 viewMatrix =  window_scale * camera_zoom * cameraTranslatePos;
			shader.setUniformMat4("viewMatrix", viewMatrix);
			//user input
			
			cameraZoom = mult * 0.05f;
			mod = 13 / mult;  //allows you to play with the size of the graph by changing mult before running
			wid = 4 * mod -1;
			height = 3 * mod -1;


			// Update and render all game objects
			for (int i = 0; i < gameObjects.size(); i++) {
				// Get the current object
				GameObject* currentGameObject = gameObjects[i];

				// Updates game objects
				////////////////////////////implements////////////////////////
				
				if(currentGameObject->getType() == "Player"){
					PlayerGameObject *playerGameObject = dynamic_cast<PlayerGameObject*>(currentGameObject);
			
				}
				
				/*.
				.
				.
				.
				.

				*/

				currentGameObject->update(deltaTime);

				//gameobjects Collision
				for (int j = 0; j < gameObjects.size(); j++) {
					GameObject* otherGameObjects = gameObjects[j];
					float distance = glm::length(currentGameObject->getPosition() - otherGameObjects->getPosition());
					if (distance < 1.0f) {

					}

				}

				//reset color uniform.
				GLint color_loc = glGetUniformLocation(shader.getShaderID(), "colorMod");
				glUniform3f(color_loc, 0.0f, 0.0f, 0.0f);

				// Render game objects
				currentGameObject->render(shader);
			}

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