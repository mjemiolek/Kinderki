#pragma once
#include "SceneGraph.h"
#include <stdlib.h>
#include <iostream>

class PhysicsWorld {
public:
	std::vector<std::shared_ptr<SceneGraphNode>> physicsObjects;
	float speed = 2.5f; //the same as in PlayerController
	PhysicsWorld() {}
	PhysicsWorld(std::vector<std::shared_ptr<SceneGraphNode>> colObj)
	{
		physicsObjects = colObj;
	}

	void step(float deltaTime){
		for (const auto& object : physicsObjects)
		{
			if (object->collider.getIsDynamic() == true)
			{
				object->applyGravity(deltaTime);
				object->moveObject(deltaTime);
			}
		}
		manageCollisions(deltaTime);
	}

	void manageCollisions(float deltaTime)
	{
		for (const auto& object : physicsObjects)
		{
			for (const auto& player : physicsObjects)
			{
				if (player->collider.getIsDynamic() == true) //Optimalization (check only for dynamic objects)
				{
					if (!(object == player))
					{
						Collider tempCollider = object->collider;
						resolveCollisions(player, object, deltaTime);
						for (int t = 0; t < object->additionalColliders.size(); t++)
						{
							object->collider = object->additionalColliders[t];
							resolveCollisions(player, object, deltaTime);
						}
						object->collider = tempCollider;

					}
					//Don't go into ground
					//if (player->get_transform().m_position.y < 1.8f) player->get_transform().m_position.y = 1.8f;
					//std::cout<< player->get_transform().m_position.y << std::endl;
				}
			}
		}
	}
	void resolveCollisions(std::shared_ptr<SceneGraphNode> player, std::shared_ptr<SceneGraphNode> object,float deltaTime)
	{
		glm::vec3 play = player->collider.getPosition();
		glm::vec3 p = object->collider.getPosition();
		glm::vec3 colR = object->collider.getCollisionRange();
		float x = play.x - p.x, y = play.y - p.y, z = play.z - p.z; //distance from player in all 3 directions
		//There is so problem for not perfect cube boxes
		//For box to box//			   It's not trigger           //         If it is box         //   player have box collider
		if (object->collider.getIsTrigger() == false && object->collider.getRadius() <= 0 && player->collider.getRadius() <= 0 &&
			player->collider.boxToBoxCollisioncheck(object->collider))
		{
			//abs(x) >= abs(y) && abs(x) >= abs(z)
			if (abs(x) - object->collider.getCollisionRange().x >= abs(z) - object->collider.getCollisionRange().z &&
				abs(x) - object->collider.getCollisionRange().x >= abs(y) - object->collider.getCollisionRange().y) // x-axis collision
			{
				//Push object away from collision
				//player->get_transform().m_position.x -= player->velocity.x * deltaTime;
				if (x > 0)
				{
					player->get_transform().m_position.x += speed * deltaTime;
				}
				else
				{
					player->get_transform().m_position.x -= speed * deltaTime;
				}
				//std::cout << "abs(x):"<<abs(x) <<"abs(z)"<<abs(z)<<std::endl;
				//Reset object velocity in collision direction
				player->velocity.x = 0.0f;
			}
			if (abs(y) - object->collider.getCollisionRange().y >= abs(z) - object->collider.getCollisionRange().z &&
				abs(y) - object->collider.getCollisionRange().y >= abs(x) - object->collider.getCollisionRange().x) //y-axis collision
			{
				player->canJump = true;
				//Push object away from collision
				//player->get_transform().m_position.y -= player->velocity.y * deltaTime;

				if (y > 0)
				{
					player->get_transform().m_position.y -= player->velocity.y * deltaTime;
				}
				else
				{
					player->get_transform().m_position.y += player->velocity.y * deltaTime;
				}

				//Reset object velocity in collision direction
				player->velocity.y = 0.0f;
			}
			if (abs(z) - object->collider.getCollisionRange().z >= abs(x) - object->collider.getCollisionRange().x &&
				abs(z) - object->collider.getCollisionRange().z >= abs(y) - object->collider.getCollisionRange().y) //z-axis collision
			{
				//Push object away from collision
				//player->get_transform().m_position.z -= player->velocity.z * deltaTime;
				if (z > 0)
				{
					player->get_transform().m_position.z += speed * deltaTime;
				}
				else
				{
					player->get_transform().m_position.z -= speed * deltaTime;
				}
				//Reset object velocity in collision direction
				player->velocity.z = 0.0f;
			}
		}
		//For Sphere to sphere and box to sphere
					//				 It's not trigger		    	//         If it is sphere    //
		if (object->collider.getIsTrigger() == false && object->collider.getRadius() > 0)
		{      //Player have box collider
			if (player->collider.getRadius() <= 0)
			{
				//Create temporary sphere collider for player beacuse I'm lazy
				Collider* tempCollider = new Collider(0.4f, false, player->collider.getPosition(), true);
				//Push player away
				if (tempCollider->sphereToSphereCollisionCheck(object->collider))
				{
					pushFromSphere(player, object->collider, tempCollider->getRadius());
				}
				//delete tempCollider
				delete tempCollider;
			}
			else {
				//Push player away
				if (player->collider.sphereToSphereCollisionCheck(object->collider))
				{
					pushFromSphere(player, object->collider, player->collider.getRadius());
				}
			}
		}
		//For sphere to box//		 It's not trigger       //        It's box                 //  player have sphere collider
		if (object->collider.getIsTrigger() == false && object->collider.getRadius() <= 0 && player->collider.getRadius() > 0)
		{
			//Create temporary box collider for player beacuse I'm lazy
			Collider* tempCollider = new Collider(glm::vec3(0.38f, 0.38f, 0.38f), false, player->collider.getPosition(), true);
			//Copy-paste from above
			if (tempCollider->boxToBoxCollisioncheck(object->collider))
			{
				//abs(x) >= abs(y) && abs(x) >= abs(z)
				if (abs(x) - object->collider.getCollisionRange().x >= abs(z) - object->collider.getCollisionRange().z &&
					abs(x) - object->collider.getCollisionRange().x >= abs(y) - object->collider.getCollisionRange().y) // x-axis collision
				{
					//Push object away from collision
					//player->get_transform().m_position.x -= player->velocity.x * deltaTime;
					if (x > 0)
					{
						player->get_transform().m_position.x += speed * deltaTime;
					}
					else
					{
						player->get_transform().m_position.x -= speed * deltaTime;
					}
					//std::cout << "abs(x):"<<abs(x) <<"abs(z)"<<abs(z)<<std::endl;
					//Reset object velocity in collision direction
					player->velocity.x = 0.0f;
				}
				if (abs(y) - object->collider.getCollisionRange().y >= abs(z) - object->collider.getCollisionRange().z &&
					abs(y) - object->collider.getCollisionRange().y >= abs(x) - object->collider.getCollisionRange().x) //y-axis collision
				{
					player->canJump = true;
					//Push object away from collision
					//player->get_transform().m_position.y -= player->velocity.y * deltaTime;

					if (y > 0)
					{
						player->get_transform().m_position.y -= player->velocity.y * deltaTime;
					}
					else
					{
						player->get_transform().m_position.y += player->velocity.y * deltaTime;
					}

					//Reset object velocity in collision direction
					player->velocity.y = 0.0f;
				}
				if (abs(z) - object->collider.getCollisionRange().z >= abs(x) - object->collider.getCollisionRange().x &&
					abs(z) - object->collider.getCollisionRange().z >= abs(y) - object->collider.getCollisionRange().y) //z-axis collision
				{
					//Push object away from collision
					//player->get_transform().m_position.z -= player->velocity.z * deltaTime;
					if (z > 0)
					{
						player->get_transform().m_position.z += speed * deltaTime;
					}
					else
					{
						player->get_transform().m_position.z -= speed * deltaTime;
					}
					//Reset object velocity in collision direction
					player->velocity.z = 0.0f;
				}
			}
			delete tempCollider;
		}
	}

	void pushFromSphere(std::shared_ptr<SceneGraphNode> player, Collider sphere, float playerRadius)
	{
		//Positions
		glm::vec3 play = player->collider.getPosition();
		glm::vec3 p = sphere.getPosition();
		//distance between sphere centers
		float distance = sqrt((p.x - play.x) * (p.x - play.x) + (p.y - play.y) * (p.y - play.y) + (p.z - play.z) * (p.z - play.z));
		//Distance to push sphere from other sphere
		float overlap = distance - playerRadius - sphere.getRadius();
		//Displace player
		play.x -= overlap * (play.x - p.x) / distance;
		play.y -= overlap * (play.y - p.y) / distance;
		play.z -= overlap * (play.z - p.z) / distance;
		//Attach new position to player
		player->get_transform().m_position = play;
	}
};