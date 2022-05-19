#pragma once
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

#include <irrKlang/ik_ISound.h>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "SceneGraph.h"
#include "PlayerController.h"
#include "Text.h"
#include "Skybox.h"
#include "Settings.h"
#include "Collider.h"
#include "GravityManager.h"
#include <mmcobj.h>
#include <vector>

//GameManager is responsible for creating and rendering objects, gameplay, game physics
class GameManager {
    public:
    std::shared_ptr<SceneGraphNode> root_node;
    std::shared_ptr<SceneGraphNode> cube1;
    std::shared_ptr<SceneGraphNode> cube2;
    std::shared_ptr<SceneGraphNode> cube3; //player
    std::shared_ptr<SceneGraphNode> ball;
    std::shared_ptr<SceneGraphNode> progressbar;
    std::vector<std::shared_ptr<SceneGraphNode>> collidingObjects;
    std::shared_ptr<GravityManager> gravity;

    std::shared_ptr<SceneGraphNode> aerialrunnwayptr;
    std::shared_ptr<SceneGraphNode> benchesptr;
    std::shared_ptr<SceneGraphNode> floorptr;
    std::shared_ptr<SceneGraphNode> footballstuffptr;
    std::shared_ptr<SceneGraphNode> sandpitptr;
    std::shared_ptr<SceneGraphNode> sandsptr;
    std::shared_ptr<SceneGraphNode> seesawptr;
    std::shared_ptr<SceneGraphNode> seesawreversepts;
    std::shared_ptr<SceneGraphNode> slideptr;
    std::shared_ptr<SceneGraphNode> swingptr;
    std::shared_ptr<SceneGraphNode> tablesptr;
    std::shared_ptr<SceneGraphNode> trampolineptr;
    std::shared_ptr<SceneGraphNode> treeptr;
    std::shared_ptr<SceneGraphNode> umbrellaptr;
    std::shared_ptr<SceneGraphNode> walkptr;
    std::shared_ptr<SceneGraphNode> wallsptr;



    //For shadows
    Shader shaderShad = Shader("res/shaders/shadow_mapping.vert", "res/shaders/shadow_mapping.frag");
    unsigned int depthMapFBO, depthMap;
    Shader simpleDepthShader = Shader("res/shaders/shadow_mapping_depth.vert", "res/shaders/shadow_mapping_depth.frag");
    Shader debugDepthQuad = Shader("res/shaders/debug_quad.vert", "res/shaders/debug_quad.frag");
    //For outline
    Shader outlineShader = Shader("res/shaders/outlining.vert", "res/shaders/outlining.frag");



