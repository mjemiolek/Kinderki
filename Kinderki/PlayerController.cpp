#define PLAYERCONTROLLER_H_IMPLEMENTATION
#include "PlayerController.h"

PlayerController::PlayerController()
{
	
}

PlayerController::~PlayerController()
{
}

glm::vec3 PlayerController::getPlayerPosition()
{
	return PlayerPosition;
}

void PlayerController::setPlayerPosition(glm::vec3 position)
{
	PlayerPosition = position;
}

void PlayerController::move(GLFWwindow* window, glm::vec3* Cube1Position, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        Cube1Position->z -= 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        Cube1Position->z += 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        Cube1Position->x -= 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        Cube1Position->x += 2.5f * deltaTime;
    setPlayerPosition(*Cube1Position);

};



