#pragma once
#include "SceneGraph.h"


class GravityManager {
private:
	float gravity;
public:
	GravityManager(float tempGravity) {
		gravity = tempGravity;
	}
	GravityManager() {

	}
	float getGravity() {
		return gravity;
	}
	void setGravity(float newGravity) {
		gravity = newGravity;
	}
	void updateGravityInPositiveX(std::shared_ptr<SceneGraphNode> object, float dt) {
		object->get_transform().m_position.x += gravity * dt;
		object->collider.setPosition(object->get_transform().m_position);
	}
	void updateGravityInNegativeX(std::shared_ptr<SceneGraphNode> object, float dt) {
		object->get_transform().m_position.x -= gravity * dt;
		object->collider.setPosition(object->get_transform().m_position);
	}
	void updateGravityInPositiveY(std::shared_ptr<SceneGraphNode> object, float dt) {
		object->get_transform().m_position.y += gravity * dt;
		object->collider.setPosition(object->get_transform().m_position);
	}
	void updateGravityInNegativeY(std::shared_ptr<SceneGraphNode> object, float dt) {
		object->get_transform().m_position.y -= gravity * dt;
		object->collider.setPosition(object->get_transform().m_position);
	}
	void updateGravityInPositiveZ(std::shared_ptr<SceneGraphNode> object, float dt) {
		object->get_transform().m_position.z += gravity * dt;
		object->collider.setPosition(object->get_transform().m_position);
	}
	void updateGravityInNegativeZ(std::shared_ptr<SceneGraphNode> object, float dt) {
		object->get_transform().m_position.z -= gravity * dt;
		object->collider.setPosition(object->get_transform().m_position);
	}


};
