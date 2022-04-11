#pragma once
#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <irrKlang/ik_ISound.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class PlayerController {
private:
	glm::vec3 PlayerPosition;
public:
	PlayerController(glm::vec3 PlayerPosition);
	~PlayerController();
	glm::vec3 getPlayerPosition();
	void setPlayerPosition(glm::vec3 position);
	void move(GLFWwindow* window, glm::vec3* Cube1Position);
};

#endif
