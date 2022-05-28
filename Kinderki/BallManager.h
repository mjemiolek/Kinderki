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

    void manageBall(GLFWwindow* window, float dt)
    {
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
            ball->get_transform().m_position = glm::vec3(12.0f, 2.5f, 15.0f);
        }
        //ball logic
        float vectorx = (ball->get_transform().m_position.x - playerObject->get_transform().m_position.x);
        float vectorz = (ball->get_transform().m_position.z - playerObject->get_transform().m_position.z);
        //apply force
        if (ball->collider.sphereToSphereCollisionCheck(playerObject->collider))
        {
            ball->velocity.x = 8 * vectorx;
            ball->velocity.z = 8 * vectorz;
        }
        float stopVal= 0.01f;
        //decelerate
        if (ball->velocity.x > stopVal || ball->velocity.x < -stopVal)
        {
            ball->velocity.x -= ball->velocity.x * dt;
            ball->get_transform().y_rotation_angle += 90.0f * dt;
            ball->get_transform().x_rotation_angle += 90.0f * dt;
        }
        if (ball->velocity.z > stopVal || ball->velocity.z < -stopVal)
        {
            ball->velocity.z -= ball->velocity.z * dt;
            ball->get_transform().y_rotation_angle += 90.0f * dt;
            ball->get_transform().z_rotation_angle += 90.0f * dt;
        }
        //stop
        if (ball->velocity.x <= stopVal && ball->velocity.x >= -stopVal)
        {
            ball->velocity.x = 0.0f;
        }
        if (ball->velocity.z <= stopVal && ball->velocity.z >= -stopVal)
        {
            ball->velocity.z = 0.0f;
        }
        //Don't let the ball to go into ground
        if (ball->get_transform().m_position.y<-0.01f) ball->get_transform().m_position.y = 0.0f;


        ball->update_transform();
        ball->collider.setPosition(ball->get_transform().m_position);
    }
};

#endif