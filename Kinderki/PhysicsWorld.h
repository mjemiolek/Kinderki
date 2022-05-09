#pragma once
#include "SceneGraph.h"
#include <stdlib.h>
#include <iostream>

class PhysicsWorld {
public:
	std::vector<std::shared_ptr<SceneGraphNode>> physicsObjects;
	PhysicsWorld() {}
	PhysicsWorld(std::vector<std::shared_ptr<SceneGraphNode>> colObj)
	{
		physicsObjects = colObj;
	}

	void step(float deltaTime){
		for (const auto& object : physicsObjects)
		{
			object->applyGravity(deltaTime);
		}
		manageCollisions(deltaTime);
		for (const auto& object : physicsObjects)
		{
			object->moveObject(deltaTime);
		}
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

						glm::vec3 play = player->collider.getPosition();
						glm::vec3 p = object->collider.getPosition();
						float x = play.x - p.x, y = play.y - p.y, z = play.z - p.z;
						//For box to box//			   It's not trigger           //         If it is box         //   player have box collider
						if (object->collider.getIsTrigger() == false && object->collider.getRadius() <= 0 && player->collider.getRadius() <= 0 &&
							player->collider.boxToBoxCollisioncheck(object->collider))
						{
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
			}
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