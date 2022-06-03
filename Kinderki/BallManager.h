#pragma once
#ifndef BALLMANAGER_H
#define BALLMANAGER_H

#include "SceneGraph.h"

class BallManager {
private:
    std::shared_ptr<SceneGraphNode> playerObject;
    std::shared_ptr<SceneGraphNode> ball;
    std::shared_ptr<SceneGraphNode> damagedwall;
    float kickpower = 16.0f;
    float decelerateVar = 0.5f;
public:
    BallManager(std::shared_ptr<SceneGraphNode> ball, std::shared_ptr<SceneGraphNode> player, std::shared_ptr<SceneGraphNode> damagedwall) {
        this->ball = ball;
        playerObject = player;
        this->damagedwall = damagedwall;
    }
    //TODO: 
    // bouncing off walls
    // fix of going player into ground (its corelated with sphere collider or smth)
    // fix ball going through walls or mask it
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
            ball->velocity.x = kickpower * vectorx;
            ball->velocity.z = kickpower * vectorz;
        }
        float stopVal= 0.01f;
        //decelerate
        if (ball->velocity.x > stopVal || ball->velocity.x < -stopVal)
        {
            ball->velocity.x -= ball->velocity.x * dt * decelerateVar;
            //fix this or wypierdol this
            /*ball->get_transform().y_rotation_angle += 90.0f * dt;
            ball->get_transform().x_rotation_angle += 90.0f * dt;*/
        }
        if (ball->velocity.z > stopVal || ball->velocity.z < -stopVal)
        {
            ball->velocity.z -= ball->velocity.z * dt * decelerateVar;
            //fix this or wypierdol this 
            /*ball->get_transform().y_rotation_angle += 90.0f * dt;
            ball->get_transform().z_rotation_angle += 90.0f * dt;*/
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


        //update position
        ball->update_transform();
        ball->collider.setPosition(ball->get_transform().m_position);

        //check for trigger in damagedwall
        if (ball->collider.boxToBoxCollisioncheck(damagedwall->trigger))
        {
            std::cout << "Ball hitted the wall. Good job comrade.\n";
        }
    }
};

#endif