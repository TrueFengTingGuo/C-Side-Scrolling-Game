#include "Store.h"

Store::Store(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements,std::string newType,PlayerGameObject* playerReference)
	: GameObject(entityPos, entityTexture, entityNumElements, newType) {
}

