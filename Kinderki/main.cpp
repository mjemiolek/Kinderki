//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <irrKlang/ik_ISound.h>

#include "Sound.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "SceneGraph.h"
#include "PlayerController.h"
#include "AIController.h"
#include "Skybox.h"
#include "GameManager.h"
#include "ColliderManager.h"
#include "Gui.h"
#include "Settings.h"
#include "GravityManager.h"

#include <mmcobj.h>


static void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void input(GLFWwindow* window, std::shared_ptr<SceneGraphNode> player);
//unsigned int loadTexture(char const* path);
//void update(float dt);
//boolean checkForCollisions(PlayerController* player, std::vector<std::shared_ptr<SceneGraphNode>> objects, std::shared_ptr<SceneGraphNode> cube);
//void render();
void render_gui();

GLFWwindow* window = nullptr;
//light
glm::vec3 lightPosition(5.0f, 35.0f, -30.0f);
// camera
glm::vec3 cameraPos(0.0f, 16.0f, 5.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


//time
double last_time = glfwGetTime();
double unprocessed_time = 0.0;
double current_time = 0.0;
double passed_time = 0.0;
bool should_render = false;
double frame_time = 1.0 / 60.0;

bool temp = true;



int main()
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return 1;

    // GL 4.3 + GLSL 430
    const char* glsl_version = "#version 430";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

    // Create window with graphics context
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Dear ImGui GLFW+OpenGL3 example", NULL, NULL);
    if (window == NULL)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSwapInterval(1); // Enable vsync

//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    bool err = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (err) {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    // stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Creating game components
    GameManager gameManager;
    ColliderManager colManager(gameManager.collidingObjects);
    Gui gui;
    Skybox skybox;
    PlayerController* player = new PlayerController(gameManager.cube3);
    AIController* AI = new AIController(gameManager.cube2);

    //load texture to gui
    unsigned int texture = gameManager.loadTexture("res/textures/notebook.png");
    unsigned int textureSeeSaw = gameManager.loadTexture("res/textures/icons/Iseesaw.png");
    unsigned int textureAerialRunway = gameManager.loadTexture("res/textures/icons/Iaerialrunway.png");
    unsigned int textureSwing = gameManager.loadTexture("res/textures/icons/Iswing.png");
    unsigned int textureTrampoline = gameManager.loadTexture("res/textures/icons/Itrampoline.png");
    unsigned int textureWallDestroy = gameManager.loadTexture("res/textures/icons/Iwallbang.png");
    unsigned int textureSandpit = gameManager.loadTexture("res/textures/icons/sandpit.png");
    unsigned int textureSlide = gameManager.loadTexture("res/textures/icons/slide.png");
    
    unsigned int textureCandy = gameManager.loadTexture("res/textures/candy.png");
    unsigned int textureCandyx0 = gameManager.loadTexture("res/textures/candyx0.png");
    unsigned int textureCandyx1 = gameManager.loadTexture("res/textures/candyx1.png");
    unsigned int textureCandyx2 = gameManager.loadTexture("res/textures/candyx2.png");
    unsigned int textureCandyx3 = gameManager.loadTexture("res/textures/candyx3.png");
    unsigned int textureCandyx4 = gameManager.loadTexture("res/textures/candyx4.png");
    unsigned int textureCandyx5 = gameManager.loadTexture("res/textures/candyx5.png");
    unsigned int textureCandyx6 = gameManager.loadTexture("res/textures/candyx6.png");

    gui.texture = texture;
    gui.textureSeeSaw = textureSeeSaw;
    gui.textureAerialRunway = textureAerialRunway;
    gui.textureSwing = textureSwing;
    gui.textureTrampoline = textureTrampoline;
    gui.textureWallDestroy = textureWallDestroy;
    gui.textureSandpit = textureSandpit;
    gui.textureSlide = textureSlide;

    gui.textureCandy = textureCandy;
    


    

    Sound sound("res/sounds/CasualGameSounds/ziuuum.wav");
    sound.play();



    
    while (!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        passed_time = current_time - last_time;
        last_time = current_time;
        unprocessed_time += passed_time;

        input(window, gameManager.cube3);
        AI->move(window, passed_time);
        player->move(window, passed_time);
        player->interact(window, gameManager.sandpitptr,passed_time);
        gui.textureCandyCount = gameManager.candyCount(player, textureCandyx0, textureCandyx1, textureCandyx2, textureCandyx3, textureCandyx4, textureCandyx5, textureCandyx6);
        colManager.manageCollisions(passed_time);
        gui.handleGui(window);

        //robocza modyfikacja candyCount
        if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
            player->setCandyCount(player->getCandyCount() - 1);
         
        //robocza modyfikacja candyCount
        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) 
            player->setCandyCount(player->getCandyCount() + 1);
            
        


        while (unprocessed_time >= frame_time) {
            should_render = true;
            unprocessed_time -= frame_time;
            gameManager.update(frame_time);
            gui.update(passed_time);
        }


        if (should_render) {
            should_render = false;
           
            //gameManager.render();
            gameManager.renderwithShadows();
            gameManager.renderWithOutline();
            skybox.render();
            gui.render();

            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }
    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    
    //glDeleteVertexArrays(1, &cubeVAO);
    //glDeleteVertexArrays(1, &quadVAO);
    //glDeleteBuffers(1, &VBO);
    delete player;


        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}



static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void input(GLFWwindow* window, std::shared_ptr<SceneGraphNode> player) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
        //Player+Camera                                OnlyCamera
    //if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    //    camera.ProcessKeyboard(FORWARD, passed_time);
    //if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    //    camera.ProcessKeyboard(BACKWARD, passed_time);
    //if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    //    camera.ProcessKeyboard(LEFT, passed_time);
    //if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    //    camera.ProcessKeyboard(RIGHT, passed_time);
    //if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    //    cube2->get_transform().x_rotation_angle += 6.0f * passed_time;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    //    cube2->get_transform().z_rotation_angle += 9.0f * passed_time;
    //if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.Position.x = player->get_transform().m_position.x + cameraPos.x;  //attach camera to player
        camera.Position.z = player->get_transform().m_position.z + cameraPos.z;  //attach camera to player
        camera.Position.y = player->get_transform().m_position.y + cameraPos.y;  //attach camera to player
        lightPos.x = player->get_transform().m_position.x + lightPosition.x;     //attach light to player
        lightPos.y = player->get_transform().m_position.y + lightPosition.y;     //attach light to player
        lightPos.z = player->get_transform().m_position.z + lightPosition.z;     //attach light to player

    //}
        //camera.Position = cube3->get_transform().m_position + cameraPos;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
