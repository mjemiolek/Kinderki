//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"
#pragma once

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <irrKlang/ik_ISound.h>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "SceneGraph.h"
#include "PlayerController.h"
#include "text.h"
#include "skybox.h"
#include "GameManager.h"

#include <mmcobj.h>


static void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void input(GLFWwindow* window);
//unsigned int loadTexture(char const* path);
//void update(float dt);
boolean checkForCollisions(PlayerController* player, std::shared_ptr<SceneGraphNode> objects[], std::shared_ptr<SceneGraphNode> cube);
//void render();
void render_gui();

GLFWwindow* window = nullptr;
std::ostringstream strs;

// settings
const GLuint SCR_WIDTH = 1280;
const GLuint SCR_HEIGHT = 720;

// camera
glm::vec3 cameraPos(0.0f, 16.0f, 5.0f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);





float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

float quadVertices[] = {
    // pozycje       // kolory
    0.95f,  0.60f,
    0.60f, 0.95f,
    0.95f, 0.95f,
    0.60f,  0.60f
};

float textCords[] = { 0.0f, 1.0f,
                     1.0f, 0.0f,
                     0.0f, 0.0f,
                     1.0f, 1.0f };

uint32_t indices[] = { 3, 1, 2,
                      2, 0, 3 };

float normals[] = { 0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f,
                   0.0f, 1.0f, 0.0f };

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

float color[] = {
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f
};


GLint u_scale_loc = -1;
GLint u_world_loc = -1;
GLint u_scale_loc2 = -1;
float scale = 1.0f;



//time
double last_time = glfwGetTime();
double unprocessed_time = 0.0;
double current_time = 0.0;
double passed_time = 0.0;
bool should_render = false;
double frame_time = 1.0 / 60.0;



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
//    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile shaders
    // -------------------------

    Shader textShader("res/shaders/text.vert", "res/shaders/text.frag");
    Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
    Shader test2Shader("res/shaders/basic2.vert", "res/shaders/basic2.frag");
    Shader skyboxShader("res/shaders/skybox.vert", "res/shaders/skybox.frag");

    
    unsigned int quadVAO, quadVBO1, quadVBO2, quadVBO3, quadEBO;

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


    unsigned int progressVAO, progressVBO1, progressVBO2, progressEBO;

    glGenVertexArrays(1, &progressVAO);
    glBindVertexArray(progressVAO);

    glGenBuffers(1, &progressVBO1);
    glBindBuffer(GL_ARRAY_BUFFER, progressVBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bar), &bar, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    

    // shader configuration
    // --------------------

    

    // load models
    // -----------
    

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //root_node = std::make_shared<SceneGraphNode>();
    //cube1 = std::make_shared<SceneGraphNode>();
    //cube2 = std::make_shared<SceneGraphNode>();
    //cube3 = std::make_shared<SceneGraphNode>();
    //test1 = std::make_shared<SceneGraphNode>();
    //modelTest = std::make_shared<SceneGraphNode>();
    //floorTest = std::make_shared<SceneGraphNode>();
    //meshesTest = std::make_shared<SceneGraphNode>();
    //sandsTest = std::make_shared<SceneGraphNode>();


    
    GameManager gameManager;
    gameManager.init();

    Skybox skybox;
    Text text(textShader);
    PlayerController* player = new PlayerController();
    unsigned int texture = gameManager.loadTexture("res/textures/stone.jpg");


    skyboxShader.use();
    glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

    while (!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        passed_time = current_time - last_time;
        last_time = current_time;
        unprocessed_time += passed_time;

        input(window);
        if (!checkForCollisions(player, gameManager.collidingObjects, gameManager.cube3)) {
            player->move(window, &gameManager.cube3->get_transform().m_position, passed_time);

        }

        



        while (unprocessed_time >= frame_time) {
            should_render = true;
            unprocessed_time -= frame_time;
            gameManager.update(frame_time);
        }


        if (should_render) {
            should_render = false;
            
            gameManager.render();
            testShader.use();
            glBindVertexArray(quadVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glDrawElements(GL_TRIANGLES, GLsizei(std::size(indices)), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glBindBuffer(GL_ARRAY_BUFFER, progressVBO1);
            glBufferData(GL_ARRAY_BUFFER, sizeof(bar), &bar, GL_STATIC_DRAW);

            test2Shader.use();
            glBindVertexArray(progressVAO);
            glDrawArrays(GL_TRIANGLES, 0, 18);
            glBindVertexArray(0);

            skybox.render(skyboxShader);
            strs.str(std::string());
            strs << passed_time;
            text.RenderText(textShader, strs.str(), 50.0f, 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

            render_gui();
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
void input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    
        //Player+Camera                                OnlyCamera
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, passed_time);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, passed_time);
    //if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    //    cube2->get_transform().x_rotation_angle += 6.0f * passed_time;
    //if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    //    cube2->get_transform().z_rotation_angle += 9.0f * passed_time;
    //if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    //    camera.Position.x = cube3->get_transform().m_position.x + cameraPos.x;  //attach camera to player
    //    camera.Position.z = cube3->get_transform().m_position.z + cameraPos.z;  //attach camera to player
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



boolean checkForCollisions(PlayerController* player, std::shared_ptr<SceneGraphNode> objects[], std::shared_ptr<SceneGraphNode> cube) {
    glm::vec3 play = cube->get_transform().m_position;  //change it to player
    for (int i = 0; i < 3; i++) //change "3" to "number of objects in array"
    {
        glm::vec3 p = objects[i]->get_transform().m_position;
        float distance = sqrt((p.x - play.x) * (p.x - play.x) + (p.y - play.y) * (p.y - play.y) + (p.z - play.z) * (p.z - play.z));
        if (distance <= 1.5f)
        {
            //push player outside
            glm::vec3 direction(play.x - p.x, play.y - p.y, play.z - p.z);
            cube->get_transform().m_position.x += direction.x * 2.5f * passed_time;
            cube->get_transform().m_position.y += direction.y * 2.5f * passed_time;
            cube->get_transform().m_position.z += direction.z * 2.5f * passed_time;

            camera.Position.x = cube->get_transform().m_position.x + cameraPos.x;  //attach camera to player
            camera.Position.z = cube->get_transform().m_position.z + cameraPos.z;  //attach camera to player
            return true;
        }
    }
    return false;
}





void render_gui() {
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();

    //ImGui::Render();
    //int display_w, display_h;
    //glfwGetFramebufferSize(window, &display_w, &display_h);
    //glViewport(0, 0, display_w, display_h);
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}