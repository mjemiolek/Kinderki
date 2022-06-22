#pragma once
#include <memory>
#include "PlayerController.h"
#include "text.h"

int x = 0;
float scale = 0.8f;
float Iscale = 1 / scale;
float vectorText = 0.6f;


float verticesText[] = { 0.7375f * scale, -0.14074f * scale - vectorText,
				-0.7375f * scale, 0.14074f * scale - vectorText,
				 0.7375f * scale, 0.14074f * scale - vectorText,
				-0.7375f * scale, -0.14074f * scale - vectorText };

float tempVerticesText[] = { 0.7375f * scale, -0.14074f * scale - vectorText,
				-0.7375f * scale, 0.14074f * scale - vectorText,
				 0.7375f * scale, 0.14074f * scale - vectorText,
				-0.7375f * scale, -0.14074f * scale - vectorText };

uint32_t indicesText[] = { 3, 1, 2,
					  2, 0, 3 };


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
	bool putOffMovable;
	bool carry;
	bool bigScale;
	std::shared_ptr<Text> text;
	std::ostringstream tutorialStream;
	std::string tutorialString;
	unsigned int ct;
	unsigned int waitTime;
	unsigned int dt;
	unsigned int textVAO;
	unsigned int textVBO1, textVBO2;
	unsigned int textEBO;

	unsigned int texture1;
	unsigned int texture2;
	unsigned int texture3;
	unsigned int texture4;
	unsigned int texture5;
	unsigned int texture6;
	unsigned int texture7;
	unsigned int *textureText;

	unsigned int initTime;
	float ystep;
	float xstep;
	int numberOfSteps;
