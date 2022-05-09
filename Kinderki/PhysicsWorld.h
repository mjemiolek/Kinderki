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
	}
};