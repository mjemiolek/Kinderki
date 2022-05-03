#pragma once
#include <GLFW/glfw3.h>
#include "Text.h"

unsigned int loadTexture(char const* path);

float quadVertices[] = {
    // pozycje       // kolory
    0.95f,  0.60f,
    0.60f,  0.95f,
    0.95f,  0.95f,
    0.60f,  0.60f
};

float noteBookVertices[] = {
    // pozycje
    0.80f,  -0.80f,
    -0.80f,  0.80f,
    0.80f,  0.80f,
    -0.80f,  -0.80f
};

float leftPageVertices[] = {
    // pozycje
    -0.20,  0.2,
    -0.60,  0.70,
    -0.20,  0.70,
    -0.60,  0.2,
};
float rightPageVertices[] = {
    // pozycje
    0.20,  0.2,
    0.60,  0.70,
    0.20,  0.70,
    0.60,  0.2
};


uint32_t indices[] = { 3, 1, 2,
                      2, 0, 3 };

float x = -0.90f;

float bar[] = {
    // pozycje       // kolory
    -0.95f,  -0.95f,
    -0.95f, -0.90f,
    x, -0.90f,
    x, -0.90f,
    x,  -0.95f,
    -0.95f,  -0.95f
};


float textureCords[] = { 0.0f, 1.0f,
                     1.0f, 0.0f,
                     0.0f, 0.0f,
                     1.0f, 1.0f };


class Gui {
public:
    unsigned int quadVAO, leftVAO, rightVAO;
    unsigned int quadVBO1, quadVBO2, quadVBO3, quadEBO;
    unsigned int progressVAO, progressVBO1, progressVBO2, progressEBO;
    unsigned int texture;
    unsigned int textureSeeSaw;
    unsigned int textureAerialRunway;
   
    bool visibility = false;
    bool visibilityPageOne = false;
    
    bool pressflag = false;
    bool pressflagPageOne = false;
    
    
    Text text;
    Text text2;
    std::ostringstream strs;
    std::ostringstream strs2;
    Gui() {
        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);
        
        glGenBuffers(1, &quadVBO1);     //Zrobienie boxa notatnika
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(noteBookVertices), noteBookVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        
        glGenBuffers(1, &quadVBO1);     //Wrzucenie tekstury notatnika
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        
        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        glGenVertexArrays(1, &leftVAO);
        glBindVertexArray(leftVAO);

        glGenBuffers(1, &quadVBO2);     //Zrobienie boxa
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(leftPageVertices), leftPageVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &quadVBO2);     //Wrzucenie tekstury
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO2);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        

        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &rightVAO);
        glBindVertexArray(rightVAO);

        glGenBuffers(1, &quadVBO3);     //Zrobienie boxa
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO3);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rightPageVertices), rightPageVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &quadVBO3);     //Wrzucenie tekstury
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO3);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        
        /*
        glGenVertexArrays(1, &progressVAO);
        glBindVertexArray(progressVAO);

        glGenBuffers(1, &progressVBO1);
        glBindBuffer(GL_ARRAY_BUFFER, progressVBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bar), &bar, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        */
    }
	void render()
	{
        Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
        Shader test2Shader("res/shaders/basic2.vert", "res/shaders/basic2.frag");
        //rendering image
        testShader.use();

        if (visibilityPageOne) {
            glBindVertexArray(leftVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureSeeSaw);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glBindVertexArray(rightVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureAerialRunway);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        if (visibilityPageOne) {
            glBindVertexArray(quadVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
       

        //rendering progressbar

        /*
        test2Shader.use();
        glBindBuffer(GL_ARRAY_BUFFER, progressVBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bar), &bar, GL_DYNAMIC_DRAW);

        glBindVertexArray(progressVAO);
        glDrawArrays(GL_TRIANGLES, 0, 18);
        glBindVertexArray(0);
        */

        //rendering text
        text.RenderText(strs.str(), 50.0f, 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        text.RenderText(strs2.str(), 50.0f, 75.0f, 1.0f, glm::vec3(0.9, 0.2f, 0.2f));
	}
   
    void update(double passed_time) {
        strs.str(std::string());
        strs << passed_time;
        strs2.str(std::string());
        strs2 << visibilityPageOne;
    }

    void handleGui(GLFWwindow* window) {
       
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && !visibility && !pressflag) {
            visibility = true;
            pressflag = true;
            printf("%s \n", "notebook on");
        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && visibility && !pressflag) {
            visibility = false;
            pressflag = true;
            printf("%s \n", "notebook off");
        }
        if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE && pressflag) {
            pressflag = false;
        }
        
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !visibilityPageOne && !pressflagPageOne) {
            visibilityPageOne = true;
            pressflagPageOne = true;
            printf("%s \n", "seesaw on");
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && visibilityPageOne && !pressflagPageOne) {
            visibilityPageOne = false;
            pressflagPageOne = true;
            printf("%s \n", "seesaw off");
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE && pressflagPageOne) {
            pressflagPageOne = false;
        }

    
    }

    /*
    void update(double passed_time)
    {
    if (x < -0.50f) {
        x = x + 0.01f;
        bar[4] = x;
        bar[6] = x;
        bar[8] = x;
        strs.str(std::string());
        strs << passed_time;
    }
    else {
        x = -0.90f;
    }
    }
    */
};