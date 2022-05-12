#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

class Collider {
private:
	glm::vec3 position;
	float radius = -1;
	glm::vec3 collisionRange = glm::vec3(0.0f ,0.0f ,0.0f); //distance from center in all 3 directions
	bool isTrigger;
	bool isDynamic; //Can be static or dynamic
public:
	Collider() {
		radius = 0;
		isTrigger = false;
		position = glm::vec3(0.0f, 0.0f, -3.0f);
		isDynamic = false;
	}
	Collider(float rad, bool isTrig, glm::vec3 pos,bool dynamic) {
		radius = rad;
		isTrigger = isTrig;
		position = pos;
		isDynamic = dynamic;
	}
	Collider(glm::vec3 collRange, bool isTrig, glm::vec3 pos,bool dynamic) {
		collisionRange = collRange;
		isTrigger = isTrig;
		position = pos;
		isDynamic = dynamic;
	}
	bool sphereToSphereCollisionCheck(Collider sphereCollider) {
		glm::vec3 play = position;
		glm::vec3 p = sphereCollider.getPosition();
		float distance = sqrt((p.x - play.x) * (p.x - play.x) + (p.y - play.y) * (p.y - play.y) + (p.z - play.z) * (p.z - play.z));
		if (distance < radius+sphereCollider.getRadius())
		{
			//std::cout << "SphereCollision";
			return true;
		}
		return false;
	}
	bool boxToBoxCollisioncheck(Collider boxCollider) {
		float leftA, leftB;
		float rightA, rightB;
		float topA, topB;
		float bottomA, bottomB;
		float awayA, awayB;
		float closeA, closeB;

		//Calculate the sides of box A
		leftA = position.x - collisionRange.x;
		rightA = position.x + collisionRange.x;
		topA = position.y + collisionRange.y;
		bottomA = position.y - collisionRange.y;
		awayA = position.z - collisionRange.z;
		closeA = position.z + collisionRange.z;

		//Calculate the sides of box B
		leftB = boxCollider.getPosition().x - boxCollider.getCollisionRange().x;
		rightB = boxCollider.getPosition().x + boxCollider.getCollisionRange().x;
		topB = boxCollider.getPosition().y + boxCollider.getCollisionRange().y;
		bottomB = boxCollider.getPosition().y - boxCollider.getCollisionRange().y;
		awayB = boxCollider.getPosition().z - boxCollider.getCollisionRange().z;
		closeB = boxCollider.getPosition().z + boxCollider.getCollisionRange().z;

		//If any of the sides from A are outside of B
		//Y-axis
		if (bottomA >= topB)
		{
			return false;
		}
		if (topA <= bottomB)
		{
			return false;
		}
		//X-axis
		if (rightA <= leftB)
		{
			return false;
		}
		if (leftA >= rightB)
		{
			return false;
		}
		//Z-axis
		if (awayA >= closeB)
		{
			return false;
		}
		if (closeA <= awayB)
		{
			return false;
		}
		//std::cout << "BoxCollision";
		return true;
	}
	bool getIsTrigger() {
		return isTrigger;
	}
	glm::vec3 getPosition() {
		return position;
	}
	void setPosition(glm::vec3 pos) {
		position = pos;
	}
	float getRadius() {
		return radius;
	}
	glm::vec3 getCollisionRange() {
		return collisionRange;
	}
	bool getIsDynamic() {
		return isDynamic;
	}
	bool operator==(const Collider& rhs) const {
		return
			position == rhs.position
			&& collisionRange == rhs.collisionRange
			&& isTrigger == rhs.isTrigger
			&& radius == rhs.radius
			&& isDynamic == rhs.isDynamic
			;
	}
};