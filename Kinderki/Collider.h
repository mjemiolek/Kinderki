#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Collider {
private:
	glm::vec3 position;
	float radius;
public:
	bool checkforCollision();
};