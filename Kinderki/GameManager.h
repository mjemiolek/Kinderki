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
#include "Frustum.h"
#include <mmcobj.h>
#include <vector>



//GameManager is responsible for creating and rendering objects, gameplay, game physics
class GameManager {
    public:
    std::shared_ptr<SceneGraphNode> root_node;
    std::shared_ptr<SceneGraphNode> root_water;
    std::shared_ptr<SceneGraphNode> cube1;
    std::shared_ptr<SceneGraphNode> cube2;
    std::shared_ptr<SceneGraphNode> cube3; //player
    std::shared_ptr<SceneGraphNode> ball;
    std::shared_ptr<SceneGraphNode> progressbar;
    std::vector<std::shared_ptr<SceneGraphNode>> collidingObjects;
    std::shared_ptr<GravityManager> gravity;

    std::shared_ptr<SceneGraphNode> aerialrunnwaywholeptr;
    std::shared_ptr<SceneGraphNode> aerialrunnwayseatptr;
    std::shared_ptr<SceneGraphNode> benchesptr;
    std::shared_ptr<SceneGraphNode> floorptr;
    std::shared_ptr<SceneGraphNode> footballstuffptr;
    std::shared_ptr<SceneGraphNode> goalLeftptr;
    std::shared_ptr<SceneGraphNode> goalRightptr;
    std::shared_ptr<SceneGraphNode> sandpitptr;
    std::shared_ptr<SceneGraphNode> sandsptr;
    std::shared_ptr<SceneGraphNode> seesawptr;
    std::shared_ptr<SceneGraphNode> seesawreversepts;
    std::shared_ptr<SceneGraphNode> slideptr;
    std::shared_ptr<SceneGraphNode> swingptr;
    std::shared_ptr<SceneGraphNode> swingseatptr;
    std::shared_ptr<SceneGraphNode> tablesptr;
    std::shared_ptr<SceneGraphNode> trampolineptr;
    std::shared_ptr<SceneGraphNode> treeptr;
    std::shared_ptr<SceneGraphNode> umbrellaptr;
    std::shared_ptr<SceneGraphNode> walkptr;
    std::shared_ptr<SceneGraphNode> wallsptr;
    std::shared_ptr<SceneGraphNode> poolptr;
    std::shared_ptr<SceneGraphNode> poolwaterptr;

    std::shared_ptr<SceneGraphNode> heartptr;
    std::shared_ptr<SceneGraphNode> heartptr2;

    std::shared_ptr<SceneGraphNode> colaptr;
    std::shared_ptr<SceneGraphNode> mentosptr;

    Shader lightingShader = Shader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    //For shadows
    Shader shaderShad = Shader("res/shaders/shadow_mapping.vert", "res/shaders/shadow_mapping.frag");
    unsigned int depthMapFBO, depthMap;
    Shader simpleDepthShader = Shader("res/shaders/shadow_mapping_depth.vert", "res/shaders/shadow_mapping_depth.frag");
    Shader debugDepthQuad = Shader("res/shaders/debug_quad.vert", "res/shaders/debug_quad.frag");
    //For outline
    Shader outlineShader = Shader("res/shaders/outlining.vert", "res/shaders/outlining.frag");
    Shader animShader = Shader("res/shaders/skeletal_animation.vert", "res/shaders/skeletal_animation.frag");
    //For water
    Shader waterShader = Shader("res/shaders/water.vert", "res/shaders/water.frag");

    Shader antialliasingshader = Shader("res/shaders/antialliasing.vert", "res/shaders/antialliasing.frag");


