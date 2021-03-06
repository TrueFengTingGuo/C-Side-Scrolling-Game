#include "PlayerGameObject.h"

#include "Window.h"
using namespace std;

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(GameObjectHandler* h, glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, GLuint allStoredTex[], std::string newType, float newMass,float newHealth, float newDamage, int newLevel)
	: AliveGameObject(h, entityPos, entityTexture, entityNumElements,newType, newMass,newHealth,newDamage,newLevel) {
	storedTex = allStoredTex;
	currentWeapon = 0;
	experience = 0;
	currency = 10;

	objectRadius = 0.5f;

	//determine the window size
	glfwGetWindowSize(Window::getWindow(), &window_width_g, &window_height_g);
	float x_axis_max = ((window_width_g) / (float)(window_width_g / 2.0f)) - 1.0f;
	float y_axis_max = 1.0f - ((window_height_g) / (float)(window_height_g / 2.0f));

	x_axis_max /= (cameraZoom * aspectRatio); //only x is scaled by using the aspect ratio atm.
	y_axis_max /= cameraZoom;	//transforms cursor position based on screen scale. used to be const 0.2
	//std::cout << x_axis_max << " , " << y_axis_max << std::endl;
	
	//set where the (0,0) of the window
	displayIconStartFrom = glm::vec3(-x_axis_max + 0.5, y_axis_max + 0.5, 0.0f); // the staring localtion where all weapons will be displayed


}

//switch weapon
void PlayerGameObject::switchWeapon() {
	weapons[currentWeapon]->setActive(false);
	currentWeapon = (currentWeapon + 1) % weapons.size();
	weapons[currentWeapon]->setActive(true);
}


// Update function for moving the player object around
void PlayerGameObject::update(double deltaTime) {

	/*
	//gravity
	glm::vec3 Accel = glm::vec3(0.0f, -0.98f, 0.0f);
	glm::vec3 newVel = getVelocity() + Accel * (float)deltaTime;
	setVelocity(newVel);
	*/

	// reduce velocity
	if (glm::length(velocity) > 2.0f) {
		velocity[0] *= 0.998;
		velocity[1] *= 0.998;
 
	}
	
	//player controller
	// Checking for player input and changing velocity
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		setVelocity(getVelocity() + glm::vec3(0.0f, 2.0f* currentSpeedBuffVolumn, 0.0f) * (float)deltaTime);
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		setVelocity(getVelocity() + glm::vec3(0.0f, -2.0f * currentSpeedBuffVolumn, 0.0f) * (float)deltaTime);
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		setVelocity(getVelocity() + glm::vec3(2.0f * currentSpeedBuffVolumn, 0.0f, 0.0f) * (float)deltaTime);
		// rotate player to face right
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		setVelocity(getVelocity() + glm::vec3(-2.0f * currentSpeedBuffVolumn, 0.0f, 0.0f) * (float)deltaTime);
		
		// rotate player to face left
	}


	//swetich weapon
	if (cuurentSwitchWeaponCD <= 0.0f) {
		if (glfwGetKey(Window::getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
		
			weapons[currentWeapon]->setFireRateAmp(1.0);
			switchWeapon();
			cuurentSwitchWeaponCD = switchWeaponCD;
			
		}
		
	}
	else {
		cuurentSwitchWeaponCD -= deltaTime;
	}


	if (currentdodgeCD <= 0.0f) {
		if (glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

			velocity *= 7.0f *glm::abs((pow(2.0f, -1.0f* glm::length(velocity))));
			
			currentdodgeCD = dodgeCD;
			

		}

	}
	else {
		
		currentdodgeCD -= deltaTime;
	}

	//power up
	if (speedBuffTime > 0) {
	
		speedBuffTime -= deltaTime;
		weapons[currentWeapon]->setFireRateAmp(0.2);
		if (!isAmped) {
			fireAmpPartical = new Partical(handler, getPosition(), handler->savedTex[0], 6, "Partical_fire", 0.0f, glm::vec4(0.2f, 1.0f, 1.0f, 1.0f), this, 0.1f);
			fireAmpPartical->setDontDestroyOnTime(true);
			handler->addPartical(fireAmpPartical);
		}

		isAmped = true;
		
	}
	else {

		if (fireAmpPartical != NULL) {
			isAmped = false;
			fireAmpPartical->destroy = true;//destory partical
		}
		

		currentSpeedBuffVolumn = 1.0f;
		weapons[currentWeapon]->setFireRateAmp(1.0);
	}

	if (weapons.size() > 0) {
		// Aim weapon
		// get mouse input
		double mouseX, mouseY;
		glfwGetCursorPos(Window::getWindow(), &mouseX, &mouseY);

		mouseX = (mouseX - window_width_g / 2) * cameraZoom;
		mouseY = (mouseY - window_height_g / 2) * cameraZoom;

		// set orientation based on mouse position
		weapons[currentWeapon]->setOrientation(-360.0f / 3.14159265 / 2.0f * atan2(mouseY - position[1], mouseX - position[0]));

		// Fire weapon
		if (glfwGetKey(Window::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS) {
			weapons[currentWeapon]->fire();
			
		}

		
	}

	AliveGameObject::update(deltaTime);
}


void PlayerGameObject::render(Shader& shader)
{
	shader.enable();
	shader.SetAttributes_sprite();

	AliveGameObject::render(shader);

	//render currency
	int tempCurrency = currency;
	vector<int> intVec;

	while (tempCurrency > 0) {
		int digit = tempCurrency % 10;
		tempCurrency = tempCurrency / 10;
		intVec.push_back(digit);
	}

	int intVecSize = intVec.size();
	for (int count = 0; count < intVecSize; count++) {

		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, storedTex[intVec.back() + 6]);

		intVec.pop_back();//take out one digit

		// Setup the transformation matrix for the shader
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), handler->getPlayer()->getPosition() + displayIconStartFrom + glm::vec3(count * 0.5f, 0.0f, 0.0f));
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));


		// Set the transformation matrix in the shader
		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
		shader.setUniformMat4("transformationMatrix", transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);


	}

	//render bullet ammo
	int tempAmmo = weapons.at(currentWeapon)->getAmmo();
	intVec.clear();

	while (tempAmmo > 0) {
		int digit = tempAmmo % 10;
		tempAmmo = tempAmmo / 10;
		intVec.push_back(digit);
	}

	intVecSize = intVec.size();
	for (int count = 0; count < intVecSize; count++) {

		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, storedTex[intVec.back() + 6]);

		intVec.pop_back();//take out one digit

		// Setup the transformation matrix for the shader
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), handler->getPlayer()->getPosition() + displayIconStartFrom + glm::vec3(count * 0.5f, 0.5f, 0.0f));
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));


		// Set the transformation matrix in the shader
		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
		shader.setUniformMat4("transformationMatrix", transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}

	
}


void PlayerGameObject::addExperience(int tempExperience)
{
	experience += tempExperience;
	if (neededExperience < experience) {
		hp = level * getGrowingHealth();
		level += 1;
		neededExperience += level * 5;
	}
}