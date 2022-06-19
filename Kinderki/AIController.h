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
};

#endif