    GameManager() {
        //settings
        glm::vec3 zeroPos(0.0f, 0.0f, 0.0f);
        glm::vec3 floorPos(0.0f, 0.0f, 0.0f);
        glm::vec3 sandPitPos(8.87f, 0.0f, -14.34f);
        glm::vec3 seesawPos(8.0f, 0.68f, -4.5f);
        glm::vec3 ballPos(11.53f, 3.00f, 14.46f);
        glm::vec3 slidePos(22.50f, 0.38f, -14.0f);
        glm::vec3 trampolinePos(29.50f, 0.58f, -14.95f);
        glm::vec3 treePos(34.0f, 5.38f, -18.0f);
        glm::vec3 aerialRunnwayPos(32.87f, 0.82f, -9.91f);
        glm::vec3 aerialRunnwaySeatPos(0.33, 0.1f, 0.0f);
        glm::vec3 swingPos(8.0f, 2.38f, 6.0f);
        glm::vec3 poolPos(-2.0f, 0.0f, 6.0f);
        glm::vec3 poolWaterPos(-2.0f, 0.58f, 6.0f);
        glm::vec3 goalLeftPos(5.5f, 0.0f, 15.5f);
        glm::vec3 goalRightPos(18.5f, 0.0f, 15.5f);
        glm::vec3 wallPosColl1(2.42f, 0.0f, 0.0f);
        glm::vec3 wallPosColl2(20.675f, 0.0f, -20.89f);
        glm::vec3 wallPosColl3(12.1845f, 0.0f, 21.0f);
        glm::vec3 wallPosColl4(21.4975f, 0.0f, 15.823f);
        glm::vec3 wallPosColl5(30.1425f, 0.0f, 11.07f);
        glm::vec3 wallPosColl6(38.455f, 0.0f, -4.68f);

        glm::vec3 heartPos(2.0f, 0.2f, 2.0f);
        glm::vec3 heartPos2(-2.0f, 0.2f, -2.0f);
        glm::vec3 colaPos(5.0f, 3.0f, 0.0f);
        glm::vec3 mentosPos(10.0f, 3.0f, 0.0f);

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
        lightingShader.use();
        lightingShader.setInt("material.diffuse", 0);
        lightingShader.setInt("material.specular", 64);
        //lightingShader.setVec3("light.position", lightPos);

        //Initializing water shader
        waterShader.use();
        glUniform1i(glGetUniformLocation(waterShader.ID, "refractionTexture"), 0);
        glUniform1i(glGetUniformLocation(waterShader.ID, "reflectionTexture"), 1);

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

        Model aerialrunnwaywhole("res/models/level/aerialrunnway_whole.obj");
        Model aerialrunnwayseat("res/models/level/aerialrunnway_seat.obj");


        Model benches("res/models/level/benches.obj");
        Model floor("res/models/level/floor.obj",256.0f,256.0f);
        Model footballstuff("res/models/level/footballstuff.obj");
        Model goalLeft("res/models/level/bramkahp.obj");
        Model goalRight("res/models/level/bramkahp.obj");
        Model sandpit("res/models/level/sandpit.obj");
        Model sands("res/models/level/sands.obj");
        Model seesaw("res/models/level/seesaw.obj");
        Model seesawrevers("res/models/level/seesawreverse.obj");
        Model slide("res/models/level/slide.obj");
        Model swing("res/models/level/swing.obj");
        Model swingseat("res/models/level/swingseat.obj");
        Model tables("res/models/level/tables.obj");
        Model trampoline("res/models/level/trampoline.obj");
        Model tree("res/models/level/tree.obj");
        Model umbrella("res/models/level/umbrella.obj");
        Model walk("res/models/level/walk.obj");
        Model walls("res/models/level/walls.obj",16.0f,1.0f);
        Model pool("res/models/level/pool.obj");
        Model poolwater("res/models/level/poolwater.obj");


        Model heart("res/models/movable/mentos.obj");
        Model cola("res/models/movable/cola.obj");
        Model mentos("res/models/movable/mentos.obj");

        //Model postac_test("res/models/main_character.obj");
        //Model postac_test("res/models/postac_test_kolejny.obj");
        Model postac_test("res/models/postac_test_v4.obj");




        unsigned int texturekupa = loadTexture("res/textures/win.png");
        unsigned int texturegrass = loadTexture("res/textures/grasstexture.png");
        unsigned int texturemetal = loadTexture("res/textures/metaltexture.png");
        unsigned int texturesand = loadTexture("res/textures/sandtexture.png");
        unsigned int textureplanks = loadTexture("res/textures/planks.png");
        unsigned int textureshrek = loadTexture("res/textures/shrek.png");
        unsigned int texturestone = loadTexture("res/textures/stone.jpg");
        unsigned int texturewater = loadTexture("res/textures/water.png");


        unsigned int diffuseMap = loadTexture("res/textures/diff.jpg");
        unsigned int specularMap = loadTexture("res/textures/spec.jpg");

        //unsigned int texture_postac_test = loadTexture("res/textures/oko_tekstura_test2.png");
        unsigned int texture_postac_test = loadTexture("res/textures/baking_5.png");

        
        unsigned int texaerial = loadTexture("res/textures/models/texaerial.png");
        unsigned int texballkeep = loadTexture("res/textures/models/texballkeep.png");
        unsigned int texsandpit = loadTexture("res/textures/models/texsandpit.png");
        unsigned int texseesaw = loadTexture("res/textures/models/texseesaw.png");
        unsigned int texslide = loadTexture("res/textures/models/texslide.png");
        unsigned int texswing = loadTexture("res/textures/models/texswing.png");
        unsigned int textrampoline = loadTexture("res/textures/models/textrampoline.png");
        unsigned int textree = loadTexture("res/textures/models/textree.png");

        unsigned int texcola = loadTexture("res/textures/models/texcola.png");
        unsigned int texbucketpink = loadTexture("res/textures/models/texbucketpink.png");
        //unsigned int texbucketpurple = loadTexture("res/textures/models/texbucketpurple.png");
        //unsigned int texbucketyellow = loadTexture("res/textures/models/texbucketyellow.png");
        
        

        //Allocating storage for the objects
        root_node = std::make_shared<SceneGraphNode>();
        root_water = std::make_shared<SceneGraphNode>();
        cube1 = std::make_shared<SceneGraphNode>();
        cube2 = std::make_shared<SceneGraphNode>();
        cube3 = std::make_shared<SceneGraphNode>();
        ball = std::make_shared<SceneGraphNode>();

        aerialrunnwaywholeptr = std::make_shared<SceneGraphNode>();
        aerialrunnwayseatptr = std::make_shared<SceneGraphNode>();

        benchesptr = std::make_shared<SceneGraphNode>();
        floorptr = std::make_shared<SceneGraphNode>();
        footballstuffptr = std::make_shared<SceneGraphNode>();
        goalLeftptr = std::make_shared<SceneGraphNode>();
        goalRightptr = std::make_shared<SceneGraphNode>();
        sandpitptr = std::make_shared<SceneGraphNode>();
        sandsptr = std::make_shared<SceneGraphNode>();
        seesawptr = std::make_shared<SceneGraphNode>();
        seesawreversepts = std::make_shared<SceneGraphNode>();
        slideptr = std::make_shared<SceneGraphNode>();
        swingptr = std::make_shared<SceneGraphNode>();
        swingseatptr = std::make_shared<SceneGraphNode>();
        tablesptr = std::make_shared<SceneGraphNode>();
        trampolineptr = std::make_shared<SceneGraphNode>();
        treeptr = std::make_shared<SceneGraphNode>();
        umbrellaptr = std::make_shared<SceneGraphNode>();
        walkptr = std::make_shared<SceneGraphNode>();
        wallsptr = std::make_shared<SceneGraphNode>();
        poolptr = std::make_shared<SceneGraphNode>();
        poolwaterptr = std::make_shared<SceneGraphNode>();


        heartptr = std::make_shared<SceneGraphNode>();
        heartptr2 = std::make_shared<SceneGraphNode>();
        colaptr = std::make_shared<SceneGraphNode>();
        mentosptr = std::make_shared<SceneGraphNode>();

        collidingObjects.insert(collidingObjects.end(),{
        cube1,cube2,cube3, floorptr, ball,wallsptr,heartptr,heartptr2,colaptr, mentosptr,
        trampolineptr, goalLeftptr, goalRightptr, swingptr, swingseatptr });
        glm::vec3 boxColRange(2.5f, 0.5f, 0.7f);
        glm::vec3 triggerRange(0.80f, 0.80f, 0.80f);
        glm::vec3 floorColRange(300.0f, 1.0f, 300.0f);

        ////cube do testow
        //root_node->add_child(cube1);
        //Collider cube1Collider(glm::vec3(0.38f, 0.38f, 0.38f), false, cubePositions[0],false);
        //cube1->setProperties(lightingShader, texturestone, cubePositions[0], MODEL, box, 0.15f,true, cube1Collider);
        ////test
        //Collider cube1ExtraCollider(boxColRange, false,glm::vec3(-0.5f, 2.0f, 5.5f), false);
        //cube1->additionalColliders.push_back(cube1ExtraCollider);
        ////test

        //cube do testu AI
        root_node->add_child(cube2);
        Collider cube2Collider(boxColRange, false, cubePositions[2], false);
        cube2->setProperties(lightingShader, texturekupa, cubePositions[2], MODEL, box, 0.15f, true, cube2Collider);
        
        //gracz
        root_node->add_child(cube3);
        Collider cube3Collider(0.34f, false, cubePositions[4],true);
        //cube3->setProperties(lightingShader, texturekupa, cubePositions[4], MODEL, box, 0.15f, true, cube3Collider);
        cube3->setProperties(lightingShader, texture_postac_test, cubePositions[4], MODEL, postac_test, 1.0f, true, cube3Collider);

        //pilka
        root_node->add_child(ball);
        Collider ballCollider(0.28f, false, glm::vec3(0.0f, 2.0f, -2.0f), true);
        ball->setProperties(lightingShader, textureshrek, glm::vec3(0.0f, 2.0f, -2.0f),MODEL,sphere,0.03f,true,ballCollider);



        //tyrolka
        Collider aerialrunnwayTrigger(0.8f, false, aerialRunnwayPos, true);
        root_node->add_child(aerialrunnwaywholeptr);
        aerialrunnwaywholeptr->m_transform.y_rotation_angle = 180;
        aerialrunnwaywholeptr->setProperties(lightingShader, texaerial, aerialRunnwayPos, MODEL, aerialrunnwaywhole, 1.00f,false);
        aerialrunnwaywholeptr->trigger = aerialrunnwayTrigger;

        root_node->add_child(aerialrunnwayseatptr);
        aerialrunnwayseatptr->setProperties(lightingShader, texturemetal, aerialRunnwayPos+aerialRunnwaySeatPos, MODEL, aerialrunnwayseat, 1.00f, false);
        //aerialrunnwayseatptr->trigger = aerialrunnwayTrigger;

        //³awki
        root_node->add_child(benchesptr);
        benchesptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, benches, 0.01f, false);

