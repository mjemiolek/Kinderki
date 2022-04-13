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

#include <mmcobj.h>


static void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void input(GLFWwindow* window);
unsigned int loadTexture(char const* path);
void update(float dt);
void checkForCollisions(PlayerController* player, std::shared_ptr<SceneGraphNode> objects[]);
void render();
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
glm::vec3 zeroPos(0.0f, 0.0f, 0.0f);
glm::vec3 floorPos(0.0f, -1.75f, 0.0f);


glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 2.0f,  3.5f),
        glm::vec3(2.0f,  2.0f, -15.0f),
        glm::vec3(0.5f, 2.0f, -1.5f),
        glm::vec3(-3.8f, 2.0f, -12.3f),
        glm::vec3(0.0f, 2.0f,  0.0f),
        glm::vec3(0.0f,  2.0f, 0.0f),
        glm::vec3(1.3f, 2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -1.5f),
        glm::vec3(-1.3f,  2.0f, -1.5f)
};

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
unsigned int cubeVAO = 0;
unsigned int VBO = 0;
//unsigned int quadVAO = 0;
unsigned int progressVBO1 = 0;
unsigned int quadVAO, quadVBO1, quadVBO2, quadVBO3, quadEBO;


//time
double last_time = glfwGetTime();
double unprocessed_time = 0.0;
double current_time = 0.0;
double passed_time = 0.0;
bool should_render = false;
double frame_time = 1.0 / 60.0;

std::shared_ptr<SceneGraphNode> root_node;
std::shared_ptr<SceneGraphNode> cube1;
std::shared_ptr<SceneGraphNode> cube2;
std::shared_ptr<SceneGraphNode> cube3;
std::shared_ptr<SceneGraphNode> test1;
std::shared_ptr<SceneGraphNode> progressbar;
std::shared_ptr<SceneGraphNode> modelTest;

std::shared_ptr<SceneGraphNode> floorTest;
std::shared_ptr<SceneGraphNode> meshesTest;
std::shared_ptr<SceneGraphNode> sandsTest;

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

    Shader lightingShader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
    Shader test2Shader("res/shaders/basic2.vert", "res/shaders/basic2.frag");
    Shader skyboxShader("res/shaders/skybox.vert", "res/shaders/skybox.frag");
    Shader textShader("res/shaders/text.vert", "res/shaders/text.frag");

    Model box("res/models/box.obj");
    Model sphere("res/models/sphere.obj");

    Model floor("res/models/floor.obj");
    Model meshes("res/models/meshes.obj");
    Model sands("res/models/sands.obj");

    skyboxShader.use();
    glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
    //    glBufferSubData(GL_ARRAY_BUFFER,0, sizeof(bar), &bar);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


    // load textures (we now use a utility function to keep the code more organized)
    // -----------------------------------------------------------------------------
    unsigned int diffuseMap = loadTexture("res/textures/diff.jpg");
    unsigned int specularMap = loadTexture("res/textures/spec.jpg");

    // shader configuration
    // --------------------

    lightingShader.use();
    lightingShader.setInt("material.diffuse", 0);
    lightingShader.setInt("material.specular", 1);

    testShader.use();
    testShader.setInt("texture_diffuse1", 0);

    // load models
    // -----------
    //Model myModel("../../res/models/kupa.obj");
    unsigned int texture = loadTexture("res/textures/stone.jpg");
    unsigned int texturekupa = loadTexture("res/textures/win.png");
    unsigned int texturegrass = loadTexture("res/textures/grasstexture.png");
    unsigned int texturemetal = loadTexture("res/textures/metaltexture.png");
    unsigned int texturesand = loadTexture("res/textures/sandtexture.png");
    //unsigned int candy = loadTexture("res/textures/candy.jpg");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    root_node = std::make_shared<SceneGraphNode>();
    cube1 = std::make_shared<SceneGraphNode>();
    cube2 = std::make_shared<SceneGraphNode>();
    cube3 = std::make_shared<SceneGraphNode>();
    test1 = std::make_shared<SceneGraphNode>();
    modelTest = std::make_shared<SceneGraphNode>();
    floorTest = std::make_shared<SceneGraphNode>();
    meshesTest = std::make_shared<SceneGraphNode>();
    sandsTest = std::make_shared<SceneGraphNode>();


    PlayerController* player = new PlayerController(cubePositions[4]);

    root_node->add_child(cube1);
    cube1->shaderTemp = lightingShader;
    cube1->texture = texture;
    cube1->get_transform().m_position = cubePositions[0];
    cube1->tempRender = BOX;
    cube1->VAOTemp = cubeVAO;

    root_node->add_child(cube2);
    cube2->shaderTemp = lightingShader;
    cube2->texture = texturekupa;
    cube2->get_transform().m_position = cubePositions[2];
    cube2->tempRender = BOX;
    cube2->VAOTemp = cubeVAO;

    root_node->add_child(cube3);
    cube3->shaderTemp = lightingShader;
    cube3->texture = texturekupa;
    cube3->get_transform().m_position = player->getPlayerPosition();
    cube3->tempRender = BOX;
    cube3->VAOTemp = cubeVAO;

    root_node->add_child(modelTest);
    modelTest->shaderTemp = lightingShader;
    modelTest->texture = texturekupa;
    modelTest->get_transform().m_position = cubePositions[3];
    modelTest->tempRender = MODEL;
    modelTest->modelTemp = sphere;
    modelTest->get_transform().m_scale = 0.15f;

    root_node->add_child(floorTest);
    floorTest->shaderTemp = lightingShader;
    floorTest->texture = texturegrass;
    floorTest->get_transform().m_position = floorPos;
    floorTest->tempRender = MODEL;
    floorTest->modelTemp = floor;
    floorTest->get_transform().m_scale = 0.02f;

    root_node->add_child(sandsTest);
    sandsTest->shaderTemp = lightingShader;
    sandsTest->texture = texturesand;
    sandsTest->get_transform().m_position = zeroPos;
    sandsTest->tempRender = MODEL;
    sandsTest->modelTemp = sands;
    sandsTest->get_transform().m_scale = 0.01f;

    root_node->add_child(meshesTest);
    meshesTest->shaderTemp = lightingShader;
    meshesTest->texture = texturemetal;
    meshesTest->get_transform().m_position = zeroPos;
    meshesTest->tempRender = MODEL;
    meshesTest->modelTemp = meshes;
    meshesTest->get_transform().m_scale = 0.01f;
    

    Skybox skybox;
    Text text(textShader);

    std::shared_ptr<SceneGraphNode> collidingObjects[] = { cube1,cube2,modelTest,floorTest,meshesTest,sandsTest };

    while (!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        passed_time = current_time - last_time;
        last_time = current_time;
        unprocessed_time += passed_time;

        input(window);
        player->move(window, &cube3->get_transform().m_position, passed_time);
        checkForCollisions(player, collidingObjects);



        while (unprocessed_time >= frame_time) {
            should_render = true;
            unprocessed_time -= frame_time;
            update(frame_time);
        }


        if (should_render) {
            should_render = false;
            
            render();
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

            text.RenderText(textShader, strs.str(), 50.0f, 50.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));

            render_gui();
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
    }
    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGlfw_Shutdown();
    //ImGui::DestroyContext();
    
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &VBO);

    //    glDeleteBuffers(1, &vbo_id);
    //    glDeleteBuffers(1, &colors_vbo_id);
    //    glDeleteBuffers(1, &ebo_id);
    //    glDeleteVertexArrays(1, &vao_id);

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
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        cube2->get_transform().x_rotation_angle += 6.0f * passed_time;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        cube2->get_transform().z_rotation_angle += 9.0f * passed_time;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        camera.Position = cube3->get_transform().m_position + cameraPos;
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

unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void checkForCollisions(PlayerController* player, std::shared_ptr<SceneGraphNode> objects[]) {
    Shader textShader("res/shaders/text.vert", "res/shaders/text.frag");
    glm::vec3 play = cube3->get_transform().m_position;  //player->getPlayerPosition() doesnt work
    for (int i = 0; i < 3; i++) //change "3" to "number of objects in array"
    {
        glm::vec3 p = objects[i]->get_transform().m_position;
        float distance = sqrt((p.x - play.x) * (p.x - play.x) + (p.y - play.y) * (p.y - play.y) + (p.z - play.z) * (p.z - play.z));
        if (distance <= 1.5f)
        {
            //push player outside
            glm::vec3 direction(play.x - p.x, play.y - p.y, play.z - p.z);
            cube3->get_transform().m_position.x += direction.x * 2.5f * passed_time;
            cube3->get_transform().m_position.y += direction.y * 2.5f * passed_time;
            cube3->get_transform().m_position.z += direction.z * 2.5f * passed_time;

            camera.Position.x = cube3->get_transform().m_position.x + cameraPos.x;  //attach camera to player
            camera.Position.z = cube3->get_transform().m_position.z + cameraPos.z;  //attach camera to player
            //while (distance <= 1.5f) {
                //cube3->get_transform().m_position.x += direction.x * 0.1f;
                //cube3->get_transform().m_position.y += direction.y * 0.1f;
                //cube3->get_transform().m_position.z += direction.z * 0.1f;
                //distance = sqrt((p.x - play.x) * (p.x - play.x) + (p.y - play.y) * (p.y - play.y) + (p.z - play.z) * (p.z - play.z));
            //}
        }
    }
}

void update(float dt) {
    if (x < -0.50f) {
        x = x + 0.01f;
        bar[4] = x;
        bar[6] = x;
        bar[8] = x;

        //std::cout << bar[4] << " " << std::endl;

    }
    else {
        x = -0.90f;
    }
    strs.str(std::string());

    strs << passed_time;
    cube2->update_transform();
    cube3->update_transform();
    root_node->update(Transform(), false);
}

void render() {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    root_node->render(true);

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