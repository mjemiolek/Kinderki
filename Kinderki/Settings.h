#pragma once
#include <GLFW/glfw3.h>

extern const GLuint SCR_WIDTH = 1920;
extern const GLuint SCR_HEIGHT = 1080;
extern const unsigned int shadowMapWidth = 10*2560, shadowMapHeight = 10*1440;
Camera camera(glm::vec3(0.0f, 16.0f, 5.0f));