        ////piaski
        //root_node->add_child(sandsptr);
        //sandsptr->setProperties(lightingShader, texturesand, zeroPos, MODEL, sands, 0.01f, false);

        ////krawezniki?
        //root_node->add_child(walkptr);
        //walkptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, walk, 0.01f, false);

        //podloga
        root_node->add_child(floorptr);
        Collider floorCol(floorColRange, false, glm::vec3(15.0f, -1.2f, 0.0f), false);
        floorptr->setProperties(lightingShader, texturegrass, floorPos, MODEL, floor, 0.05f, false, floorCol);


        //Bramki
        root_node->add_child(goalLeftptr);
        //tyl
        glm::vec3 gLCP = goalLeftPos; //Goal Left Collider Position
        gLCP.x -= 1.6f;
        Collider goalLeftCollider(glm::vec3(0.015f, 3.0f, 2.95f), false, gLCP, false);
        gLCP.x += 1.4f;
        goalLeftptr->setProperties(lightingShader, texballkeep, goalLeftPos, MODEL, goalLeft, 0.14f, false, goalLeftCollider);
        goalLeftptr->setRotation(0.0f, 90.0f, 0.0f);
        //gora
        gLCP.z -= 3.0f;
        Collider goalLeftColliderUp(glm::vec3(0.9f, 3.0f, 0.015f), false, gLCP, false);
        gLCP.z += 3.0f;
        goalLeftptr->additionalColliders.push_back(goalLeftColliderUp);
        //dol
        gLCP.z += 3.0f;
        Collider goalLeftColliderDown(glm::vec3(0.9f, 3.0f, 0.015f), false, gLCP, false);
        goalLeftptr->additionalColliders.push_back(goalLeftColliderDown);


