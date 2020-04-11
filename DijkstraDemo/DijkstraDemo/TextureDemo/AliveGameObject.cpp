#include "AliveGameObject.h"
#include "GameObject.h"
using namespace std;


AliveGameObject::AliveGameObject(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string myType,float newMass,float newHealth,float newDamage, int newLevel)
	: GameObject(h, entityPos, entityTexture, entityNumElements, myType,newMass) {
	level = newLevel;
	hp = newHealth + newLevel * growingHealth;
	initHP = hp;
	currentWeapon = 0;
}

void AliveGameObject::hurt(float d) {

		hp -= d;
}

//reverse the velocity and update the position
void AliveGameObject::reverseVelocity(double deltaTime)
{
	setVelocity(getVelocity() * (-1.0f));
	GameObject::update(deltaTime);
}

void AliveGameObject::update(double deltaTime)
{
	if (damageTimer > 0) damageTimer--;
	
	for each (Weapon* weapon in weapons)
	{
		if (weapon->getActive()) {
			weapon->update(deltaTime);
		}
		
	}
	GameObject::update(deltaTime);
}

void AliveGameObject::render(Shader& shader)
{
	//render health
	vector<int> intVec;
	int tempHealth = getHealth();
	intVec.clear();

	while (tempHealth > 0) {
		int digit = tempHealth % 10;
		tempHealth = tempHealth / 10;
		intVec.push_back(digit);
	}

	int intVecSize = intVec.size();
	float numberRenderStartFrom = intVecSize * 0.4f / 2.0f-0.2f;

	for (int count = 0; count < intVecSize; count++) {

		shader.enable();
		shader.SetAttributes_sprite();
		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, handler->savedTex[intVec.back() + 6]);

		intVec.pop_back();//take out one digit

		// Setup the transformation matrix for the shader
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), getPosition() + glm::vec3(-numberRenderStartFrom +count * 0.3f, 0.5f, 0.0f));
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), orientation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.4f, 0.4f));


		// Set the transformation matrix in the shader
		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
		shader.setUniformMat4("transformationMatrix", transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}


	for each (Weapon * weapon in weapons)
	{
		if (weapon->getActive()) {
			weapon->render(shader);
		}

	}

	GameObject::render(shader);
}

//fail when the weapon is not new
bool AliveGameObject::addWeapon(Weapon* w) {
	for (int count = 0; count < weapons.size(); count++) {
		if (weapons.at(count)->getName().compare(w->getName()) == 0) {
			
			return false;// add weapon failed
		}
	}
	//if there is no same weapon
	weapons.push_back(w);
	std::cout << "new Weapon added" << std::endl;
	return true; // add weapon successed
	
}

Weapon* AliveGameObject::findAWeapon(string weaponName) {

	for each (Weapon* aWeapon in weapons)
	{
		if (weaponName.compare(aWeapon->getName()) == 0) {
			return aWeapon;
		}
	}

	return NULL;
}

void AliveGameObject::cleanWeapons() {

	weapons.clear();
}