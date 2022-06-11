#pragma once
#ifndef BALLMANAGER_H
#define BALLMANAGER_H

#include "SceneGraph.h"

class BallManager {
private:
    std::shared_ptr<SceneGraphNode> playerObject;
    std::shared_ptr<SceneGraphNode> ball;
    std::shared_ptr<SceneGraphNode> damagedwall;
    std::shared_ptr<SceneGraphNode> wall;
    float kickpower = 6.9f;
    float decelerateVar = 0.69f;
    float stopVal = 0.01f;
    bool shouldbounceeoffx = false;
    bool shouldbounceeoffz = false;
public:
    BallManager(std::shared_ptr<SceneGraphNode> ball, std::shared_ptr<SceneGraphNode> playerObject, std::shared_ptr<SceneGraphNode> damagedwall, std::shared_ptr<SceneGraphNode> wall) {
        this->ball = ball;
        this->playerObject = playerObject;
        this->damagedwall = damagedwall;
        this->wall = wall;
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
        
        //if(ball->velocity)

        //apply force
        if (ball->collider.sphereToSphereCollisionCheck(playerObject->collider))
        {
            ball->velocity.x = kickpower * vectorx;
            ball->velocity.z = kickpower * vectorz;
        }
        //decelerate
        if (ball->velocity.x > stopVal)
        {
            ball->velocity.x -= ball->velocity.x * dt * decelerateVar;
            ball->get_transform().z_rotation_angle += 200 * ball->velocity.x * dt * decelerateVar;
        }
        if (ball->velocity.x < -stopVal)
        {
            ball->velocity.x -= ball->velocity.x * dt * decelerateVar;
            ball->get_transform().z_rotation_angle += 200 * ball->velocity.x * dt * decelerateVar;
        }

        if (ball->velocity.z > stopVal)
        {
            ball->velocity.z -= ball->velocity.z * dt * decelerateVar;
            ball->get_transform().x_rotation_angle -= 200 * ball->velocity.z * dt * decelerateVar;
        }
        if (ball->velocity.z < -stopVal)
        {
            ball->velocity.z -= ball->velocity.z * dt * decelerateVar;
            ball->get_transform().x_rotation_angle -= 200 * ball->velocity.z * dt * decelerateVar;
        }

        //stop
        if (ball->velocity.x <= stopVal && ball->velocity.x >= -stopVal)
        {
            ball->velocity.x = 0.0f;
            shouldbounceeoffx = false;
        }
        if (ball->velocity.z <= stopVal && ball->velocity.z >= -stopVal)
        {
            ball->velocity.z = 0.0f;
            shouldbounceeoffz = false;

        }

        //Don't let the ball to go into ground
        if (ball->get_transform().m_position.y<0.25f) ball->get_transform().m_position.y = 0.26f;


        //update position
        ball->update_transform();
        ball->collider.setPosition(ball->get_transform().m_position);

        //check for trigger in damagedwall
        if (ball->collider.boxToBoxCollisioncheck(damagedwall->trigger))
        {
            //change model (maybe it can be done better)
            Model destroyedwall("res/models/level/dziura_ogrodzenie_destroyed.obj"); 
            damagedwall->modelTemp = destroyedwall;
            //replace colliders
            wall->additionalColliders.at(2).setPosition(glm::vec3(11.7f, 0.0f, 21.0f)); //down
            wall->additionalColliders.at(3).setPosition(glm::vec3(21.5f, 0.0f, 15.4f)); //right
        }
    }
};

#endif