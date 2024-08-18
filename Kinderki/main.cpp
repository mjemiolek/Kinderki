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
#include "ModelAnimation.h"
#include "SceneGraph.h"
#include "PlayerController.h"
#include "AIController.h"
#include "Skybox.h"
#include "GameManager.h"
#include "ColliderManager.h"
#include "Gui.h"
#include "Settings.h"
#include "GravityManager.h"
#include "PhysicsWorld.h"
#include "BallManager.h"
#include "MovableManager.h"
#include "WaterFrameBuffers.h"

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
void daySimulation(float dt,bool changeday, std::shared_ptr<SceneGraphNode> playerObject);

GLFWwindow* window = nullptr;
//light
glm::vec3 lightPosition(30.0f, 35.0f, 10.0f);
// camera
glm::vec3 cameraPos(0.0f, 10.0f, 5.0f);
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
double frame_time = 1.0 / 144.0;

bool temp = true;

bool showMidDayStories = false;


int playerWins = 0;
int playerWinsOld = 0;
int escapeN = NULL;

bool already = false;

int mode = 0;

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
    glfwWindowHint(GLFW_SAMPLES, 4); // for MSAA rendering to default framebuffer

    // Create window with graphics context

    //in fullscreen
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Playground Escape", glfwGetPrimaryMonitor(), NULL);
    //window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Playground Escape", NULL, NULL);
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
    glEnable(GL_MULTISAMPLE); // for MSAA rendering to default framebuffer
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //for water
    glEnable(GL_CLIP_DISTANCE0);
    WaterFrameBuffers *buffers = new WaterFrameBuffers();
    unsigned int refractiontexture=0;
    unsigned int reflectiontexture=0;
    float moveFactor = 0.0f;

    //Creating game components
    GameManager gameManager;
    ColliderManager colManager(gameManager.collidingObjects);
    PhysicsWorld physicsWorld(gameManager.collidingObjects);
    Gui gui;
    Skybox skybox;
    BallManager* ballManager = new BallManager(gameManager.ball, gameManager.cube3, gameManager.damagedwallptr,gameManager.wallsptr);
    AIController* AI = new AIController(gameManager.cube2);
    AIController* AI2 = new AIController(gameManager.cubeKid2);
    AIController* AI3 = new AIController(gameManager.cubeKid3);
    AIController* AI4 = new AIController(gameManager.cubeKid4);
    AIController* AI5 = new AIController(gameManager.cubeKid5);
    //AI2 - AI near sandPit, AI5 - near Tyrolka 

    MovableManager* movableManager = new MovableManager(gameManager.root_node, gameManager.player);
    movableManager->addMovable(gameManager.heartptr);
    movableManager->addMovable(gameManager.heartptr2);
    movableManager->addMovable(gameManager.colaptr);
    movableManager->addMovable(gameManager.mentosptr);
    movableManager->addMovable(gameManager.bucketblackptr);
    movableManager->addMovable(gameManager.bucketpinkptr);
    movableManager->addMovable(gameManager.bucketredptr);

    //water
    unsigned int dudvMap = gameManager.loadTexture("res/textures/water/waterDUDV.png");
    unsigned int normalMap = gameManager.loadTexture("res/textures/water/water.png");

    //load texture to gui
    unsigned int texture = gameManager.loadTexture("res/textures/notebook.png");
    unsigned int textureSeeSaw = gameManager.loadTexture("res/textures/icons/Iseesaw.png");
    unsigned int textureAerialRunway = gameManager.loadTexture("res/textures/icons/Iaerialrunway.png");
    unsigned int textureSwing = gameManager.loadTexture("res/textures/icons/Iswing.png");
    unsigned int textureTrampoline = gameManager.loadTexture("res/textures/icons/Itrampoline.png");
    unsigned int textureWallDestroy = gameManager.loadTexture("res/textures/icons/Iwallbang.png");
    unsigned int textureSandpit = gameManager.loadTexture("res/textures/icons/sandpit.png");
    unsigned int textureSlide = gameManager.loadTexture("res/textures/icons/slide.png");

    unsigned int textureCandy = gameManager.loadTexture("res/textures/candy/candy.png");
    unsigned int textureCandyx0 = gameManager.loadTexture("res/textures/candy/candyx0.png");
    unsigned int textureCandyx1 = gameManager.loadTexture("res/textures/candy/candyx1.png");
    unsigned int textureCandyx2 = gameManager.loadTexture("res/textures/candy/candyx2.png");
    unsigned int textureCandyx3 = gameManager.loadTexture("res/textures/candy/candyx3.png");
    unsigned int textureCandyx4 = gameManager.loadTexture("res/textures/candy/candyx4.png");
    unsigned int textureCandyx5 = gameManager.loadTexture("res/textures/candy/candyx5.png");
    unsigned int textureCandyx6 = gameManager.loadTexture("res/textures/candy/candyx6.png");

    unsigned int textureIns = gameManager.loadTexture("res/textures/ins.png");
    unsigned int textureTime = gameManager.loadTexture("res/textures/gui/tim.png");

    unsigned int kidIntTexture = gameManager.loadTexture("res/textures/tutorial/tutorial_up.png");
    unsigned int findIntTexture = gameManager.loadTexture("res/textures/tutorial/tutorial_middle_4.png");
    unsigned int itemIntTexture = gameManager.loadTexture("res/textures/tutorial/tutorial_middle_3.png");
    unsigned int moveIntTexture = gameManager.loadTexture("res/textures/tutorial/tutorial_middle_2.png");
    unsigned int sandpitIntTexture = gameManager.loadTexture("res/textures/tutorial/tutorial_middle_1.png");
    unsigned int nextTexture1 = gameManager.loadTexture("res/textures/tutorial/tutorial_middle_5.png");
    unsigned int nextTexture2 = gameManager.loadTexture("res/textures/tutorial/tutorial_down.png");

    unsigned int buyHintWindowTexture = gameManager.loadTexture("res/textures/gui/interaction.png");
    unsigned int notEnoughCandyTexture = gameManager.loadTexture("res/textures/gui/notEnoughCandy.png");
    unsigned int pilkaPlotHintTexture = gameManager.loadTexture("res/textures/gui/pilkaPlotHint.png");
    unsigned int tyrolkerHintTexture = gameManager.loadTexture("res/textures/gui/tyrolkerHint.png");
    unsigned int sandPitHintTexture = gameManager.loadTexture("res/textures/gui/sandPitHint.png");
    unsigned int boyHelpingHintTexture = gameManager.loadTexture("res/textures/gui/boyHelpingHint.png");

    unsigned int licznik0 = gameManager.loadTexture("res/textures/gui/licznik_0_5.png");
    unsigned int licznik1 = gameManager.loadTexture("res/textures/gui/licznik_1_5.png");
    unsigned int licznik2 = gameManager.loadTexture("res/textures/gui/licznik_2_5.png");
    unsigned int licznik3 = gameManager.loadTexture("res/textures/gui/licznik_3_5.png");
    unsigned int licznik4 = gameManager.loadTexture("res/textures/gui/licznik_4_5.png");
    unsigned int licznik5 = gameManager.loadTexture("res/textures/gui/licznik_5_5.png");

    gui.licznik0 = licznik0;
    gui.licznik1 = licznik1;
    gui.licznik2 = licznik2;
    gui.licznik3 = licznik3;
    gui.licznik4 = licznik4;
    gui.licznik5 = licznik5;

    gui.textureInt1 = buyHintWindowTexture;
    gui.textureInt2 = notEnoughCandyTexture;
    gui.textureInt5 = pilkaPlotHintTexture;
    gui.textureInt4 = tyrolkerHintTexture;
    gui.textureInt3 = sandPitHintTexture;
    gui.textureInt6 = boyHelpingHintTexture;

    unsigned int midday1 = gameManager.loadTexture("res/textures/stories/midday/story1.png");
    unsigned int midday2 = gameManager.loadTexture("res/textures/stories/midday/story2.png");
    unsigned int midday3 = gameManager.loadTexture("res/textures/stories/midday/story3.png");
    unsigned int midday4 = gameManager.loadTexture("res/textures/stories/midday/story4.png");
    unsigned int midday5 = gameManager.loadTexture("res/textures/stories/midday/story5.png");

    unsigned int tyrolker1 = gameManager.loadTexture("res/textures/stories/tyrolker/tyrolker1.png");
    unsigned int tyrolker2 = gameManager.loadTexture("res/textures/stories/tyrolker/tyrolker2.png");
    unsigned int tyrolker3 = gameManager.loadTexture("res/textures/stories/tyrolker/tyrolker3.png");
    unsigned int tyrolker4 = gameManager.loadTexture("res/textures/stories/tyrolker/tyrolker3.png");

    unsigned int sandpit1 = gameManager.loadTexture("res/textures/stories/sandpit/sandpit1.png");
    unsigned int sandpit2 = gameManager.loadTexture("res/textures/stories/sandpit/sandpit2.png");
    unsigned int sandpit3 = gameManager.loadTexture("res/textures/stories/sandpit/sandpit3.png");
    unsigned int sandpit4 = gameManager.loadTexture("res/textures/stories/sandpit/sandpit3.png");

    unsigned int wallbang1 = gameManager.loadTexture("res/textures/stories/wallbang/wallbang1.png");
    unsigned int wallbang2 = gameManager.loadTexture("res/textures/stories/wallbang/wallbang2.png");
    unsigned int wallbang3 = gameManager.loadTexture("res/textures/stories/wallbang/wallbang3.png");
    unsigned int wallbang4 = gameManager.loadTexture("res/textures/stories/wallbang/wallbang3.png");

    unsigned int hustawker1 = gameManager.loadTexture("res/textures/stories/hustawker/hustawker1.png");
    unsigned int hustawker2 = gameManager.loadTexture("res/textures/stories/hustawker/hustawker2.png");
    unsigned int hustawker3 = gameManager.loadTexture("res/textures/stories/hustawker/hustawker3.png");
    unsigned int hustawker4 = gameManager.loadTexture("res/textures/stories/hustawker/hustawker3.png");

    unsigned int wazker1 = gameManager.loadTexture("res/textures/stories/grubas/grubas1.png");
    unsigned int wazker2 = gameManager.loadTexture("res/textures/stories/grubas/grubas2.png");
    unsigned int wazker3 = gameManager.loadTexture("res/textures/stories/grubas/grubas3.png");
    unsigned int wazker4 = gameManager.loadTexture("res/textures/stories/grubas/grubas3.png");

    unsigned int liner1 = gameManager.loadTexture("res/textures/stories/liner/liner1.png");
    unsigned int liner2 = gameManager.loadTexture("res/textures/stories/liner/liner2.png");
    unsigned int liner3 = gameManager.loadTexture("res/textures/stories/liner/liner3.png");
    unsigned int liner4 = gameManager.loadTexture("res/textures/stories/liner/liner3.png");

    unsigned int tree1 = gameManager.loadTexture("res/textures/stories/tree/tree1.png");
    unsigned int tree2 = gameManager.loadTexture("res/textures/stories/tree/tree2.png");
    unsigned int tree3 = gameManager.loadTexture("res/textures/stories/tree/tree3.png");
    unsigned int tree4 = gameManager.loadTexture("res/textures/stories/tree/tree3.png");

    unsigned int fin1 = gameManager.loadTexture("res/textures/stories/fin/fin1.png");
    unsigned int fin2 = gameManager.loadTexture("res/textures/stories/fin/fin2.png");
    unsigned int fin3 = gameManager.loadTexture("res/textures/stories/fin/fin3.png");

    gameManager.tutorialState->setTexture1(kidIntTexture);
    gameManager.tutorialState->setTexture2(findIntTexture);
    gameManager.tutorialState->setTexture3(itemIntTexture);
    gameManager.tutorialState->setTexture4(moveIntTexture);
    gameManager.tutorialState->setTexture5(sandpitIntTexture);
    gameManager.tutorialState->setTexture6(nextTexture1);
    gameManager.tutorialState->setTexture7(nextTexture2);

    gui.texture = texture;
    gui.textureSeeSaw = textureSeeSaw;
    gui.textureAerialRunway = textureAerialRunway;
    gui.textureSwing = textureSwing;
    gui.textureTrampoline = textureTrampoline;
    gui.textureWallDestroy = textureWallDestroy;
    gui.textureSandpit = textureSandpit;
    gui.textureSlide = textureSlide;

    gui.textureIns = textureIns;

    gui.textureCandy = textureCandy;

    gui.textureTime = textureTime;

    gui.midday1 = midday1;
    gui.midday2 = midday2;
    gui.midday3 = midday3;
    gui.midday4 = midday4;
    gui.midday5 = midday5;

    gui.tyrolker1 = tyrolker1;
    gui.tyrolker2 = tyrolker2;
    gui.tyrolker3 = tyrolker3;
    gui.tyrolker4 = tyrolker4;

    gui.hustawker1 = hustawker1;
    gui.hustawker2 = hustawker2;
    gui.hustawker3 = hustawker3;
    gui.hustawker4 = hustawker4;

    gui.wazker1 = wazker1;
    gui.wazker2 = wazker2;
    gui.wazker3 = wazker3;
    gui.wazker4 = wazker4;

    gui.sandpit1 = sandpit1;
    gui.sandpit2 = sandpit2;
    gui.sandpit3 = sandpit3;
    gui.sandpit4 = sandpit4;

    gui.wallbang1 = wallbang1;
    gui.wallbang2 = wallbang2;
    gui.wallbang3 = wallbang3;
    gui.wallbang4 = wallbang4;

    gui.liner1 = liner1;
    gui.liner2 = liner2;
    gui.liner3 = liner3;
    gui.liner4 = liner4;

    gui.tree1 = tree1;
    gui.tree2 = tree2;
    gui.tree3 = tree3;
    gui.tree4 = tree4;

    gui.fin1 = fin1;
    gui.fin2 = fin2;
    gui.fin3 = fin3;
    
    Sound bgSound("res/sounds/background-music.wav");
    bgSound.playLooped();

    bool pressFlagCandy = false;
    while (!glfwWindowShouldClose(window))
    {
        current_time = glfwGetTime();
        passed_time = current_time - last_time;
        //if (passed_time > 0.25) {
        //    passed_time = 0.25;
        //}
        last_time = current_time;
        unprocessed_time += passed_time;

        input(window, gameManager.cube3);
        daySimulation(passed_time, gui.changeday, gameManager.cube3);
        ballManager->manageBall(window, passed_time);
        gameManager.getTutorialState()->update(window, gameManager.player, gameManager.cubeKid2, gameManager.sandpitptr);
        gameManager.player->sandPiter(window, gameManager.sandpitptr, passed_time, gameManager.heartptr2);
        movableManager->manageMovable(window);
        gameManager.player->checkForInteraction(window, gameManager.cubeKid2, gameManager.cubeKid3, gameManager.cubeKid4, gameManager.cubeKid5, gameManager.cube2);
        gui.setInteractionTexture(gameManager.player->getTextureLayer(), gameManager.player->getFinishedTutorial());
        gameManager.player->move(window, passed_time, current_time);
        gameManager.player->trampoliner(gameManager.trampolineptr, passed_time);
        gameManager.player->hustawker(gameManager.swingptr, gameManager.swingseatptr, passed_time);
        gameManager.player->wazker(gameManager.seesawptr, passed_time);
        gameManager.player->liner(gameManager.aerialrunnwaywholeptr->additionalTriggers.at(0));
        gameManager.player->candier(gameManager.candyCane1ptr, gameManager.candyCane2ptr, gameManager.candyCane3ptr, gameManager.candyCane4ptr,
        gameManager.candyCane5ptr, gameManager.candyCane6ptr, passed_time);
        gameManager.player->tyrolker(gameManager.aerialrunnwayseatptr, passed_time, gameManager.colaptr, gameManager.mentosptr,gameManager.aerialrunnwaywholeptr);
        gui.textureCandyCount = gameManager.candyCount(gameManager.player, textureCandyx0, textureCandyx1, textureCandyx2, textureCandyx3, textureCandyx4, textureCandyx5, textureCandyx6);
        //colManager.manageCollisions(passed_time);
        physicsWorld.step(passed_time);
        gui.handleGui(window);
        moveFactor += 0.03f * passed_time;
        moveFactor = fmod(moveFactor,1.0f);
        gameManager.update(passed_time);
        gameManager.checkWin(); //check for win
        gameManager.player->alreadyescapedTyrolker = gameManager.already;
        playerWins = gameManager.playerWins;
        escapeN = gameManager.ESC;
        gui.update(passed_time, escapeN, playerWins);

        while (unprocessed_time >= frame_time) {
            should_render = true;
            unprocessed_time -= frame_time;

        }
        if (playerWins != playerWinsOld) {
            playerWinsOld = playerWins;
            lightPosition.x = 35.0f;
        }


        if (should_render) {
            should_render = false;
            //std::cout<< gameManager.cube3->m_transform.m_position.x << " , " << gameManager.cube3->m_transform.m_position.y << " , " << gameManager.cube3->m_transform.m_position.z << std::endl;
            //water
            //refraction
            glm::vec4 clipPlane = glm::vec4(0.0f, -1.0f, 0.0f, gameManager.waterHeight);
            //viewport
            refractiontexture = buffers->getRefractionTexture();
            buffers->bindRefraction();
            gameManager.render(clipPlane,buffers->REFRACTION_WIDTH,buffers->REFRACTION_HEIGHT);
            skybox.render();
            buffers->unbindBuffer();
            //reflection
            //move camera
            /*float distance = 2 * (camera.Position.y - clipPlane.w);
            camera.Position.y -= distance;
            camera.setPitch(-camera.Pitch);*/
            //move camera
            glm::vec4 clipPlane2 = glm::vec4(0.0f, 1.0f, 0.0f, -gameManager.waterHeight);
            reflectiontexture = buffers->getReflectionTexture();
            buffers->bindReflection();
            gameManager.render(clipPlane2, buffers->REFLECTION_WIDTH, buffers->REFLECTION_HEIGHT);
            skybox.render();
            buffers->unbindBuffer();
            //move camera
            /*camera.Position.y += distance;
            camera.setPitch(-camera.Pitch);*/
            //move camera

            //render game
            gameManager.renderwithShadows(mode);
            gameManager.renderWater(refractiontexture, reflectiontexture,dudvMap,normalMap,moveFactor);
            skybox.render();
            gui.render();
            gameManager.getTutorialState()->render();
            gui.render_interaction();                         

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
   // delete gameManager.player;
    delete ballManager;
    delete buffers;
    delete AI, AI2, AI3, AI4, AI5;

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

    if(glfwGetKey(window, GLFW_KEY_KP_0) == GLFW_PRESS)  mode = 0;
    if(glfwGetKey(window, GLFW_KEY_KP_1) == GLFW_PRESS)  mode = 1;
    if(glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)  mode = 2;
    if(glfwGetKey(window, GLFW_KEY_KP_3) == GLFW_PRESS)  mode = 3;
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
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        lightPosition.x = 35.0f;
    }
    camera.Position.x = player->get_transform().m_position.x - camera.offsetX();  //attach camera to player
    camera.Position.z = player->get_transform().m_position.z - camera.offsetZ();  //attach camera to player
    camera.Position.y = player->get_transform().m_position.y - camera.offsetY() + 1.2f;  //attach camera to player

    lightPos.x = player->get_transform().m_position.x + lightPosition.x;     //attach light to player
    lightPos.y = player->get_transform().m_position.y + lightPosition.y;     //attach light to player
    lightPos.z = player->get_transform().m_position.z + lightPosition.z;     //attach light to player
}

void daySimulation(float dt, bool changeday, std::shared_ptr<SceneGraphNode> playerObject)
{
    //float step = -0.3f;
    lightPosition.y = -0.01 * lightPosition.x * lightPosition.x + 35;
    lightPosition.x += -0.2f * dt;
    if (changeday) {
        lightPosition.x = 35.0f; //end of day
        playerObject->get_transform().m_position = glm::vec3(27.0f, 0.2f, 9.17f); // dzieciak na start
    }
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
    //if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
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
    //}
    //else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
