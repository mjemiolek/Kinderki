#pragma once
#include <memory>
#include "PlayerController.h"
#include "text.h"



class TutorialState {
	bool checkArrowsKeyMove;
	bool checkInteractionWithKid;
	bool checkInteractionWithMovable;
	bool checkInteractionWithSandpit;
	bool renderText;
	std::shared_ptr<Text> text;
	std::ostringstream tutorialStream;
	std::string tutorialString;
	unsigned int ct;
	unsigned int dt;
public:
	TutorialState() {
		checkArrowsKeyMove = true;
		checkInteractionWithKid = false;
		checkInteractionWithMovable = false;
		checkInteractionWithSandpit = false;
		renderText = true;
		tutorialString = "";
		tutorialStream.str(std::string());
		text = std::make_shared<Text>();
		ct = 0;
	}


	void ManageTutorialThings(GLFWwindow* window, std::shared_ptr<PlayerController> player, std::shared_ptr<SceneGraphNode> interacterAI, std::shared_ptr<SceneGraphNode> sandPiter) {
		if (checkArrowsKeyMove) {
			tutorialString = "Press arrows key to move the character";
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				checkInteractionWithKid = true;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				checkInteractionWithKid = true;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				checkInteractionWithKid = true;
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				checkInteractionWithKid = true;
			}
		}
		if (checkInteractionWithKid && ct - dt > 2) {
			tutorialString = "Press E to interact with kid";
			if (interacterAI->trigger.sphereToSphereCollisionCheck(player->getPlayerObject()->collider)) {
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
					dt = ct;
					checkInteractionWithKid = false;
					checkInteractionWithMovable = true;
				}
			}
		}
		if (checkInteractionWithMovable && ct - dt > 1) {
			tutorialString = "To pick up item just go into it";
			if (player->getPlayerObject()->m_children.size() == 1) {
				dt = ct;
				checkInteractionWithMovable = false;
				checkInteractionWithSandpit = true;
			}
		}
		if (checkInteractionWithSandpit && ct - dt > 1) {
			tutorialString = "Press E to interact with sandpit if you have the correct item";
			if (player->getPlayerObject()->m_children.size() == 0) {
				return;
			}
			if (player->getPlayerObject()->collider.boxToBoxCollisioncheck(sandPiter->trigger) && player->getPlayerObject()->m_children.at(0)->getMovableType() == TOSANDPIT) {
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
					dt = ct;
					checkInteractionWithSandpit = false;
					renderText = false;
				}
			}
		}

	}
	void update(GLFWwindow* window, std::shared_ptr<PlayerController> player, std::shared_ptr<SceneGraphNode> interacterAI, std::shared_ptr<SceneGraphNode> sandPiter) {
		ct = glfwGetTime();
		ManageTutorialThings(window, player, interacterAI, sandPiter);
		tutorialStream.str(std::string());
		tutorialStream << tutorialString;
	}
	void render() {
		if(renderText)
			text->RenderText(tutorialStream.str(), 400.0f, 100.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	}
};