    GameManager() {
        // settings
        glm::vec3 zeroPos(0.0f, 0.0f, 0.0f);
        glm::vec3 floorPos(0.0f, 0.0f, 0.0f);
        glm::vec3 sandPitPos(8.87f, 1.82f, -14.34f);
        glm::vec3 seesawPos(7.53f, 1.82f, -5.46f);
        glm::vec3 ballPos(11.53f, 4.82f, 14.46f);
        glm::vec3 slidePos(21.40f, 1.82f, -15.12f);
        glm::vec3 trampolinePos(29.50f, 1.82f, -14.95f);
        glm::vec3 aerialRunnwayPos(32.87f, 1.82f, -9.91f);
        glm::vec3 swingPos(8.92f, 1.82f, 5.34f);

        glm::vec3 cubePositions[] = {
        glm::vec3(-0.5f, 2.0f,  3.5f),
        glm::vec3(2.0f,  2.0f, -15.0f),
        glm::vec3(0.5f, 2.5f, -1.5f),
        glm::vec3(-3.8f, 2.0f, -12.3f),
        glm::vec3(0.0f, 2.0f,  0.0f),
        glm::vec3(0.0f,  2.0f, 0.0f),
        glm::vec3(1.3f, 2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -1.5f),
        glm::vec3(-1.3f,  2.0f, -1.5f)
        };

        //Initializing gravity
        gravity = std::make_shared<GravityManager>();
        gravity->setGravity(0.5f);

        //Initializing shader
        Shader lightingShader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
        lightingShader.use();
        lightingShader.setInt("material.diffuse", 0);
        lightingShader.setInt("material.specular", 64);
        //lightingShader.setVec3("light.position", lightPos);


        //shadow shaders configuration
        shaderShad.use();
        shaderShad.setInt("diffuseTexture", 0);
        shaderShad.setInt("shadowMap", 1);

        // configure depth map FBO
        // -----------------------
        glGenFramebuffers(1, &depthMapFBO);
        // create depth texture
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapWidth, shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        // attach depth texture as FBO's depth buffer
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //Shadows configuration
        debugDepthQuad.use();
        debugDepthQuad.setInt("depthMap", 0);

        //Initializing models and textures
        Model box("res/models/box.obj");
        Model sphere("res/models/sphere.obj");

        Model aerialrunnway("res/models/level/aerialrunnway.obj");
        Model benches("res/models/level/benches.obj");
        Model floor("res/models/level/floor.obj");
        Model footballstuff("res/models/level/footballstuff.obj");
        Model sandpit("res/models/level/sandpit.obj");
        Model sands("res/models/level/sands.obj");
        Model seesaw("res/models/level/seesaw.obj");
        Model seesawrevers("res/models/level/seesawrevers.obj");
        Model slide("res/models/level/slide.obj");
        Model swing("res/models/level/swing.obj");
        Model tables("res/models/level/tables.obj");
        Model trampoline("res/models/level/trampoline.obj");
        Model tree("res/models/level/tree.obj");
        Model umbrella("res/models/level/umbrella.obj");
        Model walk("res/models/level/walk.obj");
        Model walls("res/models/level/walls.obj");

        //Model postac_test("res/models/main_character.obj");
        //Model postac_test("res/models/postac_test_kolejny.obj");
        Model postac_test("res/models/postac_test_v4.obj");




        unsigned int texturekupa = loadTexture("res/textures/win.png");
        unsigned int texturegrass = loadTexture("res/textures/grasstexture.png");
        unsigned int texturemetal = loadTexture("res/textures/metaltexture.png");
        unsigned int texturesand = loadTexture("res/textures/sandtexture.png");
        unsigned int textureplanks = loadTexture("res/textures/planks.png");
        unsigned int texturestone = loadTexture("res/textures/stone.jpg");

        unsigned int diffuseMap = loadTexture("res/textures/diff.jpg");
        unsigned int specularMap = loadTexture("res/textures/spec.jpg");

        //unsigned int texture_postac_test = loadTexture("res/textures/oko_tekstura_test2.png");
        unsigned int texture_postac_test = loadTexture("res/textures/baking_5.png");


        //Allocating storage for the objects
        root_node = std::make_shared<SceneGraphNode>();
        cube1 = std::make_shared<SceneGraphNode>();
        cube2 = std::make_shared<SceneGraphNode>();
        cube3 = std::make_shared<SceneGraphNode>();
        ball = std::make_shared<SceneGraphNode>();

        aerialrunnwayptr = std::make_shared<SceneGraphNode>();
        benchesptr = std::make_shared<SceneGraphNode>();
        floorptr = std::make_shared<SceneGraphNode>();
        footballstuffptr = std::make_shared<SceneGraphNode>();
        sandpitptr = std::make_shared<SceneGraphNode>();
        sandsptr = std::make_shared<SceneGraphNode>();
        seesawptr = std::make_shared<SceneGraphNode>();
        seesawreversepts = std::make_shared<SceneGraphNode>();
        slideptr = std::make_shared<SceneGraphNode>();
        swingptr = std::make_shared<SceneGraphNode>();
        tablesptr = std::make_shared<SceneGraphNode>();
        trampolineptr = std::make_shared<SceneGraphNode>();
        treeptr = std::make_shared<SceneGraphNode>();
        umbrellaptr = std::make_shared<SceneGraphNode>();
        walkptr = std::make_shared<SceneGraphNode>();
        wallsptr = std::make_shared<SceneGraphNode>();

        collidingObjects.insert(collidingObjects.end(), {  cube1,cube2,cube3, floorptr, ball });
        glm::vec3 boxColRange(2.5f, 0.5f, 0.7f);
        glm::vec3 triggerRange(0.80f, 0.80f, 0.80f);
        glm::vec3 floorColRange(300.0f, 20.0f, 300.0f);

        root_node->add_child(cube1);
        Collider cube1Collider(glm::vec3(0.38f, 0.38f, 0.38f), false, cubePositions[0],false);
        cube1->setProperties(lightingShader, texturestone, cubePositions[0], MODEL, box, 0.15f,true, cube1Collider);
        //test
        Collider cube1ExtraCollider(boxColRange, false,glm::vec3(-0.5f, 2.0f, 5.5f), false);
        cube1->additionalColliders.push_back(cube1ExtraCollider);
        //test

        root_node->add_child(cube2);
        Collider cube2Collider(boxColRange, false, cubePositions[2], false);
        cube2->setProperties(lightingShader, texturekupa, cubePositions[2], MODEL, box, 0.15f, true, cube2Collider);
        

        root_node->add_child(cube3);
        Collider cube3Collider(0.34f, false, cubePositions[4],true);
        //cube3->setProperties(lightingShader, texturekupa, cubePositions[4], MODEL, box, 0.15f, true, cube3Collider);
        cube3->setProperties(lightingShader, texture_postac_test, cubePositions[4], MODEL, postac_test, 1.0f, true, cube3Collider);

        root_node->add_child(ball);
        Collider ballCollider(0.28f, false, glm::vec3(0.0f, 2.0f, -2.0f), true);
        ball->setProperties(lightingShader, texturekupa, glm::vec3(0.0f, 2.0f, -2.0f),MODEL,sphere,0.03f,true,ballCollider);


        Collider aerialrunnwayTrigger(0.8f, false, sandPitPos, true);
        root_node->add_child(aerialrunnwayptr);
        aerialrunnwayptr->setProperties(lightingShader, texturemetal, zeroPos, MODEL, aerialrunnway, 0.01f,false);
        aerialrunnwayptr->trigger = aerialrunnwayTrigger;

        root_node->add_child(benchesptr);
        benchesptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, benches, 0.01f, false);

