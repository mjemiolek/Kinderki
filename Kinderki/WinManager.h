#pragma once
#include "SceneGraph.h"
#include <stdlib.h>
#include <iostream>

class WinManager {
private:
	std::vector<Collider> triggers;
	std::shared_ptr<SceneGraphNode> player;
public:
	WinManager(std::vector<Collider> trig, std::shared_ptr<SceneGraphNode> play)
	{
		triggers = trig;
		player = play;
	}

	bool checkForWin()
	{
		for (const auto& trigger : triggers)
		{
			if (player->collider.boxToBoxCollisioncheck(trigger))
			{
				return true;
			}
		}
		return false;
	}

	void winInstructions()
	{
		if (checkForWin()) std::cout << "Win";
	}
};