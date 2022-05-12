#pragma once
#include "SceneGraph.h"

class Object : SceneGraphNode {
private:
	glm::vec3 gravity = glm::vec3(0.0f, -0.981f, 0.0f);
public:
	glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
	float mass = 1.0f;

	void applyGravity(float deltaTime)
	{
			force += mass * gravity; // apply a force

			velocity += force / mass * deltaTime;
			m_transform.m_position += velocity * deltaTime;

			force = glm::vec3(0.0f, 0.0f, 0.0f); // reset net force
	}
};