public:
	TutorialState() {
		checkArrowsKeyMove = true;
		checkInteractionWithKid = false;
		checkInteractionWithMovable = false;
		checkInteractionWithSandpit = false;
		findSandpit = false;
		renderText = true;
		putOffMovable = false;
		bigScale = false;
		carry = true;
		tutorialString = "";
		tutorialStream.str(std::string());
		text = std::make_shared<Text>();
		ct = 0;
		initTime = glfwGetTime();
		numberOfSteps = 30;
		ystep = 0.000125f;
		xstep = 9.3118f * ystep;
		glGenVertexArrays(1, &textVAO);
		glBindVertexArray(textVAO);

		glGenBuffers(1, &textVBO1);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO1);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticesText), &verticesText, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glGenBuffers(1, &textVBO2);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO2);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCordsText), &textureCordsText, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

		glGenBuffers(1, &textEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesText), indicesText, GL_STATIC_DRAW);





	}


	void ManageTutorialThings(GLFWwindow* window, std::shared_ptr<PlayerController> player, std::shared_ptr<SceneGraphNode> interacterAI, std::shared_ptr<SceneGraphNode> sandPiter) {
		if (checkArrowsKeyMove) {
			if (textureText != &texture1) {
				textureText = &texture1;
				bigScale = true;
			}
		//	tutorialString = "Press arrows key to move the character";
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
			if (textureText != &texture3) {
				waitTime = ct;
				textureText = &texture3;
				bigScale = true;
			}
			
		//	tutorialString = "Find sandpit";
			if (player->getPlayerObject()->collider.boxToBoxCollisioncheck(sandPiter->trigger) && ct - waitTime > 0) {
				dt = ct;
				findSandpit = false;
				checkInteractionWithKid = true;
			}
		}


		if (checkInteractionWithKid) {
		//	tutorialString = "Press E to interact with kid";
			if (textureText != &texture4) {
				waitTime = ct;
				textureText = &texture4;
				bigScale = true;
			}
			if (interacterAI->trigger.sphereToSphereCollisionCheck(player->getPlayerObject()->collider) && ct - waitTime > 0) {
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
					dt = ct;
					checkInteractionWithKid = false;
					checkInteractionWithMovable = true;
				}
			}
		}
		if (checkInteractionWithMovable) {
		//	tutorialString = "To pick up item just go into it";
			if (textureText != &texture5) {
				waitTime = ct;
				textureText = &texture5;
				bigScale = true;
			}
			if (player->getPlayerObject()->m_children.size() == 1 && ct - waitTime > 0) {
				dt = ct;
				checkInteractionWithMovable = false;
				putOffMovable = true;
			}
		}



		if (putOffMovable) {
			//need texture
			if (textureText != &texture6) {
				waitTime = ct;
				textureText = &texture6;
				bigScale = true;
			}
			if (player->getPlayerObject()->m_children.size() > 0) {
				carry = true;
			}
			if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
				carry = false;
			}
			std::cout << "carry: " << carry << std::endl;
			if(player->getPlayerObject()->m_children.size() == 0 && !carry && ct - waitTime > 0){
				dt = ct;
				putOffMovable = false;
				checkInteractionWithSandpit = true;
			}		
		}


		if (checkInteractionWithSandpit && ct - dt > 0) {
		//	tutorialString = "Press E to interact with sandpit if you have the correct item";
			if (textureText != &texture7) {
				waitTime = ct;
				textureText = &texture7;
				bigScale = true;
			}
			if (player->getPlayerObject()->m_children.size() == 0) {
				return;
			}
			if (player->getPlayerObject()->collider.boxToBoxCollisioncheck(sandPiter->trigger) && player->getPlayerObject()->m_children.at(0)->getMovableType() == TOSANDPIT && ct - waitTime > 1) {
				if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
					dt = ct;
					checkInteractionWithSandpit = false;
					renderText = false;
					player->setFinishedTutorial(true);
				}
			}
		}

	}
	void update(GLFWwindow* window, std::shared_ptr<PlayerController> player, std::shared_ptr<SceneGraphNode> interacterAI, std::shared_ptr<SceneGraphNode> sandPiter) {
		if (!turnOffTutorial) {
			ct = glfwGetTime();
			if (ct - initTime < 8) {
				renderText = false;
				if (glfwGetKey(window, GLFW_KEY_BACKSLASH) == GLFW_PRESS) {
					turnOffTutorial = true;
				}
			}
			if (ct - initTime >= 8) {
				if (ct - initTime == 8) {
					renderText = true;
				}
				ManageTutorialThings(window, player, interacterAI, sandPiter);
			}
			tutorialStream.str(std::string());
			tutorialStream << tutorialString;
		}
	}
	void render() {
		if (renderText) {
			if (!turnOffTutorial) {
				if (bigScale) {
					ystep = 0.001f;
					xstep = 9.3118f * ystep;
					x = 0;
					*verticesText = *tempVerticesText;
					bigScale = false;

				}
				else {

				}
				if (x < numberOfSteps) {
					if (x < numberOfSteps / 2) {
						verticesText[0] += xstep;
						verticesText[2] -= xstep;
						verticesText[4] += xstep;
						verticesText[6] -= xstep;

						verticesText[1] -= ystep;
						verticesText[3] += ystep;
						verticesText[5] += ystep;
						verticesText[7] -= ystep;
					}
					if (x >= numberOfSteps / 2) {
						verticesText[0] += -xstep;
						verticesText[2] -= -xstep;
						verticesText[4] += -xstep;
						verticesText[6] -= -xstep;

						verticesText[1] -= -ystep;
						verticesText[3] += -ystep;
						verticesText[5] += -ystep;
						verticesText[7] -= -ystep;
					}

					x++;

				}
				else {
					if (ystep = 0.001f) {
						ystep = 0.000125f;
						xstep = 9.3118f * ystep;
						*verticesText = *tempVerticesText;
					}
					x = 0;
				}

				//cout << "x: " << verticesText[0] << endl;



				//text->RenderText(tutorialStream.str(), x, 100.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
				Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
				testShader.use();
				glBindVertexArray(textVAO);
				glBindBuffer(GL_ARRAY_BUFFER, textVBO1);
				glBufferData(GL_ARRAY_BUFFER, sizeof(verticesText), &verticesText, GL_STATIC_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, textVBO2);
				glBufferData(GL_ARRAY_BUFFER, sizeof(textureCordsText), &textureCordsText, GL_STATIC_DRAW);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, *textureText);
				glDrawElements(GL_TRIANGLES, GLsizei(std::size(indicesText)), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
			}
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
	void setTexture6(unsigned int dt) {
		texture6 = dt;
	}
	void setTexture7(unsigned int dt) {
		texture7 = dt;
	}


};