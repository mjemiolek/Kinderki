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
    bool hustawkerMove = false, hustawkerLeft = true;
    float hustawkerSpeed;
    glm::vec3 outlineColor;
   
    bool tyrolkerMove = false;
    bool tyrolkerZero = true;
    bool tyrolkerLaunch = false;
    int tyrolkerLaunchCounter = 0;
    int tyrolkerLaunchEdge = 15;
    int tyrolkerDir = -1;
    int tyrolkerAngle = 49;
    int tyrolkerSpeed = 100;
    int tyrolkerScale = 1;
    float tyrolkerVelocity6 = 6.0f;
public:
    PlayerController(std::shared_ptr<SceneGraphNode> player) {
        this->playerObject = player;
        candyCount = 6;
        outlineColor = glm::vec3(1.0f, 1.0f, 1.0f);
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
            }
            if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                playerObject->velocity.z = speed;
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                playerObject->velocity.x = -(speed);
            }
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                playerObject->velocity.x = speed;
            }
            rotate(playerObject->velocity, deltaTime);
            //debuowanie postaci
            if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
                playerObject->get_transform().m_position.x += 2.5f * deltaTime;
                playerObject->get_transform().x_rotation_angle += 90.0f * deltaTime;
            }

            playerObject->update_transform();
            playerObject->collider.setPosition(playerObject->get_transform().m_position);
            //stepSound.playLooped();

            //move Player to position (0,2,0)
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            {
                playerObject->get_transform().m_position = glm::vec3(14.0f, 2.5f, 6.0f);
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
                if (playerObject->canJump == true)
                {
                    playerObject->velocity.y = 5.0f;
                }
                playerObject->canJump = false;
            }
        }
        //else sandPitCreak.play();
        
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

    void sandPiter(GLFWwindow* window, std::shared_ptr<SceneGraphNode> interacter,float dt) {
        if (playerObject->m_children.size() == 0) {
            setFalseStencil(interacter);
            return;
        }
        
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger) && playerObject->m_children.at(0)->getMovableType() == TOSANDPIT) {
            setTrueStencil(interacter);
            if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
                setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f)); //zielony
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                playerObject->get_transform().m_position.y -= 2.0f * dt;
                if (playerObject->get_transform().m_position.y <= -1.5f) {
                    playerObject->get_transform().m_position.y += 2.0f * dt;
                    sandMove = true;
                    //playerObject->get_transform().m_position.x = -5.0f;
                }
            }
        }
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger) && !playerObject->m_children.at(0)->getMovableType() == TOSANDPIT) {
            setTrueStencil(interacter);
            if (getOutlineColor() != glm::vec3(1.0f, 0.0f, 0.0f)) {
                setOutlineColor(glm::vec3(1.0f, 0.0f, 0.0f)); //czerwony
            }

        } 
        
        //std::cout << sandMove << std::endl;

        if (sandMove) {
            if (playerObject->get_transform().m_position.x >= 1.0f) {
                playerObject->get_transform().m_position.x -= 4.5f * dt;
            }
            if (playerObject->get_transform().m_position.x <= 1.0f) {
                playerObject->get_transform().m_position.y += 2.0f * dt;
                if (playerObject->get_transform().m_position.y >= 0.01f) {
                    sandMove = false;
                }
            }
            

        }

    }

    void trampoliner(std::shared_ptr<SceneGraphNode> interacter, float dt)
    {
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger)) {
            

            playerObject->velocity.y = 10.0f;
            playerObject->canJump = false;
        }
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
            setTrueStencil(interacter);
            if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
                setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        else {
            setFalseStencil(interacter);
        }

    }

    void hustawker(std::shared_ptr<SceneGraphNode> interacter, std::shared_ptr<SceneGraphNode> seat, float dt)
    {
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger)) 
        {
            hustawkerMove = true;
            playerObject->velocity.y = 10.0f;
            hustawkerSpeed = 135.0f;
            std::cout << "dobrzej";
        }
        if (hustawkerMove)
        {
            playerObject->get_transform().m_position.x -= 4.5f * dt;
            //Preety shit rotating of swing
            //It may be updated to smooth rotation in future
            seat->get_transform().z_rotation_angle -= hustawkerSpeed * dt;
            if (seat->m_transform.z_rotation_angle < -80.0f)
            {
                seat->get_transform().z_rotation_angle += hustawkerSpeed * dt;
                hustawkerSpeed /= 2.5f;
                hustawkerSpeed = -hustawkerSpeed;
                hustawkerLeft = false;
            }
            if (hustawkerLeft == false)
            {
                if (seat->m_transform.z_rotation_angle > 0.0f)
                {
                    hustawkerMove = false;
                    hustawkerLeft = true;
                }
            }

            seat->update_transform();
        }
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
            setTrueStencil(interacter);
            setTrueStencil(seat);
            if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
                setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        else {
            setFalseStencil(interacter);
            setFalseStencil(seat);
        }
    }

    void tyrolker(std::shared_ptr<SceneGraphNode> seat, float dt, std::shared_ptr<SceneGraphNode> cola, std::shared_ptr<SceneGraphNode> mentos)
    {
        if (playerObject->collider.boxToBoxCollisioncheck(seat->trigger) && seat->trigger.getPosition().z < 5.55)
        {
            if (!tyrolkerMove) {
                seat->m_transform.x_rotation_angle = 0;
                tyrolkerAngle = 49.0;
                tyrolkerSpeed = 100.0;
            }
            tyrolkerMove = true;
            tyrolkerZero = false;
            playerObject->m_transform.m_position.z += tyrolkerVelocity6* tyrolkerScale/2 * dt;
            playerObject->m_transform.m_position.y = 1;
            playerObject->m_transform.m_position.y += tyrolkerVelocity6* dt;
            //std::cout << "taaaaak";
            seat->m_transform.m_position.z += tyrolkerVelocity6* tyrolkerScale/2 * dt;
            seat->trigger.setPosition(seat->m_transform.m_position);
            seat->update_transform();
            
            if (seat->trigger.getPosition().z > 4.0 && tyrolkerMove && seat->m_transform.x_rotation_angle < 145)
            {
                tyrolkerLaunch = true;
                seat->m_transform.x_rotation_angle += 200.0 * dt;
                //playerObject->m_transform.m_position.z += 6.0 * dt;
                //playerObject->m_transform.m_position.y += 7.5 * dt;
            }

        }
        else if (!playerObject->collider.boxToBoxCollisioncheck(seat->trigger) && seat->trigger.getPosition().z > -10.0)
        {
            
            if (tyrolkerLaunch) {
                playerObject->m_transform.m_position.z += tyrolkerVelocity6 * dt;
                playerObject->m_transform.m_position.y += 2* tyrolkerVelocity6 * dt;
                tyrolkerLaunchCounter++;
                if (tyrolkerLaunchCounter == tyrolkerLaunchEdge* tyrolkerScale) {
                    tyrolkerLaunch = false;
                    tyrolkerLaunchCounter = 0;
                }
            }
            
            tyrolkerMove = false;
            seat->m_transform.m_position.z -= 1.75 * dt;
            seat->trigger.setPosition(seat->m_transform.m_position);
            seat->update_transform();

            if (!tyrolkerMove && !tyrolkerZero)
            {
                seat->m_transform.x_rotation_angle += tyrolkerDir * tyrolkerSpeed * dt;
                
                if (tyrolkerAngle < 5) {
                    tyrolkerZero = true;
                }

                if (tyrolkerSpeed > 45) {
                    if (seat->m_transform.x_rotation_angle < 0 && tyrolkerDir == -1) { tyrolkerSpeed = tyrolkerSpeed - 0.88; }
                    if (seat->m_transform.x_rotation_angle > 0 && tyrolkerDir ==  1) { tyrolkerSpeed = tyrolkerSpeed - 0.66; }
                }

                if (tyrolkerZero) {
                    seat->m_transform.x_rotation_angle = 0;
                }
                else{
                    if (tyrolkerDir == -1 && seat->m_transform.x_rotation_angle < -tyrolkerAngle) {
                    tyrolkerDir = 1;
                    tyrolkerAngle = tyrolkerAngle - 7.0;
                    }
                    if (tyrolkerDir == 1 && seat->m_transform.x_rotation_angle > tyrolkerAngle) {
                    tyrolkerDir = -1;
                    tyrolkerAngle = tyrolkerAngle - 7.0;
                    }
                }
            }
        }
    }

    void wazker(std::shared_ptr<SceneGraphNode> interacter, float dt) {

        //TODO: 





        //change outline
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
            setTrueStencil(interacter);
            if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
                setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        else {
            setFalseStencil(interacter);
        }
    }
    void slider(std::shared_ptr<SceneGraphNode> interacter, float dt) {

        //TODO: 




        //change outline
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
            setTrueStencil(interacter);
            if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
                setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        else {
            setFalseStencil(interacter);
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
    void setOutlineColor(glm::vec3 temp) {
        outlineColor = temp;
    }
    glm::vec3 getOutlineColor() {
        return outlineColor;
    }

    void setFalseStencil(std::shared_ptr<SceneGraphNode> interacter) {
        if (interacter->getStencil() != false) {
            interacter->setStencil(false);
        }
    }
    void setTrueStencil(std::shared_ptr<SceneGraphNode> interacter) {
        if (interacter->getStencil() != true) {
            interacter->setStencil(true);
        }
    }
};

#endif
