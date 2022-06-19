#ifndef MOVABLEMANAGER_H
#define MOVABLEMANAGER_H

#include "PlayerController.h"

class MovableManager {
private:
    std::shared_ptr<SceneGraphNode> rootNode;
    std::shared_ptr<PlayerController> playerObject;
    //std::shared_ptr<SceneGraphNode> movable;
    std::vector<std::shared_ptr<SceneGraphNode>> vecMovable;
    glm::vec3 zeroPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 ofset1 = glm::vec3(0.0f, 0.0f, -0.5f);
    glm::vec3 ofset2 = glm::vec3(0.0f, 0.0f, -0.5f);
    bool carringFlag = false;
    bool mentosColaInteracted = false;
    int iterator = 0;
public:
    MovableManager(std::shared_ptr<SceneGraphNode> root, std::shared_ptr<PlayerController> player) {
        playerObject = player;
        rootNode = root;
    }

    void calculateDir() {
        if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 0.0f) { ofset2 = glm::vec3(0.0f, 0.0f, -0.5f);}
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 45.0f)  { ofset2 = glm::vec3(0.33f, 0.0f, -0.33f);}
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 90.0f)  { ofset2 = glm::vec3(0.5f, 0.0f, 0.0f);}
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 135.0f) { ofset2 = glm::vec3(0.33f, 0.0f, 0.33f);}
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 180.0f) { ofset2 = glm::vec3(0.0f, 0.0f, 0.5f);}
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 225.0f) { ofset2 = glm::vec3(-0.33f, 0.0f, 0.33f);}
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 270.0f) { ofset2 = glm::vec3(-0.5f, 0.0f, 0.0f);}
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle == 315.0f) { ofset2 = glm::vec3(-0.33f, 0.0f, -0.33f);}
    }

    //Little bit more smooth 
    void calculateDir2() {
        if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 0.0f && playerObject->getPlayerObject()->m_transform.y_rotation_angle < 45.0f) { ofset2 = glm::vec3(0.0f, 0.0f, -0.5f); }
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 45.0f && playerObject->getPlayerObject()->m_transform.y_rotation_angle < 90.0f) { ofset2 = glm::vec3(0.33f, 0.0f, -0.33f); }
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 90.0f && playerObject->getPlayerObject()->m_transform.y_rotation_angle < 135.0f) { ofset2 = glm::vec3(0.5f, 0.0f, 0.0f); }
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 135.0f && playerObject->getPlayerObject()->m_transform.y_rotation_angle < 180.0f) { ofset2 = glm::vec3(0.33f, 0.0f, 0.33f); }
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 180.0f && playerObject->getPlayerObject()->m_transform.y_rotation_angle < 225.0f) { ofset2 = glm::vec3(0.0f, 0.0f, 0.5f); }
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 225.0f && playerObject->getPlayerObject()->m_transform.y_rotation_angle < 270.0f) { ofset2 = glm::vec3(-0.33f, 0.0f, 0.33f); }
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 270.0f && playerObject->getPlayerObject()->m_transform.y_rotation_angle < 315.0f) { ofset2 = glm::vec3(-0.5f, 0.0f, 0.0f); }
        else if (playerObject->getPlayerObject()->m_transform.y_rotation_angle >= 315.0f) { ofset2 = glm::vec3(-0.33f, 0.0f, -0.33f); }
    }

    void manageMovable(GLFWwindow* window)
    {
        /*
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !carringFlag && !movableFlag) {
                    movableFlag = true;
                    carringFlag = true;
                    rootNode->detach_child(vecMovable[0]);
                    vecMovable[0]->m_transform.m_position = zeroPos;
                    //movable->m_transform.m_position = playerObject->get_transform().m_position;
                    //movable->m_transform.y_rotation_angle += 180;
                    playerObject->add_child(vecMovable[0]);
                    calculateDir();
                    vecMovable[0]->m_transform.m_position += ofset1;
                   // movable->m_transform.y_rotation_angle -= playerObject->m_transform.y_rotation_angle;


            }
        }
        */

        interact(vecMovable);

        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && carringFlag) {
                carringFlag = false;
                playerObject->setTempCheckCarry(false);
                //movableFlag = false;
                playerObject->getPlayerObject()->detach_child(vecMovable[iterator]);
                rootNode->add_child(vecMovable[iterator]);
                calculateDir2();
                vecMovable[iterator]->m_transform.y_rotation_angle += playerObject->getPlayerObject()->m_transform.y_rotation_angle;
                vecMovable[iterator]->get_transform().m_scale *= playerObject->getPlayerObject()->get_transform().m_scale;

                vecMovable[iterator]->m_transform.m_position = playerObject->getPlayerObject()->get_transform().m_position + ofset2;

            }
        }
        if (mentosColaInteracted == false) { mentosColaCheck(); }
        


        //if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE && carringFlag) {
        //    carringFlag = false;
        //}
                
        vecMovable[iterator]->update_transform();
        vecMovable[iterator]->trigger.setPosition(vecMovable[iterator]->get_transform().m_position);
    }

    void addMovable(std::shared_ptr<SceneGraphNode> movable) {
        vecMovable.push_back(movable);
    }

    bool delMovable(std::shared_ptr<SceneGraphNode> movable) {

        for (int i = 0; i < vecMovable.size(); i++) {
            if (vecMovable[i] == movable) {
                vecMovable[i] = nullptr;
                vecMovable.erase(vecMovable.begin() + i);
                return true;
            }
        }
        return false;
    }

    void interact(std::vector<std::shared_ptr<SceneGraphNode>> vecMovable) {
        if (!carringFlag) {
            for (int i = 0; i < vecMovable.size(); i++) {
                if (playerObject->getPlayerObject()->collider.boxToBoxCollisioncheck(vecMovable[i]->trigger)) {
                    if (playerObject->getPlayerObject()->m_children.size() == 0) {
                        carringFlag = true;
                        playerObject->setTempCheckCarry(true);
                        iterator = i;
                        rootNode->detach_child(vecMovable[i]);

                        vecMovable[i]->m_transform.m_position = zeroPos;
                        //std::cout << " 1. x: " << vecMovable[i]->m_transform.m_position.x << " y: " << vecMovable[i]->m_transform.m_position.y << " z: " << vecMovable[i]->m_transform.m_position.z << std::endl;

                        vecMovable[i]->get_transform().m_scale *= 1 / playerObject->getPlayerObject()->get_transform().m_scale;

                        //std::cout << " 2. x: " << vecMovable[i]->m_transform.m_position.x << " y: " << vecMovable[i]->m_transform.m_position.y << " z: " << vecMovable[i]->m_transform.m_position.z << std::endl;

                        playerObject->getPlayerObject()->add_child(vecMovable[i]);
                        calculateDir();
                        vecMovable[i]->m_transform.m_position += ofset1 * (1 / playerObject->getPlayerObject()->get_transform().m_scale);
                        //std::cout << " 3. x: " << vecMovable[i]->m_transform.m_position.x << " y: " << vecMovable[i]->m_transform.m_position.y << " z: " << vecMovable[i]->m_transform.m_position.z << std::endl;
                    }
                        
                }
            }
        }
    }

    

    //void manageMovable2(GLFWwindow* window)
    //{
    //    //check for interaction
    //    interact2(vecMovable);
    //    calculateDir2();
    //    //apply new position to carried object
    //    if (carringFlag)
    //    {
    //        vecMovable[iterator]->m_transform.y_rotation_angle = playerObject->getPlayerObject()->m_transform.y_rotation_angle; //apply rotation
    //        vecMovable[iterator]->m_transform.m_position = playerObject->getPlayerObject()->get_transform().m_position + ofset2; //new position
    //    }
    //    mentosColaCheck();
    //    //Drop Item on M
    //    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && carringFlag)
    //    {
    //        carringFlag = false;
    //        vecMovable[iterator]->m_transform.y_rotation_angle += playerObject->getPlayerObject()->m_transform.y_rotation_angle;
    //        vecMovable[iterator]->m_transform.m_position = playerObject->getPlayerObject()->get_transform().m_position + ofset2;
    //    }

    //    vecMovable[iterator]->update_transform();
    //    vecMovable[iterator]->trigger.setPosition(vecMovable[iterator]->get_transform().m_position);
    //}



    ////check for interaction and mark movable object with iterator
    //void interact2(std::vector<std::shared_ptr<SceneGraphNode>> vecMovable) {
    //    if (!carringFlag) {
    //        for (int i = 0; i < vecMovable.size(); i++) {
    //            if (!carringFlag) {
    //                if (playerObject->getPlayerObject()->collider.boxToBoxCollisioncheck(vecMovable[i]->trigger)) {
    //                    carringFlag = true;
    //                    iterator = i;
    //                }
    //            }
    //        }
    //    }
    //}

    void mentosColaCheck()
    {
        //[2]-cola [3]-mentos
        if (vecMovable[2]->trigger.boxToBoxCollisioncheck(vecMovable[3]->trigger))
        {
            mentosColaInteracted = true;
           // carringFlag = false;
            Model nothing("res/models/movable/nothing.obj");
            //Hide mentos and attach it to cola
            vecMovable[3]->modelTemp = nothing;
            vecMovable[3]->m_transform.m_position = glm::vec3(-500.0f, -2.0f, 0.0f);

            //change cola model
            Model puffedCola("res/models/movable/puffed_cola.obj");
            unsigned int texcola = loadTexture("res/textures/models/texcola.png");
            vecMovable[2]->texture = texcola;
            vecMovable[2]->modelTemp = puffedCola;
            vecMovable[2]->m_transform.m_scale = 1.2f;
            vecMovable[2]->modelOutline = nothing;
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