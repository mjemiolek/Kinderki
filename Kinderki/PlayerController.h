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
    bool goInGround = false;
    bool hustawkerMove = false, hustawkerLeft = true;
    bool canInteract = false;
    float hustawkerSpeed;
    glm::vec3 outlineColor;
   
    bool tyrolkerMove = false;
    bool tyrolkerZero = true;
    bool tyrolkerLaunch = false;
    bool tyrolkerCola = false;
    bool tyrolkerMentos = false;
    int tyrolkerLaunchCounter = 0;
    int tyrolkerLaunchEdge = 20;
    int tyrolkerDir = -1;
    int tyrolkerAngle = 49;
    int tyrolkerSpeed = 100;
    float tyrolkerScale = 1.0;
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

            //move Player to position (28.0f, 0.2f, 10.5f)
            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
            {
                playerObject->get_transform().m_position = glm::vec3(27.0f, 0.2f, 9.17f);
                playerObject->canInToGround = false;
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
        float deviation = (step/100.0f)*3.0f;
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

    bool checkForInteraction(GLFWwindow* window, std::shared_ptr<SceneGraphNode> AI1, std::shared_ptr<SceneGraphNode> AI2, std::shared_ptr<SceneGraphNode> AI3, std::shared_ptr<SceneGraphNode> AI4) {
        if ((playerObject->collider.sphereToSphereCollisionCheck(AI1->trigger)) || 
            (playerObject->collider.sphereToSphereCollisionCheck(AI2->trigger)) ||
            (playerObject->collider.sphereToSphereCollisionCheck(AI3->trigger)) ||
            (playerObject->collider.sphereToSphereCollisionCheck(AI4->trigger))) {
            std::cout << "Press E to interact with kid" << std::endl;
            canInteract = true;
        }
        if (canInteract = true) {
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                std::cout << "Player interacted with Kid" << std::endl;
                return true;
            }
        }
        canInteract = false;
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
                playerObject->canInToGround = true;
                goInGround = true;
            }
        }
        if (goInGround)
        {
            playerObject->get_transform().m_position.y -= 2.0f * dt;
            if (playerObject->get_transform().m_position.y < -1.5f) {
                playerObject->get_transform().m_position.y += 2.0f * dt;
                sandMove = true;
                goInGround = false;
                //playerObject->get_transform().m_position.x = -5.0f;
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
                    playerObject->canInToGround = false;
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
        //check for cola
        if (seat->trigger.boxToBoxCollisioncheck(cola->trigger) &&  !tyrolkerCola) {
            //seat->add_child(cola);
            cola->m_transform.m_position = seat->m_transform.m_position;
            tyrolkerScale = 1.15;
            tyrolkerCola = true;
        }
        //check for mentos
        if (seat->trigger.boxToBoxCollisioncheck(mentos->trigger)&& !tyrolkerMentos) {
            //seat->add_child(mentos);

            tyrolkerMentos = true;
        }

        if (tyrolkerCola && tyrolkerMentos) {
            tyrolkerScale = 1.5;
        }
        //if player is on seat and aerial is not at the end yet
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
            //keep player at position
            playerObject->m_transform.m_position.y = 1.4f;
            playerObject->velocity.y = 0.0f;
            playerObject->applyOppositeGravity(dt);
            
            seat->m_transform.m_position.z += tyrolkerVelocity6* tyrolkerScale/2 * dt;
            //seat->trigger.setPosition(seat->m_transform.m_position); //errrrrrrrrorrrrrrrrrrr
            seat->trigger.setPosition(glm::vec3(seat->m_transform.m_position.x,-1.5f,seat->m_transform.m_position.z));
            playerObject->update_transform();
            seat->update_transform();
            cola->update_transform();
            

            if (seat->trigger.getPosition().z > 5.0 && tyrolkerMove && seat->m_transform.x_rotation_angle < 145)
            {
                tyrolkerLaunch = true;
                seat->m_transform.x_rotation_angle += 50 * tyrolkerScale * dt;
            }

        }
        else if (!playerObject->collider.boxToBoxCollisioncheck(seat->trigger) && seat->trigger.getPosition().z > -10.0)
        {

            
            tyrolkerMove = false;
            seat->m_transform.m_position.z -= 1.75 * dt;
            //seat->trigger.setPosition(seat->m_transform.m_position); //errrrrrrrrorrrrrrrrrrr
            seat->trigger.setPosition(glm::vec3(seat->m_transform.m_position.x, -1.5f, seat->m_transform.m_position.z));
            seat->update_transform();
            cola->update_transform();

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
        if (tyrolkerLaunch) {
            playerObject->m_transform.m_position.z += tyrolkerVelocity6 *tyrolkerScale / 1.5 * dt;
            playerObject->m_transform.m_position.y += tyrolkerVelocity6 * tyrolkerScale * dt;
            tyrolkerLaunchCounter++;
            if (tyrolkerLaunchCounter == tyrolkerLaunchEdge * tyrolkerScale) {
                tyrolkerLaunch = false;
                tyrolkerLaunchCounter = 0;
            }
        }
    }

    void wazker(std::shared_ptr<SceneGraphNode> interacter, float dt) {

        //default seesaw behaviour
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(1))) {
            if (interacter->get_transform().z_rotation_angle > -14.0f)
            {
                interacter->get_transform().z_rotation_angle -= 140.0f * dt;
            }
            interacter->additionalColliders.at(0).setPosition(glm::vec3(8.0f, -0.4f, -4.5f));
            interacter->update_transform();
        }
        else if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(2))) {
            if (interacter->get_transform().z_rotation_angle < 14.0f)
            {
                interacter->get_transform().z_rotation_angle += 140.0f * dt;
            }
            interacter->additionalColliders.at(0).setPosition(glm::vec3(8.0f, -0.4f, -4.5f));
            interacter->update_transform();
        } else {
            if (interacter->get_transform().z_rotation_angle < -2.0f)
            {
                interacter->get_transform().z_rotation_angle += 80.0f * dt;
            } else if (interacter->get_transform().z_rotation_angle > 2.0f)
            {
                interacter->get_transform().z_rotation_angle -= 80.0f * dt;
            }
            else {
                interacter->setRotation(0.0f, 0.0f, 0.0f);
            }
            interacter->additionalColliders.at(0).setPosition(glm::vec3(8.0f, 0.2f, -4.5f));
            interacter->update_transform();
        }

        
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
    //void slider(std::shared_ptr<SceneGraphNode> interacter, float dt) {

    //    //TODO: 




    //    //change outline
    //    if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
    //        setTrueStencil(interacter);
    //        if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
    //            setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
    //        }
    //    }
    //    else {
    //        setFalseStencil(interacter);
    //    }
    //}


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
