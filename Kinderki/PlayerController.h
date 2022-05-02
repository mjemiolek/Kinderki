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
    std::shared_ptr<SceneGraphNode> playerObject;
public:
    PlayerController(std::shared_ptr<SceneGraphNode> player) {
        this->playerObject = player;
    }
    ~PlayerController() {}
    void move(GLFWwindow* window, float deltaTime)
    {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            playerObject->get_transform().m_position.z -= 2.5f * deltaTime;
            lightPos.z -= 2.5f * deltaTime;
            //Obrot wprzod
            if (playerObject->get_transform().y_rotation_angle <= 0.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 0.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            playerObject->get_transform().m_position.z += 2.5f * deltaTime;
            lightPos.z += 2.5f * deltaTime;
            if (playerObject->get_transform().y_rotation_angle <= 180.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 180.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            playerObject->get_transform().m_position.x -= 2.5f * deltaTime;
            lightPos.x -= 2.5f * deltaTime;
            if (playerObject->get_transform().y_rotation_angle <= 270.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 270.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            playerObject->get_transform().m_position.x += 2.5f * deltaTime;
            lightPos.x += 2.5f * deltaTime;
            if (playerObject->get_transform().y_rotation_angle <= 90.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 90.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        }
        //setPlayerPosition(playerObject->get_transform().m_position);
        playerObject->update_transform();
        playerObject->collider.setPosition(playerObject->get_transform().m_position);
	}
    void setPlayerObject(std::shared_ptr<SceneGraphNode> tempObject) {
        playerObject = tempObject;
    }
    std::shared_ptr<SceneGraphNode> getPlayerObject() {
        return playerObject;
    }
};

#endif
