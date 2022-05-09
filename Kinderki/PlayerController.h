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
    int candyCount;
public:
    PlayerController(std::shared_ptr<SceneGraphNode> player) {
        this->playerObject = player;
        candyCount = 6;
        std::cout << "candy count: " << candyCount << std::endl;
    }
    ~PlayerController() {}
    void move(GLFWwindow* window, float deltaTime)
    {
        float speed = 2.5f;
        playerObject->velocity.z = 0.0f;
        playerObject->velocity.x = 0.0f;
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            playerObject->velocity.z = -(speed);
            lightPos.z -= 2.5f * deltaTime;
            //Obrot wprzod
            if (playerObject->get_transform().y_rotation_angle <= 0.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 0.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            playerObject->velocity.z = speed;
            lightPos.z += 2.5f * deltaTime;
            if (playerObject->get_transform().y_rotation_angle <= 180.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 180.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            playerObject->velocity.x = -(speed);
            lightPos.x -= 2.5f * deltaTime;
            if (playerObject->get_transform().y_rotation_angle <= 270.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 270.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            playerObject->velocity.x = speed;
            lightPos.x += 2.5f * deltaTime;
            if (playerObject->get_transform().y_rotation_angle <= 90.0f)
                playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
            else if (playerObject->get_transform().y_rotation_angle >= 90.0f)
                playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;
        }
        //debuowanie postaci
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            playerObject->get_transform().m_position.x += 2.5f * deltaTime;
            lightPos.x += 2.5f * deltaTime;
                playerObject->get_transform().x_rotation_angle += 90.0f * deltaTime;
        }
        //setPlayerPosition(playerObject->get_transform().m_position);
        playerObject->update_transform();
        playerObject->collider.setPosition(playerObject->get_transform().m_position);

        //move Player to position (0,2,0)
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            playerObject->get_transform().m_position = glm::vec3(0.0f, 2.0f, 0.0f);
        }
	}
   
    bool triggerCollision(std::shared_ptr<SceneGraphNode> obstacle) {
        //Posistion
        glm::vec3 pla = playerObject->get_transform().m_position;
        glm::vec3 obst = obstacle->trigger.getPosition();
        //distance
        float distance = sqrt((obst.x - pla.x) * (obst.x - pla.x) + (obst.y - pla.y) * (obst.y - pla.y) + (obst.z - pla.z) * (obst.z - pla.z));
        //std::cout << "x: " << playerObject->get_transform().m_position.x << "y: " << playerObject->get_transform().m_position.y << "z: " << playerObject->get_transform().m_position.z << std::endl;
        if (distance < obstacle->trigger.getRadius()) {
            
            return true;

        }
        return false;
    }

    void interact(GLFWwindow* window, std::shared_ptr<SceneGraphNode> interacter,float dt) {
        if (triggerCollision(interacter)) {
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                playerObject->get_transform().m_position.y -= 0.3f * dt;
                if (playerObject->get_transform().m_position.y <= 1.5f) {
                    playerObject->get_transform().m_position.y += 0.3f * dt;
                    playerObject->get_transform().m_position.x = -5.0f;
                }
            }
        }
    }

    void setPlayerObject(std::shared_ptr<SceneGraphNode> tempObject) {
        playerObject = tempObject;
    }

    void setCandyCount(int thisCandyCount) {
        candyCount = thisCandyCount;
    }

    int getCandyCount() {
        return candyCount;
    }
    std::shared_ptr<SceneGraphNode> getPlayerObject() {
        return playerObject;
    }
};

#endif
