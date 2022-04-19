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

#include "SceneGraph.h"

class PlayerController {
private:
	glm::vec3 PlayerPosition;
public:
    PlayerController() {}
    ~PlayerController() {}
    glm::vec3 getPlayerPosition()
    {
        return PlayerPosition;
    }
    void setPlayerPosition(glm::vec3 position)
    {
        PlayerPosition = position;
    }
	void move(GLFWwindow* window, std::shared_ptr<SceneGraphNode> player, float deltaTime) 
    {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            player->get_transform().m_position.z -= 2.5f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            player->get_transform().m_position.z += 2.5f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            player->get_transform().m_position.x -= 2.5f * deltaTime;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            player->get_transform().m_position.x += 2.5f * deltaTime;
        setPlayerPosition(player->get_transform().m_position);
        player->collider.setPosition(player->get_transform().m_position);
	}
};

#endif
