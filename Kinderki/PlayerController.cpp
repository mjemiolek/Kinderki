#include "PlayerController.h"

PlayerController::PlayerController(glm::vec3 PlayerPosition)
{
	this->PlayerPosition;
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

void PlayerController::move(GLFWwindow* window, glm::vec3& Cube1Position)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        Cube1Position.z -= 0.005f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        Cube1Position.z += 0.005f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        Cube1Position.x -= 0.005f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        Cube1Position.x += 0.005f;
};



