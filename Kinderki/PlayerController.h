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
    float speed = 2.5f;
    bool sandMove = false;
public:
    PlayerController(std::shared_ptr<SceneGraphNode> player) {
        this->playerObject = player;
        candyCount = 6;
        std::cout << "candy count: " << candyCount << std::endl;
    }
    ~PlayerController() {}
    void move(GLFWwindow* window, float deltaTime)
    {
        if (!sandMove) {
            playerObject->velocity.z = 0.0f;
            playerObject->velocity.x = 0.0f;
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
                playerObject->velocity.z = -(speed);
                //Obrot wprzod
               /* if (playerObject->get_transform().y_rotation_angle <= 0.0f)
                    playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
                else if (playerObject->get_transform().y_rotation_angle >= 0.0f)
                    playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;*/

            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                playerObject->velocity.z = speed;
                /* if (playerObject->get_transform().y_rotation_angle <= 180.0f)
                     playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
                 else if (playerObject->get_transform().y_rotation_angle >= 180.0f)
                     playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;*/
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                playerObject->velocity.x = -(speed);
                /* if (playerObject->get_transform().y_rotation_angle <= 270.0f)
                     playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
                 else if (playerObject->get_transform().y_rotation_angle >= 270.0f)
                     playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;*/
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                playerObject->velocity.x = speed;
                /* if (playerObject->get_transform().y_rotation_angle <= 90.0f)
                     playerObject->get_transform().y_rotation_angle += 90.0f * deltaTime;
                 else if (playerObject->get_transform().y_rotation_angle >= 90.0f)
                     playerObject->get_transform().y_rotation_angle -= 90.0f * deltaTime;*/
            }
            rotate(playerObject->velocity, deltaTime);
            //debuowanie postaci
            if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
                playerObject->get_transform().m_position.x += 2.5f * deltaTime;
                playerObject->get_transform().x_rotation_angle += 90.0f * deltaTime;
            }
            //setPlayerPosition(playerObject->get_transform().m_position);
            playerObject->update_transform();
            playerObject->collider.setPosition(playerObject->get_transform().m_position);

            //move Player to position (0,2,0)
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            {
                playerObject->get_transform().m_position = glm::vec3(0.0f, 3.5f, 0.0f);
            }
            //go up
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                //playerObject->get_transform().m_position.y += 0.1f;
                playerObject->velocity.y = speed;
            }
            //jump
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                if (playerObject->canJump==true)
                {
                    playerObject->velocity.y = 5.0f;
                }
                playerObject->canJump = false;
            }
        }
        
	}

    void rotate(glm::vec3 direction,float deltaTime)
    {
        float angle = 0.0f;
        float step = 600.0f;
        float deviation = (step/100.0f)*2.2f;
        //Specify direction
        if (direction.x == 0.0f && direction.z == 0.0f) { angle = playerObject->get_transform().y_rotation_angle; }
        else if (direction.x == speed && direction.z == 0.0f) { angle = 90.0f; }              //right
        else if (direction.z == speed && direction.x == 0.0f) { angle = 180.0f; }        //down
        else if (direction.x == -speed && direction.z == 0.0f) { angle = 270.0f; }       //left
        else if (direction.z == -speed && direction.x == 0.0f) { angle = 0.0f; }         //up
        else if (direction.x == speed && direction.z == speed) { angle = 135.0f; }    //right-down
        else if (direction.z == speed && direction.x == -speed) { angle = 225.0f; }   //down-left
        else if (direction.x == -speed && direction.z == -speed) { angle = 315.0f; }  //left-up
                                                            else { angle = 45.0f; }   //up-right
        //Rotate player towards direction
        if (playerObject->get_transform().y_rotation_angle < angle - deviation || playerObject->get_transform().y_rotation_angle > angle + deviation)
        {
            float angle1= playerObject->get_transform().y_rotation_angle - angle,
                  angle2= angle - playerObject->get_transform().y_rotation_angle;
            if (angle1 < 0.0f) angle1 += 360.0f;
            if (angle2 < 0.0f) angle2 += 360.0f;
            if (angle1 < angle2)
            {
                //Rotate in left direction
                playerObject->get_transform().y_rotation_angle -= step * deltaTime;
                if (playerObject->get_transform().y_rotation_angle < 0.0f)
                {
                    playerObject->get_transform().y_rotation_angle += 360.0f;
                }
            }
            else {
                //Rotate in right direction
                playerObject->get_transform().y_rotation_angle += step * deltaTime;
                if (playerObject->get_transform().y_rotation_angle >= 360.0f)
                {
                    playerObject->get_transform().y_rotation_angle -= 360.0f;
                }
            }
        }
        else {
            playerObject->get_transform().y_rotation_angle = angle;
        }
        //std::cout << playerObject->get_transform().y_rotation_angle<<std::endl;
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
                playerObject->get_transform().m_position.y -= 2.0f * dt;
                if (playerObject->get_transform().m_position.y <= 0.0f) {
                    playerObject->get_transform().m_position.y += 2.0f * dt;
                    sandMove = true;
                    //playerObject->get_transform().m_position.x = -5.0f;
                }
            }
        }
        //std::cout << sandMove << std::endl;

        if (sandMove) {
            if (playerObject->get_transform().m_position.x >= 1.0f) {
                playerObject->get_transform().m_position.x -= 4.5f * dt;
            }
            if (playerObject->get_transform().m_position.x <= 1.0f) {
                playerObject->get_transform().m_position.y += 2.0f * dt;
                if (playerObject->get_transform().m_position.y >= 1.821f) {
                    sandMove = false;
                }
            }
            

        }
    }

    void trampoliner(GLFWwindow* window, std::shared_ptr<SceneGraphNode> interacter, float dt)
    {
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger)) {
            playerObject->velocity.y = 10.0f;
            playerObject->canJump = false;
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
