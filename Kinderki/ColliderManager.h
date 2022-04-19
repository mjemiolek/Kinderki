#pragma once
#include "SceneGraph.h"
#include <stdlib.h>
#include <iostream>

//Manage physical Collision between player and objects that are not triggers
class ColliderManager {
public:
	std::vector<std::shared_ptr<SceneGraphNode>> collidingObjects;
	ColliderManager() {}
	ColliderManager(std::vector<std::shared_ptr<SceneGraphNode>> colObj) 
	{
		collidingObjects = colObj;
	}
	void manageCollisions(std::shared_ptr<SceneGraphNode> player, float deltaTime)
	{
		for (const auto& object : collidingObjects) 
		{
			//For box to box//   It's not trigger           //         If it is box         //   player have box collider
			if (object->collider.getIsTrigger() == false && object->collider.getRadius() <= 0 && player->collider.getRadius() <= 0 &&
				player->collider.boxToBoxCollisioncheck(object->collider))
			{
				glm::vec3 play = player->collider.getPosition();
				glm::vec3 p = object->collider.getPosition();
				float x = play.x - p.x, y = play.y - p.y, z = play.z - p.z;
				if (abs(x) >= abs(y) && abs(x) >= abs(z))
				{
					if (x > 0)
					{
						player->get_transform().m_position.x += 2.5f * deltaTime;
					}
					else
					{
						player->get_transform().m_position.x -= 2.5f * deltaTime;
					}
				}
				else if (abs(y) >= abs(x) && abs(y) >= abs(z))
				{
					if (y > 0)
					{
						player->get_transform().m_position.y += 2.5f * deltaTime;
					}
					else
					{
						player->get_transform().m_position.y -= 2.5f * deltaTime;
					}
				}
				else if (abs(z) >= abs(x) && abs(z) >= abs(y))
				{
					if (z > 0)
					{
						player->get_transform().m_position.z += 2.5f * deltaTime;
					}
					else
					{
						player->get_transform().m_position.z -= 2.5f * deltaTime;
					}
				}
			}
			//For Sphere to sphere and box to sphere
			//				 It's not trigger		    	//         If it is sphere    //
			if (object->collider.getIsTrigger() == false && object->collider.getRadius() > 0)
			{      //Player have box collider
				if (player->collider.getRadius() <= 0)
				{
					//Create temporary sphere collider for player beacuse I'm lazy
					Collider* tempCollider = new Collider(0.4f, false, player->collider.getPosition());
					//Push player away
					if (tempCollider->sphereToSphereCollisionCheck(object->collider))
					{
						pushFromSphere(player, object->collider.getPosition());
					}
					//delete tempCollider
					delete tempCollider;
				}
				else {
					//Push player away
					if (player->collider.sphereToSphereCollisionCheck(object->collider))
					{
						pushFromSphere(player, object->collider.getPosition());
					}
				}
			}
			//For sphere to box// It's not trigger       //        It's box                 //  player have sphere collider
			if (object->collider.getIsTrigger() == false && object->collider.getRadius() <= 0 && player->collider.getRadius() > 0)
			{
				//Create temporary box collider for player beacuse I'm lazy
				Collider* tempCollider = new Collider(glm::vec3(0.38f, 0.38f, 0.38f), false, player->collider.getPosition());
				//Copy-paste from above
				if (tempCollider->boxToBoxCollisioncheck(object->collider))
				{
					glm::vec3 play = player->collider.getPosition();
					glm::vec3 p = object->collider.getPosition();
					float x = play.x - p.x, y = play.y - p.y, z = play.z - p.z;
					if (abs(x) >= abs(y) && abs(x) >= abs(z))
					{
						if (x > 0)
						{
							player->get_transform().m_position.x += 2.5f * deltaTime;
						}
						else
						{
							player->get_transform().m_position.x -= 2.5f * deltaTime;
						}
					}
					else if (abs(y) >= abs(x) && abs(y) >= abs(z))
					{
						if (y > 0)
						{
							player->get_transform().m_position.y += 2.5f * deltaTime;
						}
						else
						{
							player->get_transform().m_position.y -= 2.5f * deltaTime;
						}
					}
					else if (abs(z) >= abs(x) && abs(z) >= abs(y))
					{
						if (z > 0)
						{
							player->get_transform().m_position.z += 2.5f * deltaTime;
						}
						else
						{
							player->get_transform().m_position.z -= 2.5f * deltaTime;
						}
					}
				}
				//delete tempCollider
				delete tempCollider;
			}
		}
	}
	void pushFromSphere(std::shared_ptr<SceneGraphNode> player,glm::vec3 spherePos)
	{
		//Change it for something smarter
		glm::vec3 play = player->collider.getPosition();
		glm::vec3 p = spherePos;
		glm::vec3 direction(play.x - p.x, play.y - p.y, play.z - p.z);
		player->get_transform().m_position += direction * 0.02f;
	}
};