//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <irrKlang/ik_ISound.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "model.h"

#include <iostream>
#include <mmcobj.h>

static void glfw_error_callback(int error, const char* description);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void input(GLFWwindow* window);
unsigned int loadTexture(char const* path);
void update(float dt);
void render();
void render_gui();

GLFWwindow* window = nullptr;

// settings
const GLuint SCR_WIDTH = 1280;
const GLuint SCR_HEIGHT = 720;

// camera
Camera camera(glm::vec3(0.0f, 5.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(0.5f, 0.2f, -1.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
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

float x = -0.90f;

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

struct Transform {
    Transform() : m_world_matrix(1.0f) {}
    glm::mat4 get_combined_matrix() {
        return glm::translate(glm::mat4(1.0f), m_position) *
            glm::rotate(glm::mat4(1.0f), glm::radians(x_rotation_angle), glm::vec3(-1, 0, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(y_rotation_angle), glm::vec3(0, -1, 0)) *
            glm::rotate(glm::mat4(1.0f), glm::radians(z_rotation_angle), glm::vec3(0, 0, -1)) *
            glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));
    }
    glm::mat4 m_world_matrix; //TODO: private
    glm::vec3 m_position = glm::vec3(0.0f);
    float x_rotation_angle = 0.0f;
    float y_rotation_angle = 0.0f;
    float z_rotation_angle = 0.0f;
    float m_scale = 1.0;
};


struct SceneGraphNode {
    SceneGraphNode() : m_dirty(true) {}
    explicit SceneGraphNode(const Transform& t) : m_transform(t), m_dirty(true) {}
    void add_child(const std::shared_ptr<SceneGraphNode>& sgn) {
        m_children.push_back(sgn);
    }
    void update(const Transform& parent_transform, bool dirty) {
        dirty |= m_dirty;
        if (dirty) {
            m_transform.m_world_matrix = m_transform.get_combined_matrix();
            m_transform.m_world_matrix = parent_transform.m_world_matrix * m_transform.m_world_matrix;
            m_dirty = false;
        }
        for (uint32_t i = 0; i < m_children.size(); ++i) {
            m_children[i]->update(m_transform, dirty);
        }
    }
    void render(bool is_root = false
    ) {
        if (!is_root) {


            shaderTemp.use();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            shaderTemp.setMat4("projection", projection);

            glm::mat4 view = camera.GetViewMatrix();
            shaderTemp.setMat4("view", view);
            shaderTemp.setMat4("u_world", m_transform.m_world_matrix);

            if (isBox && !is2d) {

                shaderTemp.setVec3("viewPos", camera.Position);
                shaderTemp.setVec3("light.direction", -1.0f, -0.8f, -1.0f);
                shaderTemp.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
                shaderTemp.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
                shaderTemp.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
                shaderTemp.setFloat("material.shininess", 64.0f);
                glBindVertexArray(cubeVAO);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            //            if(is2d && !isBox){

            //            }



                        //glm::mat4 model = glm::mat4(1.0f);
            //            model = glm::translate(model, cubePositions[2]);
            //            float anglet = 20.0f * 2;
            //            model = glm::rotate(model, glm::radians(anglet), glm::vec3(1.0f, 0.3f, 0.5f));
            //            shaderTemp.setMat4("model", model);
            //            glBindTexture(GL_TEXTURE_2D, textureSpec);
            //            glDrawArrays(GL_TRIANGLES, 0, 36);

        }
        for (uint32_t i = 0; i < m_children.size(); ++i) {
            m_children[i]->render();
        }
    }
    void update_transform() {
        m_transform.m_world_matrix = m_transform.get_combined_matrix();
        m_dirty = true;
    }
    Transform& get_transform() {
        return m_transform;
    }

    Shader shaderTemp = Shader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    GLuint texture;
    bool isBox = false;
    bool is2d = false;

private:
    std::vector<std::shared_ptr<SceneGraphNode>> m_children;
    Transform m_transform;
    bool m_dirty;

};


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
std::shared_ptr<SceneGraphNode> test1;
std::shared_ptr<SceneGraphNode> progressbar;

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

    // build and compile shaders
    // -------------------------
    //Shader ourShader("D:/Users/wojci/CLionProjects/OpenGLPAG/res/shaders/model.vert", "D:/Users/wojci/CLionProjects/OpenGLPAG/res/shaders/model.frag");

    Shader lightingShader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    Shader testShader("res/shaders/basic.vert", "res/shaders/basic.frag");
    Shader test2Shader("res/shaders/basic2.vert", "res/shaders/basic2.frag");
    //Shader lightCubeShader("D:/Users/wojci/CLionProjects/OpenGLPAG/res/shaders/lightcube.vert", "D:/Users/wojci/CLionProjects/OpenGLPAG/res/shaders/lightcube.frag");

    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    //
    //
    //
    rapidjson::Document document;
    document.Parse(json);

    // 2. Modify it by DOM.
    rapidjson::Value& s = document["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    //

    //    FT_Library ft;
    //    if (FT_Init_FreeType(&ft))
    //    {
    //        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    //        return -1;
    //    }
    //
    //    FT_Face face;
    //    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
    //    {
    //        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    //        return -1;
    //    }

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------



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

    //    glGenBuffers(1, &quadVBO2);
    //    glBindBuffer(GL_ARRAY_BUFFER, quadVBO2);
    //    glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    //    glEnableVertexAttribArray(1);
    //    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

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
    Model ourModel("res/models/box.obj");
    //Model myModel("../../res/models/kupa.obj");
    unsigned int texture = loadTexture("res/textures/stone.jpg");
    unsigned int texturekupa = loadTexture("res/textures/win.png");
    //unsigned int candy = loadTexture("res/textures/candy.jpg");

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    root_node = std::make_shared<SceneGraphNode>();
    cube1 = std::make_shared<SceneGraphNode>();
    cube2 = std::make_shared<SceneGraphNode>();
    test1 = std::make_shared<SceneGraphNode>();

    root_node->add_child(cube1);
    cube1->shaderTemp = lightingShader;
    cube1->texture = texture;
    cube1->get_transform().m_position = cubePositions[0];
    cube1->isBox = true;

    root_node->add_child(cube2);
    cube2->shaderTemp = lightingShader;
    cube2->texture = texturekupa;
    cube2->get_transform().m_position = cubePositions[2];
    cube2->isBox = true;

    //    root_node->add_child(test1);
    //    test1->shaderTemp = testShader;
    //    test1->texture = texture;
    //    test1->is2d = true;







    while (!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        passed_time = current_time - last_time;
        last_time = current_time;
        unprocessed_time += passed_time;

        while (unprocessed_time >= frame_time) {
            should_render = true;
            unprocessed_time -= frame_time;
            update(frame_time);

        }

        if (should_render) {
            should_render = false;
            input(window);
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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, passed_time);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, passed_time);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, passed_time);
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

void update(float dt) {
    if (x < -0.50f) {
        x = x + 0.01f;
        bar[4] = x;
        bar[6] = x;
        bar[8] = x;

        std::cout << bar[4] << " " << std::endl;

    }
    else {
        x = -0.90f;
    }

    root_node->update(Transform(), false);
}
void render() {
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    root_node->render(true);

}
void render_gui() {


}