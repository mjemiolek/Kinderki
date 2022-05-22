#ifndef MOVABLEMANAGER_H
#define MOVABLEMANAGER_H

#include "SceneGraph.h"

class MovableManager {
private:
    std::shared_ptr<SceneGraphNode> rootNode;
    std::shared_ptr<SceneGraphNode> playerObject;
    std::shared_ptr<SceneGraphNode> movable;
    glm::vec3 zeroPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 ofset2 = glm::vec3(0.0f, 0.0f, 0.0f);
    bool movableFlag = false;
    bool carringFlag = false;
public:
    MovableManager(std::shared_ptr<SceneGraphNode> root, std::shared_ptr<SceneGraphNode> movable, std::shared_ptr<SceneGraphNode> player) {
        this->movable = movable;
        playerObject = player;
        rootNode = root;
    }

    void calculateDir() {
             if (playerObject->m_transform.y_rotation_angle == 0.0f)   { ofset2 = glm::vec3(0.0f, -2.0f, -1.0f); }
        else if (playerObject->m_transform.y_rotation_angle == 45.0f)  { ofset2 = glm::vec3(0.5f, -2.0f, -0.75f); }
        else if (playerObject->m_transform.y_rotation_angle == 90.0f)  { ofset2 = glm::vec3(0.75f, -2.0f, -0.5f); }
        else if (playerObject->m_transform.y_rotation_angle == 135.0f) { ofset2 = glm::vec3(0.5f, -2.0f, -0.25f); }
        else if (playerObject->m_transform.y_rotation_angle == 180.0f) { ofset2 = glm::vec3(0.0f, -2.0f, 0.0f); }
        else if (playerObject->m_transform.y_rotation_angle == 225.0f) { ofset2 = glm::vec3(-0.5f, -2.0f, -0.25f); }
        else if (playerObject->m_transform.y_rotation_angle == 270.0f) { ofset2 = glm::vec3(-0.75f, -2.0f, -0.5f); }
        else if (playerObject->m_transform.y_rotation_angle == 315.0f) { ofset2 = glm::vec3(-0.5f, -2.0f, -0.75f); }
    }

    void manageMovable(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
            if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !carringFlag) {
                movableFlag = true;
                carringFlag = true;
                rootNode->detach_child(movable);
                //movable->m_transform.m_position = zeroPos;               
                movable->m_transform.m_position = playerObject->get_transform().m_position;
                movable->m_transform.y_rotation_angle += 180;
                playerObject->add_child(movable);
            }
        }

        
                if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
                    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !carringFlag && movableFlag) {
                        carringFlag = true;
                        movableFlag = false;
                        playerObject->detach_child(movable);
                        rootNode->add_child(movable);
                        movable->m_transform.m_position = playerObject->get_transform().m_position;
                        //movable->m_transform.y_rotation_angle += 180;
                    }
                }
                
                 if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE && carringFlag) {
                     carringFlag = false;
                 }

        movable->update_transform();
        //movable->collider.setPosition(movable->get_transform().m_position);
    }
    float retX() {
        return movable->m_transform.m_position.x;
    }

    float retZ() {
        return movable->m_transform.m_position.z;
    }
    
};

#endif