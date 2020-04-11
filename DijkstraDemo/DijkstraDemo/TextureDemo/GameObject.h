#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "GameObjectHandler.h"

class GameObject {
public:
	GameObject(GameObjectHandler* h, glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements,std::string newType,float newMass);


	// Updates the GameObject's state. Can be overriden for children
	virtual void update(double deltaTime);

	// Renders the GameObject using a shader
	virtual void render(Shader &shader);

	//detect collision
	virtual bool isCollided(GameObject* comparedObject);

	// Getters
	inline glm::vec3& getPosition() { return position; }
	inline glm::vec3& getVelocity() { return velocity; }
	inline glm::vec3& getRotation() { return rotation; }
	inline float getOrientation() { return orientation; }
	inline float getMass() { return mass; }
	inline float getReverseMass() { return reverseMass; }
	inline std::string& getType() { return type; }
	inline bool& getActive() { return active; }
	inline GLuint& getTexture() { return texture; }
	inline float getRestitution() { return restitution; }
	inline float getObjectRadius() { return objectRadius; }
	// Setters
	inline void setPosition(glm::vec3& newPosition) { position = newPosition; }
	inline void setVelocity(glm::vec3& newVelocity) { velocity = newVelocity; }
	inline void setRotation(glm::vec3& newRotation) { rotation = newRotation; }
	inline void setOrientation(float newOrientation) { orientation = newOrientation; }
	inline void setActive(bool newActive) { active = newActive; }
	inline void setRestitution(float newRestitution) { restitution = newRestitution; }
	inline void setObjectRadius(float newObjectRadius) { objectRadius = newObjectRadius; }

	bool destroy = false;

protected:
	GameObjectHandler* handler;

	// Object's Transform Variables
	// TODO: Add more transformation variables
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 rotation;
	float mass;
	float reverseMass;
	float restitution = 0.5f;
	float objectRadius = 0.0f;
	float orientation;
	std::string  type;

	bool active = true;


	// Object's details
	GLint numElements;
	float objectSize; // Not currently being used (will be needed for collision detection when objects have a different scale)

	// Object's texture
	GLuint texture;
};

#endif