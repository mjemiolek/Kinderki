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
			//For box to box//
			if (object->collider.getIsTrigger() == false)
			{
				if (object->collider.getRadius() <= 0) //If it is box
				{
					if (player->collider.boxToBoxCollisioncheck(object->collider))
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
				}
			}
		}
	}
};