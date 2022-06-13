#pragma once
#include <memory>
#include "PlayerController.h"
#include "text.h"

float vertices[] = {
	 0.7f, -0.9f,
	-0.7f, -0.5f,
	 0.7f, -0.5f,
	-0.7f, -0.9f
};




uint32_t indicesText[] = { 3, 1, 2,
					  2, 0, 3 };


//float textureCordsText[] = { 0.0f, 1.0f,
//					 1.0f, 0.0f,
//					 0.0f, 0.0f,
//					 1.0f, 1.0f };
float textureCordsText[] = { 1.0f, 1.0f,
					 0.0f, 0.0f,
					 1.0f, 0.0f,
					 0.0f, 1.0f };

class TutorialState {
	bool checkArrowsKeyMove;
	bool checkInteractionWithKid;
	bool checkInteractionWithMovable;
	bool checkInteractionWithSandpit;
	bool findSandpit;
	bool renderText;
	std::shared_ptr<Text> text;
	std::ostringstream tutorialStream;
	std::string tutorialString;
	unsigned int ct;
	unsigned int dt;
	float x;
	unsigned int textVAO;
	unsigned int textVBO;
	unsigned int textEBO;

	unsigned int texture1;
	unsigned int texture2;
	unsigned int texture3;
	unsigned int texture4;
	unsigned int texture5;
	unsigned int textureText;

public:
	TutorialState() {
		checkArrowsKeyMove = true;
		checkInteractionWithKid = false;
		checkInteractionWithMovable = false;
		checkInteractionWithSandpit = false;
		findSandpit = false;
		renderText = true;
		tutorialString = "";
		tutorialStream.str(std::string());
		text = std::make_shared<Text>();
		ct = 0;
		
		////////////////////Tutorial text with texture
		glGenVertexArrays(1, &textVAO);
		glBindVertexArray(textVAO);

		glGenBuffers(1, &textVBO);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glGenBuffers(1, &textVBO);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCordsText), textureCordsText, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glGenBuffers(1, &textEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesText), indicesText, GL_STATIC_DRAW);

	}


	void ManageTutorialThings(GLFWwindow* window, std::shared_ptr<PlayerController> player, std::shared_ptr<SceneGraphNode> interacterAI, std::shared_ptr<SceneGraphNode> sandPiter) {
		if (checkArrowsKeyMove) {
		//	tutorialString = "Press arrows key to move the character";
		//	x = 618.0f;
			textureText = texture1;
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				findSandpit = true;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				findSandpit = true;
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				findSandpit = true;
			}
			if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
				dt = ct;
				checkArrowsKeyMove = false;
				findSandpit = true;
			}
		}
		if (findSandpit && ct - dt > 2) {
		//	x = 852.0f;
			textureText = texture2;
		//	tutorialString = "Find sandpit";
			if (player->getPlayerObject()->collider.boxToBoxCollisioncheck(sandPiter->trigger)) {
				dt = ct;
				findSandpit = false;
				checkInteractionWithKid = true;
			}
		}


		if (checkInteractionWithKid) {
		//	x = 708.0f;
		//	tutorialString = "Press E to interact with kid";
			textureText = texture3;
			if (interacterAI->trigger.sphereToSphereCollisionCheck(player->getPlayerObject()->collider)) {
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
					dt = ct;
					checkInteractionWithKid = false;
					checkInteractionWithMovable = true;
				}
			}
		}
		if (checkInteractionWithMovable) {
		//	x = 681.0f;
		//	tutorialString = "To pick up item just go into it";
			textureText = texture4;
			if (player->getPlayerObject()->m_children.size() == 1) {
				dt = ct;
				checkInteractionWithMovable = false;
				checkInteractionWithSandpit = true;
			}
		}
		if (checkInteractionWithSandpit) {
			//x = 411.0f;
		//	tutorialString = "Press E to interact with sandpit if you have the correct item";
			textureText = texture5;
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
		if (renderText) {
			//text->RenderText(tutorialStream.str(), x, 100.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
			Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
			testShader.use();
			glBindVertexArray(textVAO);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureText);
			glDrawElements(GL_TRIANGLES, GLsizei(std::size(indicesText)), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
			
	}



	void setTexture1(unsigned int dt) {
		texture1 = dt;
	}
	void setTexture2(unsigned int dt) {
		texture2 = dt;
	}
	void setTexture3(unsigned int dt) {
		texture3 = dt;
	}
	void setTexture4(unsigned int dt) {
		texture4 = dt;
	}
	void setTexture5(unsigned int dt) {
		texture5 = dt;
	}

};