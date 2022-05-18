#pragma once
#ifndef BALLMANAGER_H
#define BALLMANAGER_H

#include "SceneGraph.h"

class BallManager {
private:
    std::shared_ptr<SceneGraphNode> playerObject;
    std::shared_ptr<SceneGraphNode> ball;
public:
    BallManager(std::shared_ptr<SceneGraphNode> ball, std::shared_ptr<SceneGraphNode> player) {
        this->ball = ball;
        playerObject = player;
    }

    void manageBall(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            ball->get_transform().m_position = glm::vec3(0.0f, 4.5f, -5.0f);
        }
        //ball logic
        if (ball->collider.sphereToSphereCollisionCheck(playerObject->collider))
        {
            ball->velocity.x = 2 * playerObject->velocity.x;
            ball->velocity.z = 2 * playerObject->velocity.z;
        }
        if (ball->velocity.x > 0)
        {
            ball->velocity.x -= 0.01f;
        }
        if (ball->velocity.x < 0)
        {
            ball->velocity.x += 0.01f;
        }
        if (ball->velocity.z > 0)
        {
            ball->velocity.z -= 0.01f;
        }
        if (ball->velocity.z < 0)
        {
            ball->velocity.z += 0.01f;
        }


        ball->update_transform();
        ball->collider.setPosition(ball->get_transform().m_position);
    }
};

#endif