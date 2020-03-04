#include "Bullet.h"

Bullet::Bullet(GameObjectHandler* h, glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::string newType, float d, std::string bt)
	: GameObject(h, entityPos, entityTexture, entityNumElements, newType)
{
	damage = d;
	bulletType = bt;
}
