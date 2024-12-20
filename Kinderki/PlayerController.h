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

#include <mmcobj.h>

#include "SceneGraph.h"

bool turnOffTutorial = false;

class PlayerController {
private:
    std::shared_ptr<SceneGraphNode> playerObject;
    int candyCount, textureLayer = 0;
    float speed = 3.5f;
    float angle = 0.0f;
    bool sandMove = false;
    bool goInGround = false;
    bool hustawkerMove = false, hustawkerLeft = true, hustawkerWait=false;
    bool paidBoy1 = false, paidBoy2 = false, paidBoy3 = false, paidBoy4 = false, paidBoy5 = false;
    bool canInteract = false;
    bool canMove = true;
    bool finishedTutorial = false;
    int whichKidInteractedWith ;
    float hustawkerSpeed;
    glm::vec3 outlineColor;

    unsigned int dt, ct;
   
    bool tyrolkerMove = false;
    bool tyrolkerZero = true;
    bool tyrolkerLaunch = false;
    float tyrolkerVelocity6 = 6.0f;
    bool tyrolkerCola = false;
    bool tyrolkerMentos = false;
    int tyrolkerLaunchCounter = 0;
    int tyrolkerLaunchEdge = 20;
    int tyrolkerDir = -1;
    int tyrolkerAngle = 49;
    int tyrolkerSpeed = 100;
    float tyrolkerScale = 1.0f;
    

    bool candy1collected = false;
    bool candy2collected = false;
    bool candy3collected = false;
    bool candy4collected = false;
    bool candy5collected = false;
    bool candy6collected = false;

    float nowTime = 0.0f;
    float timeVariable = 0.0f;

    float hustawkerTimeToWait = 1.0f; //seconds
    bool hustawkerBoyPaid = false;

    float wazkerTimeToWait = 1.0f; //seconds
    bool wazkerBoyPaid = false;
    bool wazkerWait=false, wazkerMove=false;

    bool moveAnimation = false;
    bool tempCheckCarry = false;
public:
    bool alreadyescapedTyrolker = false;
    bool moveShovel = false;
    bool canJumpAnimation = true;
    bool hammerAnimation = false;
    bool gokuAnimation = false;

