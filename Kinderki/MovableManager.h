#ifndef MOVABLEMANAGER_H
#define MOVABLEMANAGER_H

#include "SceneGraph.h"

class MovableManager {
private:
    std::shared_ptr<SceneGraphNode> rootNode;
    std::shared_ptr<SceneGraphNode> playerObject;
    //std::shared_ptr<SceneGraphNode> movable;
    std::vector<std::shared_ptr<SceneGraphNode>> vecMovable;
    glm::vec3 zeroPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 ofset1 = glm::vec3(0.0f, 0.0f, -0.5f);
    glm::vec3 ofset2 = glm::vec3(0.0f, 0.0f, -0.5f);
    bool carringFlag = false;
    bool overlapFlag = false;
    int iterator = 0;
public:
    MovableManager(std::shared_ptr<SceneGraphNode> root, std::shared_ptr<SceneGraphNode> player) {
        playerObject = player;
        rootNode = root;
    }

    void calculateDir() {
        if (playerObject->m_transform.y_rotation_angle == 0.0f) { ofset2 = glm::vec3(0.0f, 0.0f, -0.5f);}
        else if (playerObject->m_transform.y_rotation_angle == 45.0f)  { ofset2 = glm::vec3(0.33f, 0.0f, -0.33f);}
        else if (playerObject->m_transform.y_rotation_angle == 90.0f)  { ofset2 = glm::vec3(0.5f, 0.0f, 0.0f);}
        else if (playerObject->m_transform.y_rotation_angle == 135.0f) { ofset2 = glm::vec3(0.33f, 0.0f, 0.33f);}
        else if (playerObject->m_transform.y_rotation_angle == 180.0f) { ofset2 = glm::vec3(0.0f, 0.0f, 0.5f);}
        else if (playerObject->m_transform.y_rotation_angle == 225.0f) { ofset2 = glm::vec3(-0.33f, 0.0f, 0.33f);}
        else if (playerObject->m_transform.y_rotation_angle == 270.0f) { ofset2 = glm::vec3(-0.5f, 0.0f, 0.0f);}
        else if (playerObject->m_transform.y_rotation_angle == 315.0f) { ofset2 = glm::vec3(-0.33f, 0.0f, -0.33f);}
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
                        //movableFlag = false;
                        playerObject->detach_child(vecMovable[iterator]);
                        rootNode->add_child(vecMovable[iterator]);
                        calculateDir();
                        vecMovable[iterator]->m_transform.y_rotation_angle += playerObject->m_transform.y_rotation_angle;
                        vecMovable[iterator]->get_transform().m_scale *= playerObject->get_transform().m_scale;

                        vecMovable[iterator]->m_transform.m_position = playerObject->get_transform().m_position+ ofset2;

                    }
                }
                
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
                if (playerObject->collider.boxToBoxCollisioncheck(vecMovable[i]->trigger)) {
                    
                        overlapFlag = true;
                        carringFlag = true;
                        iterator = i;
                        rootNode->detach_child(vecMovable[i]);

                        vecMovable[i]->m_transform.m_position = zeroPos;
                        vecMovable[i]->get_transform().m_scale *= 1 / playerObject->get_transform().m_scale;

                        playerObject->add_child(vecMovable[i]);
                        calculateDir();
                        vecMovable[i]->m_transform.m_position += ofset1;

                }
            }
        }
    }

    float retX(int i) {
        return vecMovable[i]->m_transform.m_position.x;
    }

    float retZ(int i) {
        return vecMovable[i]->m_transform.m_position.z;
    }
    
};

#endif