        root_node->add_child(goalRightptr);
        //tyl
        glm::vec3 gRCP = goalRightPos; //Goal Right Collider Position
        gRCP.x += 1.6f;
        Collider goalRightCollider(glm::vec3(0.015f, 3.0f, 2.95f), false, gRCP, false);
        gRCP.x -= 1.4f;
        goalRightptr->setProperties(lightingShader, texballkeep, goalRightPos, MODEL, goalRight, 0.14f, false, goalRightCollider);
        goalRightptr->setRotation(0.0f, -90.0f, 0.0f);
        //gora
        gRCP.z -= 3.0f;
        Collider goalRightColliderUp(glm::vec3(0.9f, 3.0f, 0.015f), false, gRCP, false);
        gRCP.z += 3.0f;
        goalRightptr->additionalColliders.push_back(goalRightColliderUp);
        //dol
        gRCP.z += 3.0f;
        Collider goalRightColliderDown(glm::vec3(0.9f, 3.0f, 0.015f), false, gRCP, false);
        goalLeftptr->additionalColliders.push_back(goalRightColliderDown);


        //piaskownica
        root_node->add_child(sandpitptr);
        Collider sandPitTrigger(glm::vec3(2.43f, 5.1f, 2.43f), false, sandPitPos, true);
        sandpitptr->setProperties(lightingShader, texsandpit, zeroPos, MODEL, sandpit, 0.01f, false);
        sandpitptr->trigger = sandPitTrigger;