    PlayerController(std::shared_ptr<SceneGraphNode> player) {
        this->playerObject = player;
        candyCount = 0;
        ct = 0;
        outlineColor = glm::vec3(1.0f, 1.0f, 1.0f);
        std::cout << "candy count: " << candyCount << std::endl;
    }
    ~PlayerController() {}
    void move(GLFWwindow* window, float deltaTime,float actualTime)
    {
        if (canMove) {
            if (!sandMove) {
                playerObject->velocity.z = 0.0f;
                playerObject->velocity.x = 0.0f;
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                    angle = 0.0f + camera.Yaw;
                    playerObject->velocity.z = speed * sin(glm::radians(camera.Yaw));
                    playerObject->velocity.x = speed * cos(glm::radians(camera.Yaw));
                    moveAnimation = true;
                }
                else {
                    moveAnimation = false;
                }
                if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                    angle = 180.0f + camera.Yaw;
                    playerObject->velocity.z = -speed * sin(glm::radians(camera.Yaw));
                    playerObject->velocity.x = -speed * cos(glm::radians(camera.Yaw));
                    moveAnimation = true;
                }
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                    /*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) angle = 315.0f + camera.Yaw;
                    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) angle = 225.0f + camera.Yaw;
                    else*/ angle = 270.0f + camera.Yaw;
                    playerObject->velocity.z = -speed * cos(glm::radians(camera.Yaw));
                    playerObject->velocity.x = speed * sin(glm::radians(camera.Yaw));
                    moveAnimation = true;
                }
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                    /*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) angle = 45.0f + camera.Yaw;
                    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) angle = 135.0f + camera.Yaw;
                    else*/ angle = 90.0f + camera.Yaw;
                    playerObject->velocity.z = speed * cos(glm::radians(camera.Yaw));
                    playerObject->velocity.x = -speed * sin(glm::radians(camera.Yaw));
                    moveAnimation = true;
                }
                //angle += camera.Yaw;
                playerObject->get_transform().y_rotation_angle = angle + 90.0f;
                //rotate(playerObject->velocity, deltaTime);
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
                if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
                {
                    //playerObject->get_transform().m_position.y += 0.1f;
                    //playerObject->velocity.y = speed;
                }
                //jump
                if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                {
                    if (playerObject->canJump == true)
                    {
                        moveAnimation = false;
                        canJumpAnimation = true;
                        playerObject->velocity.y = 5.0f;
                    }
                    playerObject->canJump = false;
                }
                if (!playerObject->canJump) {
                    moveAnimation = false;
                }
            }

            nowTime = actualTime; //updating time
        }

    }

    void rotate(glm::vec3 direction, float deltaTime)
    {
        //float angle = 0.0f;
        //float step = 600.0f;
        //float deviation = (step / 100.0f) * 3.0f;
        //Specify direction
        //if (direction.x == 0.0f && direction.z == 0.0f) { angle = playerObject->get_transform().y_rotation_angle; }
        //if (direction.x == speed && direction.z == 0.0f) { angle = 90.0f; }              //right
        //else if (direction.z == speed && direction.x == 0.0f) { angle = 180.0f; }        //down
        //else if (direction.x == -speed && direction.z == 0.0f) { angle = 270.0f; }       //left
        //else if (direction.z == -speed && direction.x == 0.0f) { angle = 0.0f; }         //up
        //else if (direction.x == speed && direction.z == speed) { angle = 135.0f; }    //right-down
        //else if (direction.z == speed && direction.x == -speed) { angle = 225.0f; }   //down-left
        //else if (direction.x == -speed && direction.z == -speed) { angle = 315.0f; }  //left-up
        //else if (direction.z == -speed && direction.x == speed) { angle = 45.0f; }  //up-right
        //else { angle = 0.0f; }   
        //angle += camera.Yaw;
//Rotate player towards direction
        //if (playerObject->get_transform().y_rotation_angle < angle - deviation || playerObject->get_transform().y_rotation_angle > angle + deviation)
        //{
        //    float angle1 = playerObject->get_transform().y_rotation_angle - angle,
        //        angle2 = angle - playerObject->get_transform().y_rotation_angle;
        //    if (angle1 < 0.0f) angle1 += 360.0f;
        //    if (angle2 < 0.0f) angle2 += 360.0f;
        //    if (angle1 < angle2)
        //    {
        //        //Rotate in left direction
        //        playerObject->get_transform().y_rotation_angle -= step * deltaTime;
        //        if (playerObject->get_transform().y_rotation_angle < 0.0f)
        //        {
        //            playerObject->get_transform().y_rotation_angle += 360.0f;
        //        }
        //    }
        //    else {
        //        //Rotate in right direction
        //        playerObject->get_transform().y_rotation_angle += step * deltaTime;
        //        if (playerObject->get_transform().y_rotation_angle >= 360.0f)
        //        {
        //            playerObject->get_transform().y_rotation_angle -= 360.0f;
        //        }
        //    }
        //}
        //else {
            //playerObject->get_transform().y_rotation_angle = angle + 90.0f;
        //}
        //std::cout << playerObject->get_transform().y_rotation_angle<<std::endl;
    }

    void checkForInteraction(GLFWwindow* window, std::shared_ptr<SceneGraphNode> AI1, std::shared_ptr<SceneGraphNode> AI2, std::shared_ptr<SceneGraphNode> AI3, std::shared_ptr<SceneGraphNode> AI4, std::shared_ptr<SceneGraphNode> AI5) {
        if ((playerObject->collider.sphereToSphereCollisionCheck(AI1->trigger))) {
            if (!paidBoy1) {
                //std::cout << "Press E to interact with kid" << std::endl;
                whichKidInteractedWith = 1;
                canInteract = true;
            }
            else {
                //std::cout << "This Kid already helped you" << std::endl;
            }
        }
        if (playerObject->collider.sphereToSphereCollisionCheck(AI2->trigger)) {
            if (!paidBoy2) {
                //std::cout << "Press E to interact with kid" << std::endl;
                whichKidInteractedWith = 2;
                canInteract = true;
            }
            else {
                //std::cout << "This Kid already helped you" << std::endl;
            }
        }
        if (playerObject->collider.sphereToSphereCollisionCheck(AI3->trigger)) {
            if (!paidBoy3) {
               // std::cout << "Press E to interact with kid" << std::endl;
                whichKidInteractedWith = 3;
                canInteract = true;
            }
            else {
                //std::cout << "This Kid already helped you" << std::endl;
            }
        }
        if (playerObject->collider.sphereToSphereCollisionCheck(AI4->trigger)) {
            if (!paidBoy4) {
                //std::cout << "Press E to interact with kid" << std::endl;
                whichKidInteractedWith = 4;
                canInteract = true;
            }
            else {
                //std::cout << "This Kid already helped you" << std::endl;
            }
        }
        if (playerObject->collider.sphereToSphereCollisionCheck(AI5->trigger)) {
            if (!paidBoy5) {
                //std::cout << "Press E to interact with kid" << std::endl;
                whichKidInteractedWith = 5;
                canInteract = true;
            }
            else {
                //std::cout << "This Kid already helped you" << std::endl;
            }
        }

        if ((finishedTutorial == true) && (canInteract == true) && (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)) {
            //Here interaction happens
            canMove = false;
            std::cout << "Player interacted with Kid" << std::endl;
            textureLayer = 1;
            ct = glfwGetTime();
            switch (getWichKidInteractedWith()) {
             
                dt = ct;
            case 1:
                std::cout << "interacted with: " << whichKidInteractedWith << std::endl;
                if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount == 0) && (ct - dt > 2)) {
                    textureLayer = 2;
                }
                else if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount >= 0) && (ct - dt > 2)) {
                    candyCount -= 1;
                    textureLayer = 3;
                    paidBoy1 = true;
                  }
                 break;
            case 2:
                std::cout << "interacted with: " << whichKidInteractedWith << std::endl;
                if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount == 0)) {
                    textureLayer = 2;
                }
                else if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount >= 0) && (ct - dt > 2)) {
                    hustawkerBoyPaid = true;
                    candyCount -= 1;
                    textureLayer = 6;
                    paidBoy2 = true;
                }
                break;
            case 3:
                std::cout << "interacted with: " << whichKidInteractedWith << std::endl;
                if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount == 0) && (ct - dt > 2)) {
                    textureLayer = 2;
                }
                else if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount >= 0) && (ct - dt > 2)) {
                    candyCount -= 1;
                    textureLayer = 5;
                    paidBoy3 = true;
                }
                break;
            case 4:
                std::cout << "interacted with: " << whichKidInteractedWith << std::endl;
                if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount == 0) && (ct - dt > 2)) {
                    textureLayer = 2;
                }
                else if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount >= 0) && (ct - dt > 2)) {
                    candyCount -= 1;
                    textureLayer = 4;
                    paidBoy4 = true;
                }
                break;
            case 5:
                std::cout << "interacted with: " << whichKidInteractedWith << std::endl;
                if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount == 0) && (ct - dt > 2)) {
                    textureLayer = 2;
                }
                else if ((glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) && (candyCount >= 0) && (ct - dt > 2)) {
                    wazkerBoyPaid = true;
                    candyCount -= 1;
                    textureLayer = 6;
                    paidBoy5 = true;
                }
                break;
            }
            canMove = true;
        }
        canInteract = false;
    }


    void sandPiter(GLFWwindow* window, std::shared_ptr<SceneGraphNode> interacter,float dt, std::shared_ptr<SceneGraphNode> lopatka) {
        if (sandMove) {
            if (playerObject->get_transform().m_position.x >= 1.0f) {
                playerObject->get_transform().m_position.x -= 4.5f * dt;
            }
            if (playerObject->get_transform().m_position.x <= 1.0f) {
                playerObject->get_transform().m_position.y += 2.0f * dt;
                if (playerObject->get_transform().m_position.y >= 0.01f) {
                    sandMove = false;
                    playerObject->canInToGround = false;
                    turnOffTutorial = true;
                    setFinishedTutorial(true);
                }
            }
        }
        if (goInGround)
        {
            if (moveShovel) {
                lopatka->get_transform().m_position.x = -50.0f;
                lopatka->update_transform();
                moveShovel = false;
            }
            playerObject->get_transform().m_position.y -= 2.0f * dt;
            if (playerObject->get_transform().m_position.y < -1.5f) {
                playerObject->get_transform().m_position.y += 2.0f * dt;
                sandMove = true;
                goInGround = false;
            }
        }
        if (playerObject->m_children.size() == 0) {
            setFalseStencil(interacter);
            return;
        }
        
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger) && playerObject->m_children.at(0)->getMovableType() == TOSANDPIT) {
            //setTrueStencil(interacter);
            //if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
            //    setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f)); //zielony
            //}
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                playerObject->canInToGround = true;
                goInGround = true;
                moveShovel = true;
            }
        }
        //if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger) && !playerObject->m_children.at(0)->getMovableType() == TOSANDPIT) {
        //    setTrueStencil(interacter);
        //    if (getOutlineColor() != glm::vec3(1.0f, 0.0f, 0.0f)) {
        //        setOutlineColor(glm::vec3(1.0f, 0.0f, 0.0f)); //czerwony
        //    }

        //} 


    }

    void trampoliner(std::shared_ptr<SceneGraphNode> interacter, float dt)
    {
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger)) {
            

            playerObject->velocity.y = 8.9f;
            playerObject->canJump = false;
        }
        //if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
        //    setTrueStencil(interacter);
        //    if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
        //        setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
        //    }
        //}
        //else {
        //    setFalseStencil(interacter);
        //}
    }

    void liner(Collider interacter)
    {
        if (playerObject->collider.boxToBoxCollisioncheck(interacter)) {
            playerObject->velocity.x += 1.69f;
        }
    }


    void hustawker(std::shared_ptr<SceneGraphNode> interacter, std::shared_ptr<SceneGraphNode> seat, float dt)
    {
        if (playerObject->collider.boxToBoxCollisioncheck(interacter->trigger) && hustawkerBoyPaid) 
        {
            hustawkerWait = true;
            timeVariable = nowTime;
            hustawkerBoyPaid = false;
        }
        if (hustawkerWait)
        {
            if (!playerObject->collider.boxToBoxCollisioncheck(interacter->trigger)) //if you jump from hustawker before boost delete boost
            {
                hustawkerWait = false;
            }

            //std::cout << nowTime << "   " << timeVariable << std::endl;
            if (getGokuAnimation())  //time to wait
            {
                hustawkerWait = false;
                hustawkerMove = true;
                hustawkerBoyPaid = true;
                playerObject->velocity.y = 10.0f;
                hustawkerSpeed = 135.0f;
            }
            
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
        //if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
        //    setTrueStencil(interacter);
        //    setTrueStencil(seat);
        //    if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
        //        setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
        //    }
        //}
        //else {
        //    setFalseStencil(interacter);
        //    setFalseStencil(seat);
        //}
    }

    void tyrolker(std::shared_ptr<SceneGraphNode> seat, float dt, std::shared_ptr<SceneGraphNode> cola, std::shared_ptr<SceneGraphNode> mentos, std::shared_ptr<SceneGraphNode> tyrol)
    {
        //if (playerObject->collider.boxToBoxCollisioncheck(tyrol->additionalTriggers.at(1))) {
        //    setTrueStencil(tyrol);
        //    setTrueStencil(seat);
        //    if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
        //        setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
        //    }
        //}
        //else {
        //    setFalseStencil(tyrol);
        //    setFalseStencil(seat);
        //}
        //check for puffed_cola with mentos
        if (seat->trigger.boxToBoxCollisioncheck(cola->trigger) &&  !tyrolkerCola) {
            if (cola->m_transform.m_scale > 1.19f) //this means its puffed_cola
            {
                //Hide Cola
                Model nothing("res/models/movable/nothing.obj");
                cola->modelTemp = nothing;
                cola->m_transform.m_position.x = 100.0f;
                cola->update_transform();
                //change seat model    
                Model seatWithCola("res/models/level/aerialrunnway_seat_with_cola.obj");
                unsigned int texaerialseatcola = loadTexture("res/textures/models/aerialrunnway_seat_with_cola.png");
                seat->texture = texaerialseatcola;
                seat->modelTemp = seatWithCola;
                seat->m_transform.m_scale = 10.0f;
                seat->modelOutline = nothing;
                seat->update_transform();
                            
                tyrolkerCola = true;
                tyrolkerMentos = true;
                tyrolkerScale = 1.5f;
                tyrolkerVelocity6 = 9.0f;
            }
        }

        if (alreadyescapedTyrolker) {
            //change seat model 
            tyrolkerScale = 1.0f;
            tyrolkerVelocity6 = 6.0f;
        }

        //if player is on seat and aerial is not at the end yet
        if (playerObject->collider.boxToBoxCollisioncheck(seat->trigger) && seat->trigger.getPosition().z < 5.55)
        {
            playerObject->canJump = false;
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
            

            if (seat->trigger.getPosition().z > 5.0 && tyrolkerMove && seat->m_transform.x_rotation_angle < 145)
            {
                tyrolkerLaunch = true;
                seat->m_transform.x_rotation_angle += 50 * tyrolkerScale * dt;
            }

            //timeVariable = nowTime;
        }

        //if player is not on seat and aerial is not at beggining
        else if (!playerObject->collider.boxToBoxCollisioncheck(seat->trigger) && seat->trigger.getPosition().z > -10.0)
        {
            tyrolkerMove = false;
            seat->m_transform.m_position.z -= 1.75 * dt;
            //seat->trigger.setPosition(seat->m_transform.m_position); //errrrrrrrrorrrrrrrrrrr
            seat->trigger.setPosition(glm::vec3(seat->m_transform.m_position.x, -1.5f, seat->m_transform.m_position.z));
            seat->update_transform();

            if (!tyrolkerMove && !tyrolkerZero)
            {
                seat->m_transform.x_rotation_angle += tyrolkerDir * tyrolkerSpeed * dt;
                
                if (tyrolkerAngle < 5 || seat->trigger.getPosition().z < -9.9f) {
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
            //if (nowTime - timeVariable >= 1.5f) {
             //   tyrolkerLaunch = false;
            //}
        }
    }

    void wazker(std::shared_ptr<SceneGraphNode> interacter, float dt) 
    {
        //default seesaw behaviour
        if (!wazkerBoyPaid)
        {
            defaultWazkerBehaviour(interacter,dt);
        }
        //behaviour when wazker boy paid
        if (wazkerBoyPaid && playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(1)) && !wazkerWait && !wazkerMove) //wazkerBoyPaid and proper position
        {
            //Go To delay
            wazkerWait = true;
            timeVariable = nowTime;
        }
        else 
        {
            defaultWazkerBehaviour(interacter, dt);
        }
        if (wazkerWait)
        {
            if (!playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(1))) //if you jump from wazker before boost delete boost
            {
                wazkerWait = false;
            }
            defaultWazkerBehaviour(interacter, dt);
            if (getHammerAnimation())  //time to wait
            {
                wazkerWait = false;
                //go to wazker move
                wazkerMove = true;
                timeVariable = nowTime;
                playerObject->velocity.y = 12.0f;
            }
        }
        if (wazkerMove)
        {
            if (nowTime - timeVariable >= 0.5f)
            {
                wazkerMove = false;
            }
            else
            {
                if (interacter->get_transform().z_rotation_angle < 14.0f)
                {
                    interacter->get_transform().z_rotation_angle += 140.0f * dt;
                }
                interacter->update_transform();
            }
        }

        //change outline
        //if (playerObject->collider.boxToBoxCollisioncheck(interacter->additionalTriggers.at(0))) {
        //    setTrueStencil(interacter);
        //    if (getOutlineColor() != glm::vec3(0.0f, 1.0f, 0.0f)) {
        //        setOutlineColor(glm::vec3(0.0f, 1.0f, 0.0f));
        //    }
        //}
        //else {
        //    setFalseStencil(interacter);
        //}
    }

    void defaultWazkerBehaviour(std::shared_ptr<SceneGraphNode> interacter, float dt)
    {
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
        }
        else {
            if (interacter->get_transform().z_rotation_angle < -2.0f)
            {
                interacter->get_transform().z_rotation_angle += 80.0f * dt;
            }
            else if (interacter->get_transform().z_rotation_angle > 2.0f)
            {
                interacter->get_transform().z_rotation_angle -= 80.0f * dt;
            }
            else {
                interacter->setRotation(0.0f, 0.0f, 0.0f);
            }
            interacter->additionalColliders.at(0).setPosition(glm::vec3(8.0f, 0.2f, -4.5f));
            interacter->update_transform();
        }
    }

    void candier(std::shared_ptr<SceneGraphNode> candy1, std::shared_ptr<SceneGraphNode> candy2, std::shared_ptr<SceneGraphNode> candy3,
        std::shared_ptr<SceneGraphNode> candy4, std::shared_ptr<SceneGraphNode> candy5, std::shared_ptr<SceneGraphNode> candy6, float dt)
    {
        //check for candy1
        if (playerObject->collider.boxToBoxCollisioncheck(candy1->trigger) && !candy1collected) {
            //remove candy
                //change model to nothing
                Model nothing("res/models/movable/nothing.obj");
                candy1->modelTemp = nothing;
            candy1collected = true;
            //actualize candy count
            candyCount++;
        }

        //check for candy2
        if (playerObject->collider.boxToBoxCollisioncheck(candy2->trigger) && !candy2collected) {
            Model nothing("res/models/movable/nothing.obj");
            candy2->modelTemp = nothing;
            candy2collected = true;
            candyCount++;
        }

        //check for candy3
        if (playerObject->collider.boxToBoxCollisioncheck(candy3->trigger) && !candy3collected) {
            Model nothing("res/models/movable/nothing.obj");
            candy3->modelTemp = nothing;
            candy3collected = true;
            candyCount++;
        }

        //check for candy4
        if (playerObject->collider.boxToBoxCollisioncheck(candy4->trigger) && !candy4collected) {
            Model nothing("res/models/movable/nothing.obj");
            candy4->modelTemp = nothing;
            candy4collected = true;
            candyCount++;
        }

        //check for candy5
        if (playerObject->collider.boxToBoxCollisioncheck(candy5->trigger) && !candy5collected) {
            Model nothing("res/models/movable/nothing.obj");
            candy5->modelTemp = nothing;
            candy5collected = true;
            candyCount++;
        }

        //check for candy6
        if (playerObject->collider.boxToBoxCollisioncheck(candy6->trigger) && !candy6collected) {
            Model nothing("res/models/movable/nothing.obj");
            candy6->modelTemp = nothing;
            candy6collected = true;
            candyCount++;
        }

        //Candy rotation
        candy1->get_transform().y_rotation_angle -= 100.0f * dt;
        candy1->update_transform();
        candy2->get_transform().y_rotation_angle -= 100.0f * dt;
        candy2->update_transform();
        candy3->get_transform().y_rotation_angle -= 100.0f * dt;
        candy3->update_transform();
        candy4->get_transform().y_rotation_angle -= 100.0f * dt;
        candy4->update_transform();
        candy5->get_transform().y_rotation_angle -= 100.0f * dt;
        candy5->update_transform();
        candy6->get_transform().y_rotation_angle -= 100.0f * dt;
        candy6->update_transform();
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
    int getWichKidInteractedWith() {
        return whichKidInteractedWith;
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
    bool getMoveAnimation() {
        return moveAnimation;
    }
    bool checkCarry() {
        if (playerObject->m_children.size() == 0) {
            return false;
        }
        if (playerObject->m_children.size() > 0) {
            return true;
        }
    }
    bool getTempCheckCarry() {
        return tempCheckCarry;
    }
    void setTempCheckCarry(bool temp) {
        tempCheckCarry = temp;
    }

    void setFinishedTutorial(bool swap) {
        finishedTutorial = swap;
    }

    bool getFinishedTutorial() {
        return finishedTutorial;
    }
    int getTextureLayer() {
        return textureLayer;
    }
    bool getCanInteract() {
        return canInteract;
    }
    bool getCanJumpAnimation() {
        return canJumpAnimation;
    }
    void setCanJumpAnimation(bool dt) {
        canJumpAnimation = dt;
    }
    bool getWazkerWait() {
        return wazkerWait;
    }
    bool getHammerAnimation() {
        return hammerAnimation;
    }
    void setHammerAnimation(bool dt) {
        hammerAnimation = dt;
    }
    void setWazkerBoyPaid(bool dt) {
        wazkerBoyPaid = dt;
    }
    void setGokuAnimation(bool dt) {
        gokuAnimation = dt;
    }
    bool getGokuAnimation() {
        return gokuAnimation;
    }
    bool getHustawkerWait() {
        return hustawkerWait;
    }
    void setHustawkerBoyPaid(bool dt) {
        hustawkerBoyPaid = dt;
    }

    unsigned int loadTexture(char const* path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
    //bool CanRenderInteraction() {
    //    if ((getFinishedTutorial() == false)/* || (getCanInteract() == false) */ ) return false;
    //    else return true;
    //}
};

#endif
