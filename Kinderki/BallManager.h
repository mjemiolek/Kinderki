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
    float kickpower = 9.6f;
    float decelerateVar = 0.69f;
    float stopVal = 0.25f;

    float lastvelocityx = 0.0;
    float lastvelocityz = 0.0;
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

            shouldbounceeoffx = true;
            shouldbounceeoffz = true;
        }

        if(ball->velocity.x){ lastvelocityx = ball->velocity.x; }
        if(ball->velocity.z){ lastvelocityz = ball->velocity.z; }

        //decelerate
        if (ball->velocity.x > stopVal)
        {
            ball->velocity.x -= ball->velocity.x * dt * decelerateVar;
        }
        if (ball->velocity.x < -stopVal)
        {
            ball->velocity.x -= ball->velocity.x * dt * decelerateVar;
        }
        ball->get_transform().z_rotation_angle += 200 * ball->velocity.x * dt * decelerateVar;


        if (ball->velocity.z > stopVal)
        {
            ball->velocity.z -= ball->velocity.z * dt * decelerateVar;
        }
        if (ball->velocity.z < -stopVal)
        {
            ball->velocity.z -= ball->velocity.z * dt * decelerateVar;
        }
        ball->get_transform().x_rotation_angle -= 200 * ball->velocity.z * dt * decelerateVar;

        


        if(ball->velocity.x < 0.5 && ball->velocity.x > -0.5 && shouldbounceeoffx){
            ball->velocity.x = 0.69*-lastvelocityx;
        }
        if (ball->velocity.z < 0.5 && ball->velocity.z > -0.5 && shouldbounceeoffz) {
            ball->velocity.z = 0.69*-lastvelocityz;
        }

        //off bouncing
        if (lastvelocityx > -1.5 && lastvelocityx < 1.5 && shouldbounceeoffx) {
            shouldbounceeoffx = false;
        }
        if (lastvelocityz > -1.5 && lastvelocityz < 1.5 && shouldbounceeoffz) {
            shouldbounceeoffz = false;
        }

       // std::cout << shouldbounceeoffx << "---"<< shouldbounceeoffz << std::endl
       //if (ball->velocity.x || ball->velocity.z) {    std::cout<< shouldbounceeoffx << "---"<< shouldbounceeoffz <<" +++ " << ball->velocity.x << "   " << lastvelocityx << std::endl; }

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
        if (ball->get_transform().m_position.y<0.25f) ball->get_transform().m_position.y = 0.26f;


        //update position
        ball->update_transform();
        ball->collider.setPosition(ball->get_transform().m_position);

        //check for trigger in damagedwall
        if (ball->collider.boxToBoxCollisioncheck(damagedwall->trigger))
        {
            //change model (maybe it can be done better)
            Model destroyedwall("res/models/level/dziura_ogrodzenie_destroyed.obj"); 
            unsigned int texfencedestroyed = loadTexture("res/textures/models/dziura_ogrodzenie_destroyed.png");
            damagedwall->modelTemp = destroyedwall;
            damagedwall->texture = texfencedestroyed;
            //replace colliders
            wall->additionalColliders.at(2).setPosition(glm::vec3(11.7f, 0.0f, 21.0f)); //down
            wall->additionalColliders.at(3).setPosition(glm::vec3(21.5f, 0.0f, 15.4f)); //right
        }
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
};

#endif