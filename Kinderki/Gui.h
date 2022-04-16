#pragma once
#include "Text.h"

float quadVertices[] = {
    // pozycje       // kolory
    0.95f,  0.60f,
    0.60f, 0.95f,
    0.95f, 0.95f,
    0.60f,  0.60f
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


float textCords[] = { 0.0f, 1.0f,
                     1.0f, 0.0f,
                     0.0f, 0.0f,
                     1.0f, 1.0f };


class Gui {
public:
    unsigned int quadVAO, quadVBO1, quadVBO2, quadVBO3, quadEBO;
    unsigned int progressVAO, progressVBO1, progressVBO2, progressEBO;
    unsigned int texture;
    Text text;
    std::ostringstream strs;
    Gui() {
        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);

        glGenBuffers(1, &quadVBO1);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


        glGenBuffers(1, &quadVBO3);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO3);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textCords), textCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenVertexArrays(1, &progressVAO);
        glBindVertexArray(progressVAO);

        glGenBuffers(1, &progressVBO1);
        glBindBuffer(GL_ARRAY_BUFFER, progressVBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bar), &bar, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    }
	void render()
	{
        Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
        Shader test2Shader("res/shaders/basic2.vert", "res/shaders/basic2.frag");
        //rendering image
        testShader.use();
        glBindVertexArray(quadVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        //rendering progressbar
        test2Shader.use();
        glBindBuffer(GL_ARRAY_BUFFER, progressVBO1);
        glBufferData(GL_ARRAY_BUFFER, sizeof(bar), &bar, GL_STATIC_DRAW);

        glBindVertexArray(progressVAO);
        glDrawArrays(GL_TRIANGLES, 0, 18);
        glBindVertexArray(0);
        //rendering text
        text.RenderText(strs.str(), 50.0f, 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
	}
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
};