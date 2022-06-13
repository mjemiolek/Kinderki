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

float fullDisplayVertices[] = {
    // pozycje
    -1.0,  -1.0,
    1.00,  1.0,
    -1.0,  1.0,
    1.0,  -1.0
};

float timeVertices[] = {
    // pozycje
    0.95f,  0.30f,
    0.70f,  0.65f,
    0.95f,  0.65f,
    0.70f,  0.30f
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

float InsVertices[] = {
    // pozycje
    -0.70,  -0.5,
    -0.05,  0.1,
    -0.70,  0.1,
    -0.05,  -0.5
};

float candyVertices[] = {
    // pozycje
    0.80f,  0.65f,
    0.65f,  0.80f,
    0.80f,  0.80f,
    0.65f,  0.65f
};

float candyCountVertices[] = {
    // pozycje
    0.95f,  0.65f,
    0.80f,  0.80f,
    0.95f,  0.80f,
    0.80f,  0.65f
};



uint32_t indices[] = { 3, 1, 2,
                      2, 0, 3 };


float textureCords[] = { 0.0f, 1.0f,
                     1.0f, 0.0f,
                     0.0f, 0.0f,
                     1.0f, 1.0f };


class Gui {
public:
    unsigned int quadVAO, leftVAO, rightVAO, candyVAO, candyCountVAO, StoryVAO, InsVAO, TimeVAO;
    unsigned int quadVBO, leftVBO, rightVBO, candyVBO, candyCountVBO, StoryVBO, InsVBO, TimeVBO;
    unsigned int quadEBO;
    
    unsigned int texture;
    unsigned int textureLeft;
    unsigned int textureRight;

    unsigned int textureCandy;
    unsigned int textureCandyCount;

    unsigned int textureIns;

    unsigned int textureSeeSaw;
    unsigned int textureAerialRunway;
    unsigned int textureSwing;
    unsigned int textureTrampoline;
    unsigned int textureWallDestroy;
    unsigned int textureSandpit;
    unsigned int textureSlide;

    unsigned int textureFirst;
    unsigned int textureSecond;
    unsigned int textureThird;

    std::vector<unsigned int> Storylist = { textureFirst, textureSecond, textureThird};
    unsigned int textureStory;
    bool visibilityStory = false;
    bool storiesflag = true;
    int Storycounter = 0;
    unsigned int ct = 0;
    int lt = 0;
    int ucieczki = 0;

    bool visibility = false;
    bool visibilityPageOne = true;
    bool visibilityPageTwo = false;
    bool visibilityPageThree = false;
    bool visibilityPageFour = false;
    
    bool pressflag = false;
    bool pressflagPageOne = false;
    bool pressflagPageTwo = false;
    bool pressflagPageThree = false;
    bool pressflagPageFour = false;


    bool minchangeflag = false;
    bool colorchangeflag = false;
    bool changeday = false;
    Text textCzas;
    int czasmin = 2;
    int czassec = 0;
    int czastemp = 0;
    int czastemp2 = 0;
    std::ostringstream strsCzas;
    glm::vec3 czascolor = glm::vec3(0.7, 1.0f, 0.2f);
    unsigned int textureTime;


    Text text;
    Text text2;
    Text textCukierki;
    Text textUcieczki;

    std::ostringstream strs;
    std::ostringstream strs2;
    std::ostringstream strsCukierki;
    std::ostringstream strsUcieczki;

    Gui() {
        ////////////////////NoteBook Side
        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);
        
        glGenBuffers(1, &quadVBO);     //Zrobienie boxa notatnika
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(noteBookVertices), noteBookVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        
        glGenBuffers(1, &quadVBO);     //Wrzucenie tekstury notatnika
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        
        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);




        ////////////////////Left Side
        glGenVertexArrays(1, &leftVAO);
        glBindVertexArray(leftVAO);

        glGenBuffers(1, &leftVBO);     //Zrobienie boxa
        glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(leftPageVertices), leftPageVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &leftVBO);     //Wrzucenie tekstury
        glBindBuffer(GL_ARRAY_BUFFER, leftVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        

        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



        ////////////////////Right Side
        glGenVertexArrays(1, &rightVAO);
        glBindVertexArray(rightVAO);

        glGenBuffers(1, &rightVBO);
        glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(rightPageVertices), rightPageVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &rightVBO);
        glBindBuffer(GL_ARRAY_BUFFER, rightVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        ////////////////////Ins Side
        glGenVertexArrays(1, &InsVAO);
        glBindVertexArray(InsVAO);

        glGenBuffers(1, &InsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, InsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(InsVertices), InsVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &InsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, InsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


        glGenBuffers(1, &quadEBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        ////////////////////Candy Box
        glGenVertexArrays(1, &candyVAO);
        glBindVertexArray(candyVAO);

        glGenBuffers(1, &candyVBO);
        glBindBuffer(GL_ARRAY_BUFFER, candyVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(candyVertices), candyVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &candyVBO);
        glBindBuffer(GL_ARRAY_BUFFER, candyVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &candyVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        ////////////////////CandyCount square
        glGenVertexArrays(1, &candyCountVAO);
        glBindVertexArray(candyCountVAO);

        glGenBuffers(1, &candyCountVBO);
        glBindBuffer(GL_ARRAY_BUFFER, candyCountVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(candyCountVertices), candyCountVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &candyCountVBO);
        glBindBuffer(GL_ARRAY_BUFFER, candyCountVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &candyCountVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        ////////////////////Story square
        glGenVertexArrays(1, &StoryVAO);
        glBindVertexArray(StoryVAO);

        glGenBuffers(1, &StoryVBO);
        glBindBuffer(GL_ARRAY_BUFFER, StoryVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(fullDisplayVertices), fullDisplayVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &StoryVBO);
        glBindBuffer(GL_ARRAY_BUFFER, StoryVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &StoryVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        
        ////////////////////Time square
        glGenVertexArrays(1, &TimeVAO);
        glBindVertexArray(TimeVAO);

        glGenBuffers(1, &TimeVBO);
        glBindBuffer(GL_ARRAY_BUFFER, TimeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(timeVertices), timeVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &TimeVBO);
        glBindBuffer(GL_ARRAY_BUFFER, TimeVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCords), textureCords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

        glGenBuffers(1, &TimeVBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    }
	void render()
	{
        Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
        //Shader test2Shader("res/shaders/basic2.vert", "res/shaders/basic2.frag");
        //rendering image
        testShader.use();

        if (visibilityPageOne) {
            textureLeft = texture;
            textureRight = textureSandpit;


            Storylist.at(0) = textureAerialRunway;
            Storylist.at(1) = textureCandy;
            Storylist.at(2) = textureCandyCount;

        }
        if (visibilityPageTwo) {
            textureLeft = textureAerialRunway;
            textureRight = textureTrampoline;
        }
        if (visibilityPageThree) {
            textureLeft = textureWallDestroy;
            textureRight = textureSeeSaw;
        }
        if (visibilityPageFour) {
            textureLeft = textureSwing;
            textureRight = texture;
        }

        handleStories();


        if (visibilityPageOne || visibilityPageTwo || visibilityPageThree || visibilityPageFour) {
            glBindVertexArray(leftVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureLeft);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glBindVertexArray(rightVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureRight);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        if (visibilityPageOne) {
            glBindVertexArray(InsVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureIns);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        if (visibilityStory) {
            glBindVertexArray(StoryVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textureStory);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        if (visibilityPageOne || visibilityPageTwo || visibilityPageThree || visibilityPageFour) {
            glBindVertexArray(quadVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

        

        glBindVertexArray(candyVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureCandy);
        glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glBindVertexArray(candyCountVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureCandyCount);
        glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

       
        textCzas.RenderText(strsCzas.str(), 1725.0f, 770.0f, 0.69f, czascolor);
       
        testShader.use();

        glBindVertexArray(TimeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureTime);
        glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        

        //rendering text
        text.RenderText(strs.str(), 50.0f, 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        //text2.RenderText(strs2.str(), 50.0f, 100.0f, 1.0f, glm::vec3(0.9, 0.2f, 0.2f));


        textUcieczki.RenderText(strsUcieczki.str(), 75.0f, 950.0f, 1.0f, glm::vec3(0.9, 0.2f, 0.2f));
        text2.RenderText("/5", 100.0f, 950.0f, 1.0f, glm::vec3(0.9, 0.2f, 0.2f));

 
	}
   
    void update(double passed_time) {
        strs.str(std::string());
        strs << passed_time;
        strs2.str(std::string());
        strs2 << visibilityPageOne;
        strsCukierki.str(std::string());
        strsCukierki << visibilityPageOne;

        strsUcieczki.str(std::string());
        strsUcieczki << ucieczki;

        handleTimer();

        strsCzas.str(std::string());
        strsCzas << czasmin << ":" << czassec;

    }

    void handleTimer() {
        czassec = glfwGetTime();
        czassec = 59 - czassec % 60;
        
        if (!czassec && !minchangeflag) {
            minchangeflag = true;
            
        }
        if (czassec && minchangeflag) {
            minchangeflag = false; 
            czasmin--;
        }
        
        if (czasmin == 1 && !colorchangeflag)
        {
            czascolor = glm::vec3(0.3, 0.5f, 0.9f);
            colorchangeflag = true;
        }
        else if(!czasmin && czassec > 15 && colorchangeflag)
        {
            czascolor = glm::vec3(0.9, 0.8f, 0.25f);
            colorchangeflag = false;
        }
        else if (!czasmin && czassec < 15 && !colorchangeflag) {
            czascolor = glm::vec3(0.9, 0.0f, 0.25f);
            colorchangeflag = true;
        }
        if (czasmin == -1) {
            czasmin = 2;
            czascolor = glm::vec3(0.7, 1.0f, 0.2f);
            colorchangeflag = false;
            visibilityStory = true;
            changeday = true;
            czastemp = glfwGetTime();
        }
        if (visibilityStory && glfwGetTime() > czastemp + 5.0f) {
            changeday = false;
            visibilityStory = false;
        }
    }

    void handleStories() {
        if (visibilityStory) {
            if (storiesflag) {
                storiesflag = false;
                czastemp2 = glfwGetTime();
            }
            if (glfwGetTime() >= czastemp2 + 2) {
                ct++;
                storiesflag = true;
            }
            if (ct == 3) { ct = 0; }
            textureStory = Storylist.at(ct);
        }
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
            //printf("%s \n", "Page1 on");
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && visibilityPageOne && !pressflagPageOne) {
            visibilityPageOne = false;
            pressflagPageOne = true;
            //printf("%s \n", "Page1 off");
        }
        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE && pressflagPageOne) {
            pressflagPageOne = false;
                visibilityPageTwo = false;
                visibilityPageThree = false;
                visibilityPageFour = false;
        }


        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !visibilityPageTwo && !pressflagPageTwo) {
            visibilityPageTwo = true;
            pressflagPageTwo = true;
            //printf("%s \n", "Page2 on");
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && visibilityPageTwo && !pressflagPageTwo) {
            visibilityPageTwo = false;
            pressflagPageTwo = true;
            //printf("%s \n", "Page2 off");
        }
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE && pressflagPageTwo) {
            pressflagPageTwo = false;
                visibilityPageOne = false;
                visibilityPageThree = false;
                visibilityPageFour = false;
        }


        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !visibilityPageThree && !pressflagPageThree) {
            visibilityPageThree = true;
            pressflagPageThree = true;
            //printf("%s \n", "Page3 on");
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && visibilityPageThree && !pressflagPageThree) {
            visibilityPageThree = false;
            pressflagPageThree = true;
            //printf("%s \n", "Page3 off");
        }
        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_RELEASE && pressflagPageThree) {
            pressflagPageThree = false;
                visibilityPageOne = false;
                visibilityPageTwo = false;
                visibilityPageFour = false;
        }


        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && !visibilityPageFour && !pressflagPageFour) {
            visibilityPageFour = true;
            pressflagPageFour = true;
            //printf("%s \n", "Page4 on");
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && visibilityPageFour && !pressflagPageFour) {
            visibilityPageFour = false;
            pressflagPageFour = true;
            //printf("%s \n", "Page4 off");
        }
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_RELEASE && pressflagPageFour) {
            pressflagPageFour = false;
                visibilityPageOne = false;
                visibilityPageTwo = false;
                visibilityPageThree = false;
        }
        
        if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && !visibilityStory) {
            visibilityStory = true;
        }
        else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && visibilityStory) {
            visibilityStory = false;
        }
        if (ucieczki == 5) {
            visibilityStory = true;
        }
    }
};