        //hustawka wazka
        Collider seesawTrigger(0.5f, false, seesawPos, true);
        root_node->add_child(seesawptr);
        seesawptr->setProperties(lightingShader, texseesaw, seesawPos, MODEL, seesaw, 0.2f, true);
        seesawptr->trigger = seesawTrigger;


        //root_node->add_child(seesawreversepts);
        //seesawreversepts->setProperties(lightingShader, texturemetal, zeroPos, MODEL, seesawreverse, 0.01f);


        //zjezdzalnia
        Collider slideTrigger(1.2f, false, slidePos, true);
        root_node->add_child(slideptr);
        slideptr->setProperties(lightingShader, texslide, slidePos, MODEL, slide, 0.035f, true);
        slideptr->setRotation(0.0f, -90.0f, 0.0f);
        slideptr->trigger = slideTrigger;


        //hustawka
        glm::vec3 swingTrigPos = swingPos;
        swingTrigPos.y -= 1.5f;
        Collider swingTrigger(glm::vec3(0.30f, 0.30f, 0.30f), false, swingTrigPos, true);
        root_node->add_child(swingptr);
        glm::vec3 swingColPos = swingPos;
        swingColPos.y -= 2.0f;
        //siedzenie
        Collider swingCollider(glm::vec3(0.38f, 0.38f, 0.38f), false, swingColPos, false);
        swingptr->setProperties(lightingShader, texswing, swingPos, MODEL, swing, 0.02f, true, swingCollider);
        swingptr->trigger = swingTrigger;
        swingptr->setRotation(0.0f, 180.0f, 0.0f);
        //lewo gora
        swingColPos.z -= 1.45f;
        swingColPos.x -= 1.2f;
        Collider sCLU(glm::vec3(0.15f, 2.5f, 0.03f), false, swingColPos, false); //swing collider left up
        swingptr->additionalColliders.push_back(sCLU);
        //prawo gora
        swingColPos.x += 2.4f;
        Collider sCRU(glm::vec3(0.15f, 2.5f, 0.03f), false, swingColPos, false);
        swingptr->additionalColliders.push_back(sCRU);
        //prawo dol
        swingColPos.z += 2.9f;
        Collider sCRD(glm::vec3(0.15f, 2.5f, 0.03f), false, swingColPos, false);
        swingptr->additionalColliders.push_back(sCRD);
        //lewo dol
        swingColPos.x -= 2.4f;
        Collider sCLD(glm::vec3(0.15f, 2.5f, 0.03f), false, swingColPos, false);
        swingptr->additionalColliders.push_back(sCLD);


