#pragma once

#include "GameObject.h"
#include "PlayerGameObject.h"
#include <vector>
#include "Weapon.h"
#include "Window.h"
#include <iostream>	//used for debug purposes
#include <GL/glew.h> // window management library
#include <GL/glfw3.h>

extern int window_width_g;
extern int window_height_g;
extern float cameraZoom;
extern float aspectRatio;

class Store :
	public GameObject
{
public:
	Store(GLuint newStoredTex[],GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string newType);
	
	
	//
	void render(Shader& shader) override;
	void update(double deltaTime) override;
private:
	std::vector<Weapon> weaponCollection;
	void levelup();
	void buyAmmo();
	void buyWeapon(double x, double y);

	GLuint *storedTex;
	glm::vec3 weaponIconStartFrom;
	float currentIconMovment = 1; //showing the movment of the icon
	int mouseOnTheIcon_number; // record which icon is about to clicked
};

