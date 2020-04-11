#include "Store.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! HOW TO ADD A NEW WEAPON IN THE STORE:!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// Add the new weapon in the construtor
	//texture list is stored localy in the store class, just enter the order number of that textrue

Store::Store(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string myType, float newMass)
	: GameObject(h, entityPos, entityTexture, entityNumElements, myType, newMass) {
	glm::vec3 DefaultPosition = glm::vec3(0.0f, 0.0f, 0.0f);


	//set the staring localtion where all weapons will be displayed
	glfwGetWindowSize(Window::getWindow(), &window_width_g, &window_height_g);
	float x_axis_max = ((window_width_g) / (float)(window_width_g / 2.0f)) - 1.0f;
	float y_axis_max = 1.0f - ((window_height_g) / (float)(window_height_g / 2.0f));

	x_axis_max /= (cameraZoom * aspectRatio); //only x is scaled by using the aspect ratio atm.
	y_axis_max /= cameraZoom;	//transforms cursor position based on screen scale. used to be const 0.2
	//std::cout << x_axis_max << " , " << y_axis_max << std::endl;

	weaponIconStartFrom = glm::vec3(x_axis_max - 0.5, -y_axis_max - 0.5, 0.0f); // the staring localtion where all weapons will be displayed


}

//get a weapon base on the cursor location
void Store::buyWeapon(double x, double y)
{	


	glfwGetWindowSize(Window::getWindow(), &window_width_g, &window_height_g);

	//calculating the position of the cursor  in the game world
	if (x < 0 || x > window_width_g || y < 0 || y > window_height_g) {

		return;
	}

	//cursor position before zooming out
	float cursor_x_pos = ((x) / (float)(window_width_g / 2.0f)) - 1.0f;
	float cursor_y_pos = 1.0f - ((y) / (float)(window_height_g / 2.0f));

	cursor_x_pos /= (cameraZoom * aspectRatio); //only x is scaled by using the aspect ratio atm.
	cursor_y_pos /= cameraZoom;	//transforms cursor position based on screen scale. used to be const 0.2
	//std::cout << "mouse coords: (" << cursor_x_pos << "," << cursor_y_pos << ")" << std::endl; //uncomment if interested

	//selecting a weapon base on the mouse location on the screen
	for (int count = 0; count < weaponCollection.size(); count++) {

		glm::vec3 iconStartFrom = weaponIconStartFrom - glm::vec3(0.0f, count * 1.0f, 0.0f);
		
		if (abs(cursor_x_pos - iconStartFrom.x) < 0.4f && abs(cursor_y_pos - iconStartFrom.y) < 0.4f) {
			
			mouseOnTheIcon_number = count; // mouse is on an icon
			if (glfwGetMouseButton(Window::getWindow(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
				Weapon* thisWeapon = handler->getPlayer()->findAWeapon(weaponCollection.at(count)->getName());

				if (thisWeapon == NULL) {
					if (handler->getPlayer()->getCurrency() > weaponCollection.at(count)->getCost()) {
						Weapon* newWeapon = new Weapon(*weaponCollection.at(count)); // used copy constructor
						newWeapon->setActive(false);
						handler->getPlayer()->setCurrency(handler->getPlayer()->getCurrency() - weaponCollection.at(count)->getCost()); // cost money to buy the weapon
						handler->getPlayer()->addWeapon(newWeapon);
					}
				}
				else {
					if (handler->getPlayer()->getCurrency() > int(weaponCollection.at(count)->getCost() * 0.2f)) {
						handler->getPlayer()->setCurrency(handler->getPlayer()->getCurrency() - int(weaponCollection.at(count)->getCost() * 0.2f)); // cost money to ammo
						thisWeapon->setAmmo(thisWeapon->getAmmo() + (int)25.0f * glm::abs((pow(2.0f, -1.0f * thisWeapon->getFireRate())))); // player have the weapon so buy ammo for it
					}
					
				}
			
				
			}
			break;
		}
		else {
			mouseOnTheIcon_number = -1; //mouse is not on any icon
		}
	}


}

void Store::levelup()
{
}

void Store::buyAmmo()
{

}

void Store::addWeapon(Weapon* newWeapon) {
	weaponCollection.push_back(newWeapon);

}
void Store::update(double deltaTime)
{

	double xpos, ypos;
	glfwGetCursorPos(Window::getWindow(), &xpos, &ypos);

	buyWeapon(xpos, ypos);
	
}

void Store::render(Shader& shader) {
	//std::cout << "mouse on " << mouseOnTheIcon_number << std::endl;
	for (int count = 0; count < weaponCollection.size(); count++) {
		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, weaponCollection.at(count)->getTexture());
		shader.enable();
		shader.SetAttributes_sprite();
		// Setup the transformation matrix for the shader
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), handler->getPlayer()->getPosition() + weaponIconStartFrom - glm::vec3(0.0f, count * 1.0f,0.0f));
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 0.5f, 0.5f));

		//animation on the weapon icons
		if (mouseOnTheIcon_number == count) {
			if (currentIconMovment < 0) {
				currentIconMovment = 1.0f;
			}
			else {
				currentIconMovment -= 0.01f;
			}
			//std::cout << "mouse on " << count << std::endl;
			scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f*(currentIconMovment /1), 0.5f * (currentIconMovment / 1), 0.5f));
		}

		// Set the transformation matrix in the shader
		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
		shader.setUniformMat4("transformationMatrix", transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}
	
}