        //seat
        root_node->add_child(swingseatptr);
        glm::vec3 swingSeatPos = swingPos;
        swingSeatPos.y += 1.40f;
        swingseatptr->setProperties(lightingShader, texturemetal, swingSeatPos, MODEL, swingseat, 0.02f, true);
        swingseatptr->trigger = swingTrigger;
        swingseatptr->setRotation(0.0f, 180.0f, 0.0f);


        //stoly
        root_node->add_child(tablesptr);
        tablesptr->setProperties(lightingShader, textureplanks, zeroPos, MODEL, tables, 0.01f, false);



        //trampolina
        glm::vec3 trampolineColliderPos = trampolinePos;
        trampolineColliderPos.y -= 0.9f;
        Collider trampolineTrigger(glm::vec3(1.0f, 0.6f, 1.0f), false, trampolinePos, true);
        //gora
        float q = 1.10f;
        trampolineColliderPos.z -= q;
        Collider trampolineCollider1(glm::vec3(0.9f, 1.1f, 0.1f), false, trampolineColliderPos, false);
        trampolineColliderPos.z += q;
        root_node->add_child(trampolineptr);
        trampolineptr->setProperties(lightingShader, textrampoline, trampolinePos, MODEL, trampoline, 0.006f, true, trampolineCollider1, trampolineTrigger);
        //trampolineptr->trigger = trampolineTrigger;
        //dol
        trampolineColliderPos.z += q;
        Collider trampolineCollider2(glm::vec3(0.9f, 1.1f, 0.1f), false, trampolineColliderPos, false);
        trampolineColliderPos.z -= q;
        trampolineptr->additionalColliders.push_back(trampolineCollider2);
        //lewo
        trampolineColliderPos.x -= q;
        Collider trampolineCollider3(glm::vec3(0.1f, 1.1f, 0.9f), false, trampolineColliderPos, false);
        trampolineColliderPos.x += q;
        trampolineptr->additionalColliders.push_back(trampolineCollider3);
        //prawo
        trampolineColliderPos.x += q;
        Collider trampolineCollider4(glm::vec3(0.1f, 1.1f, 0.9f), false, trampolineColliderPos, false);
        trampolineptr->additionalColliders.push_back(trampolineCollider4);



        //drzewo
        root_node->add_child(treeptr);
        treeptr->setProperties(lightingShader, textree, treePos, MODEL, tree, 0.7f, false);
        treeptr->setRotation(0.0f, 200.0f, 0.0f);

        //parasol
        root_node->add_child(umbrellaptr);
        umbrellaptr->setProperties(lightingShader, texturekupa, zeroPos, MODEL, umbrella, 0.01f, false);

        //basen
        root_node->add_child(poolptr);
        poolptr->setProperties(lightingShader, texturemetal, poolPos, MODEL, pool, 0.07f, false);
        root_water->add_child(poolwaterptr);
        poolwaterptr->setProperties(waterShader, texturewater, poolWaterPos, MODEL, poolwater, 0.07f, false);

