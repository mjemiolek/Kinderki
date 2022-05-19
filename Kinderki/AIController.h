#pragma once

#ifndef AICONTROLLER_H
#define AICONTROLLER_H

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
#include <stdlib.h>
#include <ctime>

#include "SceneGraph.h"


class AIController {
private:
    std::shared_ptr<SceneGraphNode> AIObject;
    enum StateType{Move, Interact};
public:
    AIController(std::shared_ptr<SceneGraphNode> AI) {
        this->AIObject = AI;
    }

    bool triggerCollision(std::shared_ptr<SceneGraphNode> player) {
        //Posistion
        glm::vec3 thisAI = AIObject->get_transform().m_position;
        glm::vec3 pla = player->trigger.getPosition();
        //distance
        float distance = sqrt((pla.x - thisAI.x) * (pla.x - thisAI.x) + (pla.y - thisAI.y) * (pla.y - thisAI.y) + (pla.z - thisAI.z) * (pla.z - thisAI.z));
        //std::cout << "x: " << playerObject->get_transform().m_position.x << "y: " << playerObject->get_transform().m_position.y << "z: " << playerObject->get_transform().m_position.z << std::endl;
        if (distance < player->trigger.getRadius()) {

            return true;

        }
        return false;
    }
    void interact(GLFWwindow* window, std::shared_ptr<SceneGraphNode> interacter,PlayerController* gracz, float dt) {
        if (triggerCollision(interacter)) {
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
                gracz->setCandyCount(gracz->getCandyCount() - 1);
                std::cout << "Interaction. " << std::endl;
            }
        }
    }

    bool checkForInteraction(PlayerController* gracz) {
        if (gracz->triggerCollision(AIObject)) return true;
        return false;
    }

    void move(GLFWwindow* window, float deltaTime) {
        std::srand(time(NULL));
        int number;
        number = rand() % 4;
        switch (number) {
        case 1:
            AIObject->get_transform().m_position.z -= 2.5f * deltaTime;
            break;
        case 2:
            AIObject->get_transform().m_position.z += 2.5f * deltaTime;
            break;
        case 3:
            AIObject->get_transform().m_position.x -= 2.5f * deltaTime;
            break;
        case 4:
            AIObject->get_transform().m_position.x += 2.5f * deltaTime;
            break;

        }
        AIObject->update_transform();
        AIObject->collider.setPosition(AIObject->get_transform().m_position);

    }
    void ChangeState(GLFWwindow* window, float deltaTime, PlayerController* gracz) {
        StateType CurrentState = Move;
        switch (CurrentState)
        {
        case Move:
            move(window, deltaTime);
            if (checkForInteraction(gracz)) CurrentState = Interact;
            break;
        case Interact:
            if (!checkForInteraction(gracz)) CurrentState = Move;
        }
        int count = 0;


    }
};

#endif