        root_node->add_child(floorptr);
        Collider floorCol(floorColRange, false, glm::vec3(15.0f, -18.56f, 0.0f), false);
        floorptr->setProperties(lightingShader, texturegrass, floorPos, MODEL, floor, 0.01f, false, floorCol);

        root_node->add_child(footballstuffptr);
        footballstuffptr->setProperties(lightingShader, texturemetal, zeroPos, MODEL, footballstuff, 0.01f, false);

        root_node->add_child(sandpitptr);
        Collider sandPitTrigger(2.43f, false, sandPitPos, true);
        sandpitptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, sandpit, 0.01f, false);
        sandpitptr->trigger = sandPitTrigger;

        root_node->add_child(sandsptr);
        sandsptr->setProperties(lightingShader, texturesand, zeroPos, MODEL, sands, 0.01f, false);

        Collider seesawTrigger(0.5f, false, seesawPos, true);
        root_node->add_child(seesawptr);
        seesawptr->setProperties(lightingShader, texturemetal, zeroPos, MODEL, seesaw, 0.01f, true);
        seesawptr->trigger = seesawTrigger;

        //root_node->add_child(seesawreversepts);
        //seesawreversepts->setProperties(lightingShader, texturemetal, zeroPos, MODEL, seesawreverse, 0.01f);

        Collider slideTrigger(1.2f, false, slidePos, true);
        root_node->add_child(slideptr);
        slideptr->setProperties(lightingShader, texturemetal, zeroPos, MODEL, slide, 0.01f, true);
        slideptr->trigger = slideTrigger;


        Collider swingTrigger(1.0f, false, swingPos, true);
        root_node->add_child(swingptr);
        swingptr->setProperties(lightingShader, texturemetal, zeroPos, MODEL, swing, 0.01f, true);
        swingptr->trigger = swingTrigger;

        root_node->add_child(tablesptr);
        tablesptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, tables, 0.01f, false);

        Collider trampolineTrigger(glm::vec3(1.0f, 0.1f, 1.0f), false, trampolinePos, true);
        root_node->add_child(trampolineptr);
        trampolineptr->setProperties(lightingShader, texturemetal, zeroPos, MODEL, trampoline, 0.01f, true);
        trampolineptr->trigger = trampolineTrigger;

        root_node->add_child(treeptr);
        treeptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, tree, 0.01f, false);

        root_node->add_child(umbrellaptr);
        umbrellaptr->setProperties(lightingShader, texturekupa, zeroPos, MODEL, umbrella, 0.01f, false);

        root_node->add_child(walkptr);
        walkptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, walk, 0.01f, false);

        root_node->add_child(wallsptr);
        wallsptr->setProperties(lightingShader, texturestone, zeroPos, MODEL, walls, 0.01f, false);
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

        //gravity->updateGravityInNegativeY(cube2, dt);

        
        cube2->update_transform();
        cube3->update_transform();
        root_node->update(Transform(), false);
    }
    void render() {
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        

        root_node->render(true);
        
    }
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void renderQuad()
    {
        if (quadVAO == 0)
        {
            float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // setup plane VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        }
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
    }
    void renderwithShadows()
    {
        // 1. render depth of scene to texture (from light's perspective)
        float near_plane = 0.1f, far_plane = 75.0f;
        float area = 22.0f;
        glm::mat4 orthgonalProjection = glm::ortho(-area, area, -area, area, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(lightPos, cube3->get_transform().m_position, glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix = orthgonalProjection * lightView;
        simpleDepthShader.use();
        simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, shadowMapWidth, shadowMapHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        root_node->renderScene(true, simpleDepthShader);
        //renderScene(simpleDepthShader);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // reset viewport
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 2. render scene as normal using the generated depth/shadow map  
        // --------------------------------------------------------------
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        
        shaderShad.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        shaderShad.setMat4("projection", projection);
        shaderShad.setMat4("view", view);
        // set light uniforms
        shaderShad.setVec3("viewPos", camera.Position);
        shaderShad.setVec3("lightPos", lightPos);
        shaderShad.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        // Make it so the stencil test always passes
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // Enable modifying of the stencil buffer
        //glStencilMask(0xFF);

        root_node->render2(true,depthMap, shaderShad);
        // render Depth map to quad for visual debugging
        // don't delete---------------------------------
        //debugDepthQuad.use();
        //debugDepthQuad.setFloat("near_plane", near_plane);
        //debugDepthQuad.setFloat("far_plane", far_plane);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, depthMap);
        //renderQuad();

    }
    void renderWithOutline() {
        // Make it so only the pixels without the value 1 pass the test
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        // Disable modifying of the stencil buffer
        glStencilMask(0x00);
        // Disable the depth buffer
        glDisable(GL_DEPTH_TEST);

        outlineShader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        outlineShader.setMat4("projection", projection);
        outlineShader.setMat4("view", view);
        //scale
        outlineShader.setFloat("m_scale", 0.13f);

        root_node->renderSceneWithOutline(true, outlineShader);
        glStencilMask(0xFF);
        // Clear stencil buffer
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        // Enable the depth buffer
        glEnable(GL_DEPTH_TEST);
    }

    unsigned int candyCount(PlayerController* player, unsigned int tex1, unsigned int tex2, unsigned int tex3, unsigned int tex4, unsigned int tex5, unsigned int tex6, unsigned int tex7) {
        

        if (player->getCandyCount() >= 6)
            return tex7;
        if (player->getCandyCount() == 5)
            return tex6;
        if (player->getCandyCount() == 4)
            return tex5;
        if (player->getCandyCount() == 3)
            return tex4;
        if (player->getCandyCount() == 2)
            return tex3;
        if (player->getCandyCount() == 1)
            return tex2;
        if (player->getCandyCount() == 0)
            return tex1;
    }
};