        //sciany
        Collider wallColl1(glm::vec3(0.05f, 3.0f, 21.0f), false, wallPosColl1, true);
        Collider wallColl2(glm::vec3(17.825f, 3.0f, 0.05f), false, wallPosColl2, true);
        Collider wallColl3(glm::vec3(9.3145f, 3.0f, 0.05f), false, wallPosColl3, true);
        Collider wallColl4(glm::vec3(0.05f, 3.0f, 4.747f), false, wallPosColl4, true);
        Collider wallColl5(glm::vec3(8.3125f, 3.0f, 0.05f), false, wallPosColl5, true);
        Collider wallColl6(glm::vec3(0.05f, 3.0f, 15.75f), false, wallPosColl6, true);
        root_node->add_child(wallsptr);
        wallsptr->setProperties(lightingShader, texturestone, zeroPos, MODEL, walls, 0.01f, false);
        wallsptr->additionalColliders.push_back(wallColl1);
        wallsptr->additionalColliders.push_back(wallColl2);
        wallsptr->additionalColliders.push_back(wallColl3);
        wallsptr->additionalColliders.push_back(wallColl4);
        wallsptr->additionalColliders.push_back(wallColl5);
        wallsptr->additionalColliders.push_back(wallColl6);


        Collider heartCollider(glm::vec3(0.005f, 1.0f, 0.005f), false, heartPos, true);
        Collider heartTrigger(glm::vec3(0.25f, 2.0f, 0.25f), true, heartPos, true);
        Collider heartTrigger2(glm::vec3(0.25f, 2.0f, 0.25f), true, heartPos2, true);
        Collider colaTrigger(glm::vec3(0.25f, 2.0f, 0.25f), true, colaPos, true);
        Collider mentosTrigger(glm::vec3(0.25f, 2.0f, 0.25f), true, colaPos, true);
        
        root_node->add_child(heartptr);
        heartptr->setProperties(lightingShader, texturekupa, heartPos, MODEL, postac_test, 1.0f, true);
        heartptr->trigger = heartTrigger;

        root_node->add_child(heartptr2);
        heartptr2->setProperties(lightingShader, textureplanks, heartPos2, MODEL, postac_test, 1.0f, true);
        heartptr2->trigger = heartTrigger2;


        root_node->add_child(colaptr);
        colaptr->setProperties(lightingShader, texcola, colaPos, MODEL, cola, 0.01f, true);
        colaptr->trigger = colaTrigger;

        root_node->add_child(mentosptr);
        mentosptr->setProperties(lightingShader, texturekupa, mentosPos, MODEL, mentos, 1.0f, true);
        mentosptr->trigger = mentosTrigger;

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
        root_water->update(Transform(), false);
    }
    void render(glm::vec4 clip,int width,int height) {
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        

        root_node->render(true, clip);
        
    }
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    void renderQuad() //for debbuging
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
    void renderwithShadows(int mode)
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
        //Frustrum
        const Frustum camFrustum = createFrustumFromCamera(camera, (float)SCR_WIDTH / (float)SCR_HEIGHT, glm::radians(camera.Zoom), 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();
        shaderShad.setMat4("projection", projection);
        shaderShad.setMat4("view", view);
        // set light uniforms
        shaderShad.setVec3("viewPos", camera.Position);
        shaderShad.setVec3("lightPos", lightPos);
        shaderShad.setMat4("lightSpaceMatrix", lightSpaceMatrix);
        shaderShad.setInt("mode", mode);

        // Make it so the stencil test always passes
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // Enable modifying of the stencil buffer
        //glStencilMask(0xFF);

        // draw our scene graph
        unsigned int total = 0, display = 0;
        root_node->render2(true,depthMap, shaderShad, camFrustum,display,total);
        //std::cout << "Total process in CPU : " << total << " / Total send to GPU : " << display << std::endl; //debugging

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

    void renderWater(unsigned int refractiontexture, unsigned int reflectiontexture)
    {
        root_water->renderWater(true, refractiontexture, reflectiontexture);
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