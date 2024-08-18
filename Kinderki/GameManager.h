#pragma once
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <cmath>

#include <irrKlang/ik_ISound.h>

#include "Sound.h"
#include "Shader.h"
#include "Camera.h"
#include "ModelAnimation.h"
#include "SceneGraph.h"
#include "PlayerController.h"
#include "Text.h"
#include "Skybox.h"
#include "Settings.h"
#include "Collider.h"
#include "GravityManager.h"
#include "Frustum.h"
#include "Animator.h"
#include <mmcobj.h>
#include <vector>
#include "TutorialState.h"



//GameManager is responsible for creating and rendering objects, gameplay, game physics
class GameManager {
    public:
    std::shared_ptr<SceneGraphNode> root_node;
    std::shared_ptr<SceneGraphNode> root_water;
    std::shared_ptr<SceneGraphNode> cube1;
    std::shared_ptr<SceneGraphNode> cube2;
    std::shared_ptr<SceneGraphNode> cube3; //player
    std::shared_ptr<SceneGraphNode> cubeKid2; 
    std::shared_ptr<SceneGraphNode> cubeKid3; 
    std::shared_ptr<SceneGraphNode> cubeKid4; 
    std::shared_ptr<SceneGraphNode> cubeKid5; 
    std::shared_ptr<SceneGraphNode> ball;
    std::shared_ptr<SceneGraphNode> progressbar;
    std::vector<std::shared_ptr<SceneGraphNode>> collidingObjects;
    std::vector<Collider> escapeTriggers;
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
    std::shared_ptr<SceneGraphNode> seesawbaseptr;
    std::shared_ptr<SceneGraphNode> slideptr;
    std::shared_ptr<SceneGraphNode> swingptr;
    std::shared_ptr<SceneGraphNode> swingseatptr;
    std::shared_ptr<SceneGraphNode> tablesptr;
    std::shared_ptr<SceneGraphNode> trampolineptr;
    std::shared_ptr<SceneGraphNode> treeptr;
    std::shared_ptr<SceneGraphNode> tree2ptr;
    std::shared_ptr<SceneGraphNode> umbrellaptr;
    std::shared_ptr<SceneGraphNode> walkptr;
    std::shared_ptr<SceneGraphNode> wallsptr;
    std::shared_ptr<SceneGraphNode> damagedwallptr;
    std::shared_ptr<SceneGraphNode> poolptr;
    std::shared_ptr<SceneGraphNode> poolwaterptr;
    std::shared_ptr<SceneGraphNode> tabptr;
    float waterHeight = 0.58f;


    std::shared_ptr<SceneGraphNode> temp;


    std::shared_ptr<SceneGraphNode> heartptr;
    std::shared_ptr<SceneGraphNode> heartptr2;

    std::shared_ptr<SceneGraphNode> colaptr;
    std::shared_ptr<SceneGraphNode> mentosptr;
    std::shared_ptr<SceneGraphNode> candyCane1ptr;
    std::shared_ptr<SceneGraphNode> candyCane2ptr;
    std::shared_ptr<SceneGraphNode> candyCane3ptr;
    std::shared_ptr<SceneGraphNode> candyCane4ptr;
    std::shared_ptr<SceneGraphNode> candyCane5ptr;
    std::shared_ptr<SceneGraphNode> candyCane6ptr;


    std::shared_ptr<SceneGraphNode> treecircle1;
    std::shared_ptr<SceneGraphNode> treecircle2;
    std::shared_ptr<SceneGraphNode> trampolinecircle;



    std::shared_ptr<SceneGraphNode> bucketblackptr;
    std::shared_ptr<SceneGraphNode> bucketpinkptr;
    std::shared_ptr<SceneGraphNode> bucketredptr;
    std::shared_ptr<SceneGraphNode> hammerptr;
    std::shared_ptr<SceneGraphNode> lightballptr;
    std::shared_ptr<SceneGraphNode> mentosToAnimationptr;
    std::shared_ptr<SceneGraphNode> colaToAnimationptr;

    std::shared_ptr<TutorialState> tutorialState;

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
    Shader skeletalDepth = Shader("res/shaders/skeletal_depth.vert", "res/shaders/skeletal_depth.frag");

    std::shared_ptr<PlayerController> player;
    glm::vec3 playerPos = glm::vec3(27.0f, 0.2f, 9.17); //Player position
    //glm::vec3 playerPos = glm::vec3(15.0f, 0.0f, -11.f); //Player position
    int playerWins = 0;
    int timer = 0;
    bool already = false;
    bool isSoundPlaying = false;


    // animacje
    Model postac_test = Model("res/models/main_character_TEST_v15.fbx");
    Animation anim1 = Animation("res/animations/main_character_walking.fbx", &postac_test);
    Animation anim2 = Animation("res/animations/main_character_jumping.fbx", &postac_test);
    Animation anim3 = Animation("res/animations/main_character_idle.fbx", &postac_test);
    Animation anim4 = Animation("res/animations/main_character_lifting.fbx", &postac_test);
    Animation anim5 = Animation("res/animations/main_character_zombie_walking.fbx", &postac_test);
    Animator animatorMainCharacter = Animator(&anim1);

    Model animatedBucket = Model("res/models/bucket.fbx");
    Animation aniamtionBucket = Animation("res/animations/bucket_animation.fbx", &animatedBucket);
    Animator animatorBucket = Animator(&aniamtionBucket);

    Model kidSandPit = Model("res/models/main_character_TEST_v15.fbx");
    Animation animationKidSandPit = Animation("res/animations/first_character_bucket_animation.fbx", &kidSandPit);
    Animator animatorKidSandPit = Animator(&animationKidSandPit);

    Model animatedHammer = Model("res/models/hammer.fbx");
    Animation animationHammer = Animation("res/animations/hammer_animation.fbx", &animatedHammer);
    Animator animatorHammer = Animator(&animationHammer);

    Animation animationHammerIdle = Animation("res/animations/hammer_animation_idle.fbx", &animatedHammer);

    Model kidSeesaw = Model("res/models/second_character.fbx");
    Animation animationKidSeesaw = Animation("res/animations/second_character_hammer.fbx", &kidSeesaw);
    Animator animatorKidSeesaw = Animator(&animationKidSeesaw);

    Animation animationKidSeesawIdle = Animation("res/animations/second_character_hammer_idle.fbx", &kidSeesaw);


    Model animatedLightBall = Model("res/models/light.fbx");
    Animation animationLightBallIdle = Animation("res/animations/light_animation_idle.fbx", &animatedLightBall);
    Animation animationLightBall = Animation("res/animations/light_animation.fbx", &animatedLightBall);
    Animator animatorLightBall = Animator(&animationLightBall);

    Animation animationHustawkerIdle = Animation("res/animations/first_character_kamehameha_idle.fbx", &postac_test);
    Animation animationHustawker = Animation("res/animations/first_character_kamehameha.fbx", &postac_test);
    Animator animatorHustawker = Animator(&animationHustawker);

    Animation animationKidMentosCola = Animation("res/animations/first_character_mentos_cola.fbx", &postac_test);
    Animator animatorKidMentosCola = Animator(&animationKidMentosCola);

    Model animatedMentos = Model("res/models/mentos.fbx");
    Animation animationMentos = Animation("res/animations/mentos_animation.fbx", &animatedMentos);
    Animator animatorMentos = Animator(&animationMentos);

    Model animatedCola = Model("res/models/cola.fbx");
    Animation animationCola = Animation("res/animations/cola_animation.fbx", &animatedCola);
    Animator animatorCola = Animator(&animationCola);

    //to checkWin()
    unsigned int ct;
    unsigned int st;
    bool ifWin = false;
    int ESC = false;
    bool piaskownicaMinusUcieczka = false;

    GameManager() {
        //settings
        glm::vec3 zeroPos(0.0f, 0.0f, 0.0f);
        glm::vec3 walkPos(0.0f, 0.0f, 0.0f);
        glm::vec3 floorPos(0.0f, 0.0f, 0.0f);
        glm::vec3 sandPitPos(8.87f, 0.0f, -14.34f);
        glm::vec3 seesawPos(8.0f, 0.8f, -4.5f);
        glm::vec3 ballPos(25.5f, 2.5f, -5.0f);
        glm::vec3 slidePos(21.00f, 0.10f, -14.0f);
        glm::vec3 trampolinePos(20.50f, 0.58f, -7.5f);
        glm::vec3 treePos(23.0f, 0.0f, -13.f);
        glm::vec3 tree2Pos(14.0f, 0.0f, -13.f);
        //glm::vec3 treePos(30.0f, 0.0f, -18.0f);
        glm::vec3 aerialRunnwayPos(33.0f, 0.0f, -2.5f);
        glm::vec3 aerialRunnwaySeatPos(0.05, 3.15f, -7.5f);
        glm::vec3 aerialRunnwayTrigerPos(33.0f, -1.5f, -10.0f);
        glm::vec3 aerialRunnwayLinerTrigerPos(36.5f, 4.0f, 5.5f);
        glm::vec3 swingPos(8.0f, 2.38f, 6.0f);
        glm::vec3 poolPos(15.0f, 0.0f, -23.f);
        glm::vec3 poolWaterPos(poolPos.x +0.05f, waterHeight, poolPos.z);
        glm::vec3 goalLeftPos(5.5f, 0.0f, 15.5f);
        glm::vec3 goalRightPos(18.5f, 0.0f, 15.5f);
        glm::vec3 wallPosColl1(2.42f, 0.0f, 0.0f); // left
        glm::vec3 wallPosColl2(20.675f, 0.0f, -21.0f); //up
        glm::vec3 wallPosColl3(12.1845f, 0.0f, 21.0f); //down
        glm::vec3 wallPosColl4(21.5f, 0.0f, 15.8f);
        glm::vec3 wallPosColl5(30.3f, 0.0f, 11.07f);
        glm::vec3 wallPosColl6(38.6f, 0.0f, -4.68f); //right
        glm::vec3 damagedwallPos(21.0f, 0.1f, 20.5f);


        glm::vec3 tabPos(38.25f, 3.5f, 5.75f);


        glm::vec3 tempPos(0.0f, 0.0f, 0.0f);

        glm::vec3 heartPos(12.0f, 0.2f, 2.0f);
        glm::vec3 heartPos2(7.0f, 0.0f, -9.6f);   //dziala jako lopatka
        glm::vec3 colaPos(37.0f, 0.0f, -9.0f);
        glm::vec3 mentosPos(29.5f, 2.0f, -2.69f);

        glm::vec3 candyCane1Pos(31.0f, 12.0f, -12.0f);  //tree
        glm::vec3 candyCane2Pos(21.69f, 5.f, -10.25f);    //treelow
        glm::vec3 candyCane3Pos(5.0f, 0.5f, 19.0f);     //behind goal
        glm::vec3 candyCane4Pos(34.5f, 0.5f, -12.0f);   //behind aerial
        glm::vec3 candyCane5Pos(3.5f, 1.0f, 0.0f);      //on bench
        glm::vec3 candyCane6Pos(33.0f, 5.0f, 2.69f);     //on aerial


        glm::vec3 bucketBlackPos(25.0f, 0.1f, -8.0f); //not used
        glm::vec3 bucketPinkPos(30.0f, 0.1f, -8.0f);  //not used
        glm::vec3 bucketRedPos(10.0f, 0.0f, -11.0f);

        glm::vec3 cubePositions[] = {
        glm::vec3(-0.5f, 2.0f,  3.5f),      //0
        glm::vec3(2.0f,  2.0f, -15.0f),     //1
        glm::vec3(11.25f, 0.10f, -4.4f),      //2
        glm::vec3(12.0f, 0.0f, -16.0f),     //3  
        glm::vec3(13.0f, 0.0f, -13.0f), //Player position
        glm::vec3(0.0f,  2.0f, 0.0f),       //5
        glm::vec3(1.3f, 2.0f, -2.5f),       //6
        glm::vec3(1.5f,  2.0f, -2.5f),      //7
        glm::vec3(1.5f,  2.0f, -1.5f),      //8
        glm::vec3(-1.3f,  2.0f, -1.5f),     //9
        glm::vec3(8.87f,  0.10f, -14.34f),  //10
        glm::vec3(20.5f, 0.0f, 12.5f),      //11
        glm::vec3(10.0f,  0.10f, 6.0f),     //12
        glm::vec3(30.56f,  0.10f, -7.50f)  //13
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
        glUniform1i(glGetUniformLocation(waterShader.ID, "dudvMap"), 2);
        glUniform1i(glGetUniformLocation(waterShader.ID, "normalMap"), 3);


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

        Model tab("res/models/level/tab.obj");
        Model model0("res/models/level/model0.obj");

        Model aerialrunnwaywhole("res/models/level/aerialrunnway_whole.obj");
        Model aerialrunnwaywholeOut("res/models/outline/aerialrunnway_wholeOutline.obj");

        Model aerialrunnwayseat("res/models/level/aerialrunnway_seat.obj");
        Model aerialrunnwayseatOut("res/models/outline/aerialrunnway_seatOutline.obj");

        Model benches("res/models/level/benches1.obj");
        Model floor("res/models/level/floor.obj",256.0f,256.0f);
        Model goalLeft("res/models/level/bramkahp.obj");
        Model goalRight("res/models/level/bramkahp.obj");

        Model sandpit("res/models/level/sandpit.obj");
        Model sandpitOut("res/models/outline/sandPitOutline.obj");

        Model sands("res/models/level/sands.obj");
        Model seesaw("res/models/level/seesaw.obj");
        Model seesawOut("res/models/outline/seesawOutline.obj");

        Model seesawBase("res/models/level/seesawBase.obj");
        Model seesawBaseOut("res/models/outline/seesawBaseOutline.obj");

        Model slide("res/models/level/slide.obj");
        Model slideOut("res/models/outline/slideOutline.obj");

        Model swing("res/models/level/swing.obj");
        Model swingOut("res/models/outline/swingOutline.obj");

        Model swingseat("res/models/level/swingseat.obj");
        Model swingseatOut("res/models/outline/swingseatOutline.obj");

        Model tables("res/models/level/tables.obj");
        Model trampoline("res/models/level/trampoline.obj");
        Model trampolineOut("res/models/outline/trampolineOutline.obj");

        Model tree("res/models/level/tree.obj");
        Model tree2("res/models/level/tree2full.obj");
        Model umbrella("res/models/level/umbrella.obj");
        Model walk("res/models/level/walk.obj");


        Model circle("res/models/level/circle.obj");
        Model lcircle("res/models/level/lcircle.obj");



        Model pool("res/models/level/pool.obj");
        Model poolwater("res/models/level/poolwater.obj");

        Model walls("res/models/level/ogrodzenie.obj");
        Model damagedwall("res/models/level/dziura_ogrodzenie.obj");


        Model heart("res/models/movable/mentos.obj");
        Model cola("res/models/movable/cola.obj");
        Model candyCane("res/models/movable/candyCane.obj");
        Model colaOut("res/models/outline/colaOutline.obj");

        Model mentos("res/models/movable/mentos.obj");
        Model mentosOut("res/models/outline/mentosOutline.obj");

        Model shovel("res/models/movable/lopata.obj");
        Model shovelOut("res/models/outline/showelOutline.obj");

        Model bucket("res/models/movable/wiadro.obj");
        Model bucketOut("res/models/outline/wiadroOutline.obj");

        //Model postac_test("res/models/main_character.obj");
        //Model postac_test("res/models/postac_test_kolejny.obj");
        //Model postac_test("res/models/postac_test_v4.obj");

        Model fatKid("res/models/second_character.fbx");


        unsigned int texturewin10 = loadTexture("res/textures/win.png");
        unsigned int texturegrass = loadTexture("res/textures/grasstexture.png");
        unsigned int texturemetal = loadTexture("res/textures/metaltexture.png");
        unsigned int texturesand = loadTexture("res/textures/sandtexture.png");
        unsigned int textureplanks = loadTexture("res/textures/planks.png");
        unsigned int textureshrek = loadTexture("res/textures/shrek.png");
        unsigned int texturestone = loadTexture("res/textures/stone.jpg");
        unsigned int texturewater = loadTexture("res/textures/water/water.png");

        unsigned int texturewall = loadTexture("res/textures/models/ogrodzenie.png");
        unsigned int texturedamagedwall = loadTexture("res/textures/models/dziura_ogrodzenie.png");


        unsigned int diffuseMap = loadTexture("res/textures/diff.jpg");
        unsigned int specularMap = loadTexture("res/textures/spec.jpg");

        //unsigned int texture_postac_test = loadTexture("res/textures/oko_tekstura_test2.png");
        unsigned int texture_postac_test = loadTexture("res/textures/main_character_texture.png");
        unsigned int kidSandPitTexture = loadTexture("res/textures/kids/character_1_texture_v1.png");
        unsigned int kid3texture = loadTexture("res/textures/kids/character_1_texture_v2.png");
        unsigned int kid4texture = loadTexture("res/textures/kids/character_1_texture_v3.png");
        unsigned int kid5texture = loadTexture("res/textures/kids/character_1_texture_v4.png");
        unsigned int fatkidtexture = loadTexture("res/textures/kids/character_2_texture_v1.png");
        unsigned int lighttexture = loadTexture("res/textures/models/light_texture.png");

        unsigned int hammertexture = loadTexture("res/textures/models/hammer.png");
        unsigned int texaerial = loadTexture("res/textures/models/texaerial.png");
        unsigned int texballkeep = loadTexture("res/textures/models/texballkeep.png");
        unsigned int texsandpit = loadTexture("res/textures/models/texsandpit.png");
        unsigned int texseesaw = loadTexture("res/textures/models/texseesaw.png");
        unsigned int texslide = loadTexture("res/textures/models/texslide.png");
        unsigned int texswing = loadTexture("res/textures/models/texswing.png");
        unsigned int textrampoline = loadTexture("res/textures/models/textrampoline.png");
        unsigned int textree = loadTexture("res/textures/models/textree.png");
        unsigned int textree2 = loadTexture("res/textures/models/textree2.png");
        unsigned int textab = loadTexture("res/textures/models/textab.png");

        unsigned int texaerialseat = loadTexture("res/textures/models/aerialrunnway_seat.png");
        unsigned int texswingseat = loadTexture("res/textures/models/swingseat.png");

       // unsigned int texfencefixed = loadTexture("res/textures/models/ogrodzenie_fixed.png");

        unsigned int texcola = loadTexture("res/textures/models/texcola.png");
        unsigned int texmentos = loadTexture("res/textures/models/mentos_texture.png");
        unsigned int texshowel = loadTexture("res/textures/models/lopata_tex.png");
        unsigned int texbucketblack = loadTexture("res/textures/models/bucket_black.png");
        unsigned int texbucketpink = loadTexture("res/textures/models/bucket_pink.png");
        unsigned int texbucketred = loadTexture("res/textures/models/bucket_red.png");
        unsigned int texCandyCane = loadTexture("res/textures/candy_cane_diffuse.jpg");
        

        //Allocating storage for the objects
        root_node = std::make_shared<SceneGraphNode>();
        root_water = std::make_shared<SceneGraphNode>();
        cube1 = std::make_shared<SceneGraphNode>();
        cube2 = std::make_shared<SceneGraphNode>();
        cube3 = std::make_shared<SceneGraphNode>();
        cubeKid2 = std::make_shared<SceneGraphNode>();
        cubeKid3 = std::make_shared<SceneGraphNode>();
        cubeKid4 = std::make_shared<SceneGraphNode>();
        cubeKid5 = std::make_shared<SceneGraphNode>();
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
        seesawbaseptr = std::make_shared<SceneGraphNode>();
        slideptr = std::make_shared<SceneGraphNode>();
        swingptr = std::make_shared<SceneGraphNode>();
        swingseatptr = std::make_shared<SceneGraphNode>();
        tablesptr = std::make_shared<SceneGraphNode>();
        trampolineptr = std::make_shared<SceneGraphNode>();
        treeptr = std::make_shared<SceneGraphNode>();
        tree2ptr = std::make_shared<SceneGraphNode>();
        umbrellaptr = std::make_shared<SceneGraphNode>();
        walkptr = std::make_shared<SceneGraphNode>();
        wallsptr = std::make_shared<SceneGraphNode>();
        damagedwallptr = std::make_shared<SceneGraphNode>();
        poolptr = std::make_shared<SceneGraphNode>();
        poolwaterptr = std::make_shared<SceneGraphNode>();
        tabptr = std::make_shared<SceneGraphNode>();

        treecircle1 = std::make_shared<SceneGraphNode>();
        treecircle2 = std::make_shared<SceneGraphNode>();
        trampolinecircle = std::make_shared<SceneGraphNode>();

        heartptr = std::make_shared<SceneGraphNode>();
        heartptr2 = std::make_shared<SceneGraphNode>();
        colaptr = std::make_shared<SceneGraphNode>();
        candyCane1ptr = std::make_shared<SceneGraphNode>();
        candyCane2ptr = std::make_shared<SceneGraphNode>();
        candyCane3ptr = std::make_shared<SceneGraphNode>();
        candyCane4ptr = std::make_shared<SceneGraphNode>();
        candyCane5ptr = std::make_shared<SceneGraphNode>();
        candyCane6ptr = std::make_shared<SceneGraphNode>();

        mentosptr = std::make_shared<SceneGraphNode>();
        bucketblackptr = std::make_shared<SceneGraphNode>();
        bucketpinkptr = std::make_shared<SceneGraphNode>();
        bucketredptr = std::make_shared<SceneGraphNode>();

        temp = std::make_shared<SceneGraphNode>();
        hammerptr = std::make_shared<SceneGraphNode>();
        mentosToAnimationptr = std::make_shared<SceneGraphNode>();
        colaToAnimationptr = std::make_shared<SceneGraphNode>();
        lightballptr = std::make_shared<SceneGraphNode>();
        player = std::make_shared<PlayerController>(cube3);
        tutorialState = std::make_shared<TutorialState>();


        collidingObjects.insert(collidingObjects.end(), {
        cube1,cube2,cube3, cubeKid2, cubeKid3, cubeKid4, cubeKid5, floorptr, ball,wallsptr,heartptr,heartptr2,colaptr, mentosptr, bucketblackptr, bucketpinkptr , bucketredptr,
        trampolineptr, goalLeftptr, goalRightptr, swingptr, swingseatptr, sandpitptr,benchesptr, tablesptr, treeptr, tree2ptr, aerialrunnwaywholeptr,
        seesawptr, poolptr, tabptr

            });
        glm::vec3 boxColRange(2.5f, 0.5f, 0.7f);
        glm::vec3 triggerRange(0.80f, 0.80f, 0.80f);
        glm::vec3 floorColRange(300.0f, 101.0f, 300.0f);

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
        Collider cube2Collider(0.54f, false, cubePositions[2], false);
        cube2->setProperties(animShader, fatkidtexture, cubePositions[2], MODEL, kidSeesaw, 0.05f, false, cube2Collider);
        Collider cube2Trigger(0.9f, false, cubePositions[2], true);
        cube2->trigger = cube2Trigger;
        cube2->isAnimated = true;
        cube2->tempAnim = &animatorKidSeesaw;
        cube2->shaderTemp3 = skeletalDepth;

        root_node->add_child(hammerptr);
        hammerptr->setProperties(animShader, hammertexture, cubePositions[2], MODEL, animatedHammer, 0.05f, false);
        hammerptr->isAnimated = true;
        hammerptr->tempAnim = &animatorHammer;
        hammerptr->shaderTemp3 = skeletalDepth;

        root_node->add_child(cubeKid2);
        Collider cubeKid2Collider(0.54f, false, cubePositions[10], false);
        cubeKid2->setProperties(animShader, kidSandPitTexture, cubePositions[10], MODEL, kidSandPit, 0.05f, false, cubeKid2Collider);
        Collider cubeKid2Trigger(0.9f, false, cubePositions[10], true);
        cubeKid2->trigger = cubeKid2Trigger;
        cubeKid2->isAnimated = true;
        cubeKid2->tempAnim = &animatorKidSandPit;
        cubeKid2->shaderTemp3 = skeletalDepth;

        root_node->add_child(bucketblackptr);
        bucketblackptr->setProperties(animShader, texbucketred, cubePositions[10], MODEL, animatedBucket, 0.05f, false);
        bucketblackptr->isAnimated = true;
        bucketblackptr->tempAnim = &animatorBucket;
        bucketblackptr->shaderTemp3 = skeletalDepth;

        root_node->add_child(cubeKid3);
        Collider cubeKid3Collider(0.54f, false, cubePositions[12], false);
        cubeKid3->setProperties(animShader, kid5texture, cubePositions[12], MODEL, postac_test, 0.05f, false, cubeKid3Collider);
        Collider cubeKid3Trigger(0.9f, false, cubePositions[12], true);
        cubeKid3->trigger = cubeKid3Trigger;
        cubeKid3->isAnimated = true;
        cubeKid3->tempAnim = &animatorHustawker;
        cubeKid3->shaderTemp3 = skeletalDepth;

        root_node->add_child(lightballptr);
        lightballptr->setProperties(animShader, texshowel, cubePositions[12], MODEL, animatedLightBall, 0.05f, false);
        lightballptr->isAnimated = true;
        lightballptr->tempAnim = &animatorLightBall;
        lightballptr->shaderTemp3 = skeletalDepth;

        root_node->add_child(cubeKid4);
        Collider cubeKid4Collider(0.54f, false, cubePositions[11], false);
        cubeKid4->setProperties(shaderShad, kid3texture, cubePositions[11], MODEL, postac_test, 0.05f, false, cubeKid4Collider);
        Collider cubeKid4Trigger(0.9f, false, cubePositions[11], true);
        cubeKid4->trigger = cubeKid4Trigger;
        cubeKid4->setRotation(0.0f, 270.0f, 0.0f);

        root_node->add_child(cubeKid5);
        Collider cubeKid5Collider(0.54f, false, cubePositions[13], false);
        cubeKid5->setProperties(animShader, kid4texture, cubePositions[13], MODEL, postac_test, 0.05f, false, cubeKid5Collider);
        Collider cubeKid5Trigger(0.9f, false, cubePositions[13], true);
        cubeKid5->trigger = cubeKid5Trigger;
        cubeKid5->isAnimated = true;
        cubeKid5->tempAnim = &animatorKidMentosCola;
        cubeKid5->shaderTemp3 = skeletalDepth;
        
        
        root_node->add_child(mentosToAnimationptr);
        mentosToAnimationptr->setProperties(animShader, texmentos, cubePositions[13], MODEL, animatedMentos, 0.05f, false);
        mentosToAnimationptr->isAnimated = true;
        mentosToAnimationptr->tempAnim = &animatorMentos;
        mentosToAnimationptr->shaderTemp3 = skeletalDepth;

        root_node->add_child(colaToAnimationptr);
        colaToAnimationptr->setProperties(animShader, texcola, cubePositions[13], MODEL, animatedCola, 0.05f, false);
        colaToAnimationptr->isAnimated = true;
        colaToAnimationptr->tempAnim = &animatorCola;
        colaToAnimationptr->shaderTemp3 = skeletalDepth;

        root_node->add_child(cube3);
        Collider cube3Collider(0.34f, false, playerPos, true);
        //cube3->setProperties(lightingShader, texturewin10, cubePositions[4], MODEL, box, 0.15f, true, cube3Collider);
        cube3->setProperties(animShader, texture_postac_test, playerPos, MODEL, postac_test, 0.05f, false, cube3Collider);
        cube3->isAnimated = true;
        cube3->tempAnim = &animatorMainCharacter;
        cube3->shaderTemp3 = skeletalDepth;

        //pilka
        root_node->add_child(ball);
        Collider ballCollider(0.350005f, false, glm::vec3(12.0f, 2.5f, 15.0f), true); //dont change 0.350005f (important)
        ball->setProperties(shaderShad, textureshrek, ballPos,MODEL,sphere,0.03f,true,ballCollider);
        ball->modelOutline = sphere;







        //tyrolka
        Collider aerialrunnwayTrigger(glm::vec3(0.2f, 3.0f, 0.2f), false, aerialRunnwayTrigerPos, true);
        Collider aerialrunnwayLinerTrigger(glm::vec3(1.5f, 1.f, 0.69f), false, aerialRunnwayLinerTrigerPos, true);
        Collider aerialrunnwayLinerTriggerOut(glm::vec3(3.5f, 3.f, 11.00f), false,glm::vec3(33.0f,0.13f,-2.6f), true);
        root_node->add_child(aerialrunnwaywholeptr);
        aerialrunnwaywholeptr->m_transform.y_rotation_angle = 180;
        aerialrunnwaywholeptr->setProperties(shaderShad, texaerial, aerialRunnwayPos, MODEL, aerialrunnwaywhole, 1.00f, false);
        aerialrunnwaywholeptr->modelOutline = aerialrunnwaywholeOut;
        aerialrunnwaywholeptr->additionalTriggers.push_back(aerialrunnwayLinerTrigger);
        aerialrunnwaywholeptr->additionalTriggers.push_back(aerialrunnwayLinerTriggerOut);

        //root_node->add_child(heartptr);
        //heartptr->setProperties(shaderShad, texturewin10, aerialRunnwayLinerTrigerPos, MODEL, postac_test, 0.05f, false);

        root_node->add_child(aerialrunnwayseatptr);
        aerialrunnwayseatptr->setProperties(shaderShad, texaerialseat, aerialRunnwayPos+aerialRunnwaySeatPos, MODEL, aerialrunnwayseat, 1.00f, false);
        //std::cout << aerialRunnwayPos.x + aerialRunnwaySeatPos.x <<"x"<< aerialRunnwayPos.y + aerialRunnwaySeatPos.y << "x" << aerialRunnwayPos.z + aerialRunnwaySeatPos.z << std::endl;
        aerialrunnwayseatptr->trigger = aerialrunnwayTrigger;
        aerialrunnwayseatptr->modelOutline = aerialrunnwayseatOut;

        tempPos = aerialRunnwayPos;
        tempPos.z -= 8.0f;

        //Podloga
        Collider AERfloor(glm::vec3(1.0f, 0.5f, 1.0f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERfloor);
        
        //LEFBACK RIGHTBACK
        tempPos.x -= 1.4;
        tempPos.z -= 1.1;

        Collider AERLB(glm::vec3(0.0001f, 4.0f, 0.0001f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERLB);

        tempPos.x += 1.39;
        tempPos.y += 4.0f;
        Collider AERfceelingh(glm::vec3(1.25f, 0.25f, 0.001f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERfceelingh);

        tempPos.x += 0.02;
        tempPos.z += 0.75;
        Collider AERfceelingv(glm::vec3(0.005f, 0.25f, 0.4f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERfceelingv);

        tempPos.y -= 0.85;
        tempPos.z += 1.15;
        Collider AERfceelinghl(glm::vec3(1.0f, 0.01f, 0.2f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERfceelinghl);

        tempPos.z += 8.0f;

        Collider AERrope(glm::vec3(0.01f, 0.01f, 7.35f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERrope);

        tempPos.z += 7.35f;
        Collider AERroof(glm::vec3(1.25f, 0.01f, 0.001f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERroof);

        tempPos.x -= 1.4;
        tempPos.y -= 3.25;
        tempPos.z -= 0.3;
        Collider AERFrontLeft(glm::vec3(0.01f, 2.35f, 0.45f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERFrontLeft);

        tempPos.x += 2.8;
        Collider AERFrontRight(glm::vec3(0.01f, 2.35f, 0.45f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERFrontRight);

        tempPos.x -= 1.4;
        tempPos.y += 3.35;
        tempPos.z += 0.3;

        tempPos.z -= 7.35f;
        tempPos.z -= 9.9;
        tempPos.x += 1.39;
        tempPos.y -= 3.25f;
        
        Collider AERRB(glm::vec3(0.0001f, 4.0f, 0.0001f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERRB);

        tempPos.z += 2.2;
        tempPos.x -= 0.275;
        Collider AERRF(glm::vec3(0.0001f, 3.0f, 0.0001f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERRF);

        tempPos.x -= 2.325;
        Collider AERLF(glm::vec3(0.0001f, 3.0f, 0.0001f), false, tempPos, false);
        aerialrunnwaywholeptr->additionalColliders.push_back(AERLF);
        
        //root_node->add_child(temp);
        //temp->setProperties(shaderShad, textureplanks, aerialRunnwayPos, MODEL, postac_test, 1.0f, false);

        //³awki
        root_node->add_child(benchesptr);
        benchesptr->setProperties(shaderShad, textureplanks, zeroPos, MODEL, benches, 0.01f, false);
        //benches colliders
        Collider bench1Collider(glm::vec3(0.15f, 0.45f,1.4f), false, glm::vec3(3.5f, 0.0f, -0.8f), false);
        benchesptr->additionalColliders.push_back(bench1Collider);
        Collider bench2Collider(glm::vec3(0.15f, 0.45f, 1.4f), false, glm::vec3(3.5f, 0.0f, -14.0f), false);
        benchesptr->additionalColliders.push_back(bench2Collider);
        Collider bench3Collider(glm::vec3(1.4f, 0.45f, 0.15f), false, glm::vec3(9.6f, 0.0f, -19.77f), false);
        benchesptr->additionalColliders.push_back(bench3Collider);
        Collider bench4Collider(glm::vec3(0.14f, 0.45f, 1.5f), false, glm::vec3(37.35f, 0.0f, -7.5f), false);
        benchesptr->additionalColliders.push_back(bench4Collider);
        Collider bench5Collider(glm::vec3(0.14f, 0.45f, 1.5f), false, glm::vec3(37.35f, 0.0f, 5.5f), false);
        benchesptr->additionalColliders.push_back(bench5Collider);

        Collider bench6Collider(glm::vec3(1.43f, 0.45f, 0.14f), false, glm::vec3(24.55f, 0.0f, -19.77f), false);
        benchesptr->additionalColliders.push_back(bench6Collider);
        Collider bench7Collider(glm::vec3(1.0f, 0.45f, 0.14f), false, glm::vec3(22.65f, 0.0f, 10.1f), false);
        benchesptr->additionalColliders.push_back(bench7Collider);
        Collider bench8Collider(glm::vec3(2.2f, 0.45f, 0.14f), false, glm::vec3(12.0f, 0.0f, 19.8f), false);
        benchesptr->additionalColliders.push_back(bench8Collider);


        //piaski
        root_node->add_child(sandsptr);
        sandsptr->setProperties(shaderShad, texturesand, glm::vec3(0.0f, -0.05f, 0.0f), MODEL, sands, 0.01f, false);

        ////krawezniki?
        root_node->add_child(walkptr);
        walkptr->setProperties(shaderShad, texturesand, walkPos, MODEL, walk, 0.01f, false);

        //podloga
        root_node->add_child(floorptr);
        Collider floorCol(floorColRange, false, glm::vec3(0.0f, -101.35f, 0.0f), false);
        floorptr->setProperties(shaderShad, texturegrass, floorPos, MODEL, floor, 0.05f, false, floorCol);

        root_node->add_child(treecircle1);
        treecircle1->setProperties(shaderShad, texturesand, glm::vec3(23.33f, 0.0f, -13.33f), MODEL, circle, 0.005f, false);

        root_node->add_child(treecircle2);
        treecircle2->setProperties(shaderShad, texturesand, tree2Pos, MODEL, circle, 0.005f, false);




        //Bramki
        root_node->add_child(goalLeftptr);
        //tyl
        glm::vec3 gLCP = goalLeftPos; //Goal Left Collider Position
        gLCP.x -= 1.6f;
        Collider goalLeftCollider(glm::vec3(0.015f, 3.0f, 2.95f), false, gLCP, false);
        gLCP.x += 1.4f;
        goalLeftptr->setProperties(shaderShad, texballkeep, goalLeftPos, MODEL, goalLeft, 0.14f, false, goalLeftCollider);
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
        gLCP.z -= 3.0f;
        //gora os Y
        gLCP.y += 3.0f;
        Collider goalLeftUpColliderY(glm::vec3(1.0f, 0.015f, 3.0f), false, gLCP, false);
        goalLeftptr->additionalColliders.push_back(goalLeftUpColliderY);


        root_node->add_child(goalRightptr);
        //tyl
        glm::vec3 gRCP = goalRightPos; //Goal Right Collider Position
        gRCP.x += 1.6f;
        Collider goalRightCollider(glm::vec3(0.015f, 3.0f, 2.95f), false, gRCP, false);
        gRCP.x -= 1.4f;
        goalRightptr->setProperties(shaderShad, texballkeep, goalRightPos, MODEL, goalRight, 0.14f, false, goalRightCollider);
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
        gRCP.z -= 3.0f;
        //gora os Y
        gRCP.y += 3.0f;
        Collider goalRightUpColliderY(glm::vec3(1.0f, 0.015f, 3.0f), false, gRCP, false);
        goalLeftptr->additionalColliders.push_back(goalRightUpColliderY);



        //piaskownica
        root_node->add_child(sandpitptr);
        Collider sandPitTrigger(glm::vec3(2.43f, 5.1f, 2.43f), false, sandPitPos, true);
        sandpitptr->setProperties(shaderShad, texsandpit, sandPitPos, MODEL, sandpit, 0.3f, false);
        sandpitptr->trigger = sandPitTrigger;
        sandpitptr->modelOutline = sandpitOut;

        sandPitPos.z -= 2.5f;
        Collider sandPitUpCollider(glm::vec3(2.4f, 0.25f, 0.025f), false, sandPitPos, false);
        sandpitptr->additionalColliders.push_back(sandPitUpCollider);
        sandPitPos.z += 2.5f;

        sandPitPos.z += 2.5f;
        Collider sandPitDownCollider(glm::vec3(2.4f, 0.25f, 0.025f), false, sandPitPos, false);
        sandpitptr->additionalColliders.push_back(sandPitDownCollider);
        sandPitPos.z -= 2.5f;

        sandPitPos.x -= 2.5f;
        Collider sandPitLeftCollider(glm::vec3(0.025f, 0.25f, 2.4f), false, sandPitPos, false);
        sandpitptr->additionalColliders.push_back(sandPitLeftCollider);
        sandPitPos.x += 2.5f;

        sandPitPos.x += 2.5f;
        Collider sandPitRightCollider(glm::vec3(0.025f, 0.25f, 2.4f), false, sandPitPos, false);
        sandpitptr->additionalColliders.push_back(sandPitRightCollider);
        sandPitPos.x -= 2.5f;

        //seesawbase
        root_node->add_child(seesawbaseptr);
        seesawbaseptr->setProperties(shaderShad, texseesaw, seesawPos, MODEL, seesawBase, 0.2f, false);

        //hustawka wazka
        Collider seesawTrigger(0.5f, false, seesawPos, true);
        root_node->add_child(seesawptr);
        seesawptr->setProperties(shaderShad, texseesaw, seesawPos, MODEL, seesaw, 0.2f, false);
        seesawptr->trigger = seesawTrigger;
        Collider seesawTriggerOutline(glm::vec3(3.30f, 3.30f, 3.30f), false, seesawPos, false);
        seesawptr->additionalTriggers.push_back(seesawTriggerOutline);
        seesawptr->modelOutline = seesawOut;

        //seesaw colliders
        seesawPos.y -= 0.6f;
        Collider seesawCollider1(glm::vec3(2.5f, 0.5f, 0.3f), false, seesawPos, false); //seats
        seesawPos.y += 0.6f;
        seesawPos.x -= 1.6f;
        Collider seesawCollider2(glm::vec3(0.01f, 0.5f, 0.20f), false, seesawPos, false); //left handles
         seesawPos.x -= 0.7f;
         seesawPos.y -= 0.2f;
         Collider seesawTriggerLeftSeat(glm::vec3(0.65f, 0.8f, 0.5f), false, seesawPos, false);
         seesawPos.x += 0.6f;
         seesawPos.y += 0.2f;
         seesawptr->additionalTriggers.push_back(seesawTriggerLeftSeat);
        seesawPos.x += 1.6f;
        seesawPos.x += 1.6f;
        Collider seesawCollider3(glm::vec3(0.01f, 0.5f, 0.20f), false, seesawPos, false); //right handles
         seesawPos.x += 0.6f;
         seesawPos.y -= 0.2f;
         Collider seesawTriggerRightSeat(glm::vec3(0.65f, 0.8f, 0.5f), false, seesawPos, false);
         seesawPos.x -= 0.6f;
         seesawPos.y += 0.2f;
         seesawptr->additionalTriggers.push_back(seesawTriggerRightSeat);
        seesawPos.x -= 1.6f;


        seesawptr->additionalColliders.push_back(seesawCollider1);
        seesawptr->additionalColliders.push_back(seesawCollider2);
        seesawptr->additionalColliders.push_back(seesawCollider3);


        //root_node->add_child(seesawreversepts);
        //seesawreversepts->setProperties(lightingShader, texturemetal, zeroPos, MODEL, seesawreverse, 0.01f);


        //zjezdzalnia
        /*Collider slideTrigger(1.2f, false, slidePos, true);
        root_node->add_child(slideptr);
        slideptr->setProperties(shaderShad, texslide, slidePos, MODEL, slide, 0.035f, false);
        slideptr->setRotation(0.0f, -90.0f, 0.0f);
        slideptr->trigger = slideTrigger;
        slidePos.x -= 2.3f;
        Collider slideTriggerOutline(glm::vec3(3.30f, 3.30f, 5.30f), false, slidePos, true);
        slideptr->additionalTriggers.push_back(slideTriggerOutline);
        slideptr->modelOutline = slideOut;*/

        //hustawka
        glm::vec3 swingTrigPos = swingPos;
        swingTrigPos.y -= 1.5f;
        Collider swingTrigger(glm::vec3(0.13f, 0.30f, 0.30f), false, swingTrigPos, false);

        root_node->add_child(swingptr);
        glm::vec3 swingColPos = swingPos;
        swingColPos.y -= 2.0f;
        //siedzenie
        Collider swingCollider(glm::vec3(0.20f, 0.38f, 0.38f), false, swingColPos, false);
        swingptr->setProperties(shaderShad, texswing, swingPos, MODEL, swing, 0.02f, false);
        swingptr->trigger = swingTrigger;
        swingptr->setRotation(0.0f, 180.0f, 0.0f);
        Collider swingTriggerOutline(glm::vec3(3.30f, 3.30f, 3.30f), false, swingTrigPos, false);
        swingptr->additionalTriggers.push_back(swingTriggerOutline);
        swingptr->modelOutline = swingOut;

        ////////niedziala i raczej nie bêdzie
        ////lewa porecz
        //swingColPos.z -= 0.25f;
        //Collider leftCollider(glm::vec3(0.001f, 2.38f, 0.001f), false, swingColPos, false);
        ////prawa porecz
        //swingColPos.z += 0.5f;
        //Collider rightCollider(glm::vec3(0.001f, 2.38f, 0.001f), false, swingColPos, false);
        //swingColPos.z -= 0.25f;
        //swingptr->additionalColliders.push_back(leftCollider);
        //swingptr->additionalColliders.push_back(rightCollider);


        
        //lewo gora
        swingColPos.z -= 1.45f;
        swingColPos.x -= 1.125f;
        Collider sCLU(glm::vec3(0.25f, 2.5f, 0.03f), false, swingColPos, false); //swing collider left up
        swingptr->additionalColliders.push_back(sCLU);
        //prawo gora
        swingColPos.x += 2.25f;
        Collider sCRU(glm::vec3(0.25f, 2.5f, 0.03f), false, swingColPos, false);
        swingptr->additionalColliders.push_back(sCRU);
        //prawo dol
        swingColPos.z += 2.9f;
        Collider sCRD(glm::vec3(0.25f, 2.5f, 0.03f), false, swingColPos, false);
        swingptr->additionalColliders.push_back(sCRD);
        //lewo dol
        swingColPos.x -= 2.25f;
        Collider sCLD(glm::vec3(0.25f, 2.5f, 0.03f), false, swingColPos, false);
        swingptr->additionalColliders.push_back(sCLD);


        //seat
        root_node->add_child(swingseatptr);
        glm::vec3 swingSeatPos = swingPos;
        swingSeatPos.y += 1.40f;
        swingseatptr->setProperties(shaderShad, texswingseat, swingSeatPos, MODEL, swingseat, 0.02f, false, swingCollider);
        swingseatptr->trigger = swingTrigger;
        swingseatptr->setRotation(0.0f, 180.0f, 0.0f);
     //   swingseatptr->modelOutline = swingseatOut;


        //stoly
        root_node->add_child(tablesptr);
        tablesptr->setProperties(shaderShad, textureplanks, zeroPos, MODEL, tables, 0.01f, false);
        //tables colliders
        Collider table1Collider1(glm::vec3(1.2f, 1.0f, 0.4f), false, glm::vec3(20.2f, 0.0f, 4.0f), false);
        tablesptr->additionalColliders.push_back(table1Collider1);
        Collider table1Collider2(glm::vec3(1.2f, 0.5f, 0.05f), false, glm::vec3(20.2f, 0.0f, 4.0f - 1.0f), false);
        Collider table1Collider3(glm::vec3(1.2f, 0.5f, 0.05f), false, glm::vec3(20.2f, 0.0f, 4.0f + 1.0f), false);
        tablesptr->additionalColliders.push_back(table1Collider2);
        tablesptr->additionalColliders.push_back(table1Collider3);

        Collider table2Collider1(glm::vec3(0.4f, 1.0f, 1.2f), false, glm::vec3(24.6f, 0.0f, -0.5f), false);
        tablesptr->additionalColliders.push_back(table2Collider1);
        Collider table2Collider2(glm::vec3(0.05f, 0.5f, 1.2f), false, glm::vec3(24.6f - 1.0f, 0.0f, -0.5f), false);
        Collider table2Collider3(glm::vec3(0.05f, 0.5f, 1.2f), false, glm::vec3(24.6f + 1.0f, 0.0f, -0.5f), false);
        tablesptr->additionalColliders.push_back(table2Collider2);
        tablesptr->additionalColliders.push_back(table2Collider3);
        Collider table3Collider1(glm::vec3(0.4f, 1.0f, 1.2f), false, glm::vec3(29.5f, 0.0f, -0.5f), false);
        tablesptr->additionalColliders.push_back(table3Collider1);
        Collider table3Collider2(glm::vec3(0.05f, 0.5f, 1.2f), false, glm::vec3(29.5f - 1.0f, 0.0f, -0.5f), false);
        Collider table3Collider3(glm::vec3(0.05f, 0.5f, 1.2f), false, glm::vec3(29.5f + 1.0f, 0.0f, -0.5f), false);
        tablesptr->additionalColliders.push_back(table3Collider2);
        tablesptr->additionalColliders.push_back(table3Collider3);

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
        trampolineptr->setProperties(shaderShad, textrampoline, trampolinePos, MODEL, trampoline, 0.006f, false, trampolineCollider1, trampolineTrigger);
        Collider trampolineTriggerOutline(glm::vec3(3.0f, 0.6f, 3.0f), false, trampolinePos, true);
        trampolineptr->additionalTriggers.push_back(trampolineTriggerOutline);
        trampolineptr->modelOutline = trampolineOut;

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


        root_node->add_child(treeptr);
        treeptr->setProperties(shaderShad, textree, treePos, MODEL, tree, 0.90f, false);
        

        tempPos = treePos; //(22.0f, 0.0f, -13.0f);
        //tempPos.y += 1.20;

        tempPos.y += 0.5;

        Collider treeColider0(0.6f, false, tempPos, false);

        tempPos.y += 0.7;

        Collider treeColider01(0.6f, false, tempPos, false);

        tempPos.y += 4.13;

        Collider treeColider02(glm::vec3(3.25f, 0.01f, 0.01f), false, tempPos, false);

        tempPos.y -= 0.6;

        Collider treeColider03(0.5f, false, tempPos, false);
        
        tempPos = treePos;
        tempPos.x += -1.0;
        tempPos.y += 4.20;
        tempPos.z += 2.2;


        Collider treeColider(glm::vec3(0.25f, 0.1f, 0.2f), false, tempPos, false);

        tempPos.x += 1.5;
        tempPos.y += 2.1;
        tempPos.z += -0.1;

        Collider treeColider2(glm::vec3(0.3f, 0.1f, 0.17f), false, tempPos, false);

        tempPos.x += 4.2;
        tempPos.y += -0.9;
        tempPos.z += 0.48;

        Collider treeColider3(glm::vec3(0.35f, 0.2f, 0.21f), false, tempPos, false);



        tempPos.x += -0.1;
        tempPos.y += -0.6;
        tempPos.z += -1.25;

        Collider treeColider4(glm::vec3(0.01f, 0.1f, 1.0f), false, tempPos, false);

        tempPos.x += -3.5;
        tempPos.y += 1.2;
        tempPos.z += 0.02;

        Collider treeColider5(glm::vec3(0.01f, 0.1f, 0.69f), false, tempPos, false);

        tempPos = treePos; //(22.0f, 0.0f, -13.0f);
        tempPos.x += -1.0;
        tempPos.y += 4.20;
        tempPos.z += 1.2;

        Collider treeColider6(glm::vec3(0.01f, 0.1f, 0.6f), false, tempPos, false);
        
        tempPos.y += 0.2;
        tempPos.z = treePos.z;
        
        Collider treeColider7(glm::vec3(0.01f, 0.4f, 0.01f), false, tempPos, false);
        
        tempPos.x -= 0.25;
        tempPos.y += 0.85;
        tempPos.z += -1.15;

        Collider treeColider8(glm::vec3(0.001f, 0.1f, 0.85f), false, tempPos, false);


        tempPos.x += -0.6;
        tempPos.y += 0.45;
        tempPos.z += -.5;

        Collider treeColider9(glm::vec3(0.3f, 0.3f, 0.001f), false, tempPos, false);


        tempPos.x -= 0.69;
        tempPos.y += 0.1;

        Collider treeColider10(glm::vec3(0.25f, 0.3f, 0.25f), false, tempPos, false);

        tempPos.x -= 0.35;
        tempPos.y += 0.6;
        tempPos.z += 2.25;

        //root_node->add_child(heartptr);
        //heartptr->setProperties(shaderShad, texturewin10, tempPos, MODEL, postac_test, 0.05f, false);

        Collider treeColider11(glm::vec3(0.37f, 0.45f, 0.46f), false, tempPos, false);


        tempPos.x -= 1.;
        //tempPos.y += -0.13;
        tempPos.z += 0.4;



        Collider treeColider12(glm::vec3(0.20f, 0.1f, 0.25f), false, tempPos, false);

        tempPos = treePos;
        tempPos.x += 2.25;
        tempPos.y += 6.0;
        tempPos.z += -0.30;

        Collider treeColider13(glm::vec3(0.64f, 2.f, 0.25f), false, tempPos, false);

        //glm::vec3 treePos(23.0f, 0.0f, -13.f);
        tempPos = treePos;
        tempPos.x += 5.0;
        tempPos.y += 6.0;
        //tempPos.z -= .25;


        Collider treeColider14(glm::vec3(0.65f, 0.5f, 0.33f), false, tempPos, false);


        tempPos.x += -1.0;
        tempPos.y += 1.3;
        tempPos.z += .15;


        Collider treeColider15(glm::vec3(0.15f, 0.3f, 0.15f), false, tempPos, false);

        tempPos.x -= 0.5;
        tempPos.y -= 1.5;
        tempPos.z -= .15;

        Collider treeColider16(glm::vec3(0.35f, 1.75f, 0.05f), false, tempPos, false);

        tempPos = treePos;
        tempPos.x += 4.0;
        tempPos.y += 7.04;
        tempPos.z -= 0.4;

        Collider treeColider17(glm::vec3(2.f, 1.12f, 0.0001f), false, tempPos, false);

        //w przód
        tempPos.x += -1.0;
        //tempPos.y += 7.0;
        tempPos.z -= 0.69;

        Collider treeColider18(glm::vec3(0.001f, 1.12f, 0.069f), false, tempPos, false);

        tempPos.x += .5;
        tempPos.y += 1.69;
        tempPos.z -= 0.30;

        Collider treeColider19(glm::vec3(0.25f, 0.11f, 0.13f), false, tempPos, false);



        tempPos.x += -1.5;
        tempPos.y += .33;
        tempPos.z += 2.;

        Collider treeColider20(glm::vec3(0.25f, 0.5f, 0.15f), false, tempPos, false);

        tempPos.x += -1.;
        tempPos.y += 1.1;
        //tempPos.z += -.1;

        Collider treeColider21(glm::vec3(0.25f, 0.5f, 0.16f), false, tempPos, false);

        tempPos.x += .9;
        tempPos.y += .60;
        tempPos.z += -.89;

        Collider treeColider22(glm::vec3(0.27f, 0.5f, 0.16f), false, tempPos, false);

        tempPos = treePos;
        tempPos.x += 6.45;
        tempPos.y += 9;
        tempPos.z += -0.69;

        Collider treeColider23(glm::vec3(0.85f, 0.69f, 0.69f), false, tempPos, false);


        tempPos.x += -.69;
        tempPos.y += 0.90;
        tempPos.z += -0.34;

        Collider treeColider24(glm::vec3(0.17f, 0.25f, 0.27f), false, tempPos, false);

        tempPos.x += 1.69;
        tempPos.y += 0.33;
        tempPos.z += 1.15;

        Collider treeColider25(glm::vec3(0.50f, 0.33f, 0.30f), false, tempPos, false);


        tempPos.x += .69;
        tempPos.y += 0.35;
        tempPos.z += .69;

        Collider treeColider26(glm::vec3(0.4f, 0.35f, 0.25f), false, tempPos, false);

        //root_node->add_child(heartptr);
        //heartptr->setProperties(shaderShad, texturewin10, tempPos, MODEL, postac_test, 0.05f, false);





        treeptr->additionalColliders.push_back(treeColider0);
        treeptr->additionalColliders.push_back(treeColider01);
        treeptr->additionalColliders.push_back(treeColider02);
        treeptr->additionalColliders.push_back(treeColider03);
        treeptr->additionalColliders.push_back(treeColider);
        treeptr->additionalColliders.push_back(treeColider2);
        treeptr->additionalColliders.push_back(treeColider3);
        treeptr->additionalColliders.push_back(treeColider4);
        treeptr->additionalColliders.push_back(treeColider5);
        treeptr->additionalColliders.push_back(treeColider6);
        treeptr->additionalColliders.push_back(treeColider7);
        treeptr->additionalColliders.push_back(treeColider8);
        treeptr->additionalColliders.push_back(treeColider9);
        treeptr->additionalColliders.push_back(treeColider10);
        treeptr->additionalColliders.push_back(treeColider11);
        treeptr->additionalColliders.push_back(treeColider12);
        treeptr->additionalColliders.push_back(treeColider13);
        treeptr->additionalColliders.push_back(treeColider14);
        treeptr->additionalColliders.push_back(treeColider15);
        treeptr->additionalColliders.push_back(treeColider16);
        treeptr->additionalColliders.push_back(treeColider17);
        treeptr->additionalColliders.push_back(treeColider18);
        treeptr->additionalColliders.push_back(treeColider19);
        treeptr->additionalColliders.push_back(treeColider20);
        treeptr->additionalColliders.push_back(treeColider21);
        treeptr->additionalColliders.push_back(treeColider22);
        treeptr->additionalColliders.push_back(treeColider23);
        treeptr->additionalColliders.push_back(treeColider24);
        treeptr->additionalColliders.push_back(treeColider25);
        treeptr->additionalColliders.push_back(treeColider26);


        root_node->add_child(tree2ptr);
        tree2ptr->setProperties(shaderShad, textree2, tree2Pos, MODEL, tree2, 0.90f, false);

        tempPos = tree2Pos;
        //tempPos.x += 5.0;
        tempPos.y += 1.5;
        tempPos.z += 0.069;

        Collider tree2Colider0(glm::vec3(0.4f, 2.f, 0.3f), false, tempPos, false);

        tempPos.x -= 0.15;
        tempPos.y += 1.50;

        Collider tree2Colider01(0.30, false, tempPos, false);


        tempPos.x += 0.6;
        tempPos.y += 2.2;
        tempPos.z += 0.2;

        Collider tree2Colider1(glm::vec3(0.20f, 0.5f, 0.3f), false, tempPos, false);

        tempPos.x += .9;
        tempPos.y -= .15;
        tempPos.z += 0.15;

        Collider tree2Colider2(glm::vec3(0.25f, 0.5f, 0.33f), false, tempPos, false);

        tempPos.x -= 1.25;
        tempPos.y += 0.69;
        tempPos.z += 1.30;

        Collider tree2Colider3(glm::vec3(0.01f, 0.5f, 0.55f), false, tempPos, false);

        tempPos.x += 0.25;
        tempPos.y += 0.69;
        tempPos.z += 1.35;

        Collider tree2Colider4(glm::vec3(0.2f, 0.3f, 0.25f), false, tempPos, false);

        tempPos.x -= 0.9;
        //tempPos.y = 0.69;
        tempPos.z -= 1.35;

        Collider tree2Colider5(glm::vec3(0.10f, 0.65f, 0.10f), false, tempPos, false);


        //tylne
        tempPos.x -= 1.25;
        tempPos.y -= 2.35;
        tempPos.z -= 2.15;

        Collider tree2Colider6(glm::vec3(0.20f, 0.15f, 0.33f), false, tempPos, false);

        tempPos.x += 1.0;
        //tempPos.y -= 0.69;
        tempPos.z -= 0.2;

        Collider tree2Colider7(glm::vec3(0.69f, 0.15f, 0.001f), false, tempPos, false);

        tempPos.x += 1.;
        //tempPos.y -= 0.69;
        tempPos.z -= 0.65;

        Collider tree2Colider8(glm::vec3(0.01f, 0.15f, 0.3f), false, tempPos, false);

        tempPos.x += 1.;
        tempPos.y += 0.69;
        tempPos.z -= 0.15;

        Collider tree2Colider9(glm::vec3(0.33f, 0.15f, 0.33f), false, tempPos, false);



        tempPos = tree2Pos;
        tempPos.x += .16;
        tempPos.y += 5.5;
        //tempPos.z += 0.069;

        Collider tree2Colider10(glm::vec3(0.17f, 1.5f, 0.2f), false, tempPos, false);

        //tempPos.x += .16;
        tempPos.y += 2.22;
        //tempPos.z += 0.069;

        Collider tree2Colider11(glm::vec3(0.10f, 1.6f, 0.22f), false, tempPos, false);


        tempPos.x += -.5;
        //tempPos.y += .22;
        tempPos.z += 0.1;

        Collider tree2Colider12(glm::vec3(0.25f, .1f, 0.001f), false, tempPos, false);

        tempPos.x += -1.23;
        tempPos.y += 0.15;
        tempPos.z -= 0.15;

        Collider tree2Colider13(glm::vec3(0.5f, .4f, 0.001f), false, tempPos, false);

        tempPos.x += -.65;
        tempPos.y += .5;
        tempPos.z -= 0.25;

        Collider tree2Colider14(glm::vec3(0.33f, .45f, 0.38f), false, tempPos, false);

        tempPos.x += 2.2;
        tempPos.y += .25;
        tempPos.z -= .4;

        Collider tree2Colider15(glm::vec3(0.23f, .4f, 0.01f), false, tempPos, false);

        tempPos.x += .33;
        tempPos.y += 1.0;
        tempPos.z += 1.62;

        Collider tree2Colider16(glm::vec3(0.01f, .3f, 0.06f), false, tempPos, false);

        tempPos.z += -1.1;

        Collider tree2Colider17(glm::vec3(0.02f, .5f, 0.05f), false, tempPos, false);

        tempPos.x += 1.1;
        tempPos.y += .5;
        tempPos.z += .15;

        Collider tree2Colider18(glm::vec3(0.1f, .3f, 0.02f), false, tempPos, false);

        tempPos.x += -.69;
        tempPos.y += .5;
        tempPos.z += -.2;

        Collider tree2Colider19(glm::vec3(0.06f, .2f, 0.2f), false, tempPos, false);

        tempPos.x += .25;
        tempPos.y += .5;
        tempPos.z += -.5;

        Collider tree2Colider20(glm::vec3(0.05f, .25f, 0.07f), false, tempPos, false);

        tempPos.x -= .33;
        tempPos.y += .69;
        tempPos.z += -.17;

        Collider tree2Colider21(glm::vec3(0.03f, .25f, 0.033f), false, tempPos, false);




        tempPos = tree2Pos;
        tempPos.x += .33;
        tempPos.y += 8.5;
        tempPos.z += -1.6;

        Collider tree2Colider22(glm::vec3(0.03f, .25f, 0.33f), false, tempPos, false);

        tempPos.x += -.8;
        tempPos.y += -1.10;
        tempPos.z += -.6;

        Collider tree2Colider23(glm::vec3(0.3f, .25f, 0.005f), false, tempPos, false);

        tempPos.x += 1.8;
        tempPos.y += 1.1;
        //tempPos.z += -.6;

        Collider tree2Colider24(glm::vec3(0.5f, .25f, 0.005f), false, tempPos, false);

        tempPos.x += 0.5;
        tempPos.y += 0.33;
        //tempPos.z += -.6;

        Collider tree2Colider241(glm::vec3(0.005f, .25f, 0.005f), false, tempPos, false);

        tempPos.x += -.4;
        tempPos.y += -0.1;
        tempPos.z += -.6;

        Collider tree2Colider25(glm::vec3(0.0001f, .4f, 0.2f), false, tempPos, false);

        //tempPos.x += 1.8;
        tempPos.y += 0.42;
        tempPos.z += -.9;

        Collider tree2Colider26(glm::vec3(0.1f, .2f, 0.18f), false, tempPos, false);

        tree2ptr->additionalColliders.push_back(tree2Colider0);
        tree2ptr->additionalColliders.push_back(tree2Colider01);
        tree2ptr->additionalColliders.push_back(tree2Colider1);
        tree2ptr->additionalColliders.push_back(tree2Colider2);
        tree2ptr->additionalColliders.push_back(tree2Colider3);
        tree2ptr->additionalColliders.push_back(tree2Colider4);
        tree2ptr->additionalColliders.push_back(tree2Colider5);

        //ty³
        tree2ptr->additionalColliders.push_back(tree2Colider6);
        tree2ptr->additionalColliders.push_back(tree2Colider7);
        tree2ptr->additionalColliders.push_back(tree2Colider8);
        tree2ptr->additionalColliders.push_back(tree2Colider9);

        //wy¿sze piêtra
        tree2ptr->additionalColliders.push_back(tree2Colider10);
        tree2ptr->additionalColliders.push_back(tree2Colider11);
        tree2ptr->additionalColliders.push_back(tree2Colider12);
        tree2ptr->additionalColliders.push_back(tree2Colider13);
        tree2ptr->additionalColliders.push_back(tree2Colider14);
        tree2ptr->additionalColliders.push_back(tree2Colider15);
        tree2ptr->additionalColliders.push_back(tree2Colider16);
        tree2ptr->additionalColliders.push_back(tree2Colider17);
        tree2ptr->additionalColliders.push_back(tree2Colider18);
        tree2ptr->additionalColliders.push_back(tree2Colider19);
        tree2ptr->additionalColliders.push_back(tree2Colider20);
        tree2ptr->additionalColliders.push_back(tree2Colider21);

        //wyjebable
        tree2ptr->additionalColliders.push_back(tree2Colider22);
        tree2ptr->additionalColliders.push_back(tree2Colider23);
        tree2ptr->additionalColliders.push_back(tree2Colider24);
        tree2ptr->additionalColliders.push_back(tree2Colider241);
        tree2ptr->additionalColliders.push_back(tree2Colider25);
        tree2ptr->additionalColliders.push_back(tree2Colider26);


        //parasol (I dont want to deal with colliders here xd)
        //root_node->add_child(umbrellaptr);
        //umbrellaptr->setProperties(shaderShad, texturewin10, zeroPos, MODEL, umbrella, 0.01f, false);

        //basen
        root_node->add_child(poolptr);
        poolptr->setProperties(shaderShad, texturewin10, poolPos, MODEL, pool, 0.07f, false);
        root_water->add_child(poolwaterptr);
        poolwaterptr->setProperties(waterShader, texturewater, poolWaterPos, MODEL, poolwater, 0.07f, false);
        //Collider poolColliderUp(glm::vec3(2.0f, 0.6f, 0.1f), false, glm::vec3(poolPos.x, 0.0f, poolPos.z - 1.5f), false);
        //Collider poolColliderDown(glm::vec3(2.0f, 0.6f, 0.1f), false, glm::vec3(poolPos.x, 0.0f, poolPos.z + 1.5f), false);
        //Collider poolColliderLeft(glm::vec3(0.1f, 0.6f, 0.9f), false, glm::vec3(poolPos.x - 2.2f, 0.0f, poolPos.z), false);
        //Collider poolColliderRight(glm::vec3(0.1f, 0.6f, 0.9f), false, glm::vec3(poolPos.x + 2.2f, 0.0f, poolPos.z), false);

        //poolptr->additionalColliders.push_back(poolColliderUp);
        //poolptr->additionalColliders.push_back(poolColliderDown);
        //poolptr->additionalColliders.push_back(poolColliderLeft);
        //poolptr->additionalColliders.push_back(poolColliderRight);


        //damaged wall
        root_node->add_child(damagedwallptr);
        damagedwallptr->setProperties(shaderShad, texturedamagedwall, glm::vec3(0.0f, -1.6f, 0.0f), MODEL, damagedwall, 0.01f, false);
        Collider damagedwallTrigger(glm::vec3(0.2f, 0.2f, 0.4f), false, damagedwallPos, false);
        damagedwallptr->trigger = damagedwallTrigger;
        
        root_node->add_child(tabptr);
        tabptr->setProperties(shaderShad, textab, tabPos, MODEL, model0, .03f, false);
        tabptr->m_transform.y_rotation_angle = 169;

        //walls
        float wallHeight = 2.0f;
        Collider wallColl1(glm::vec3(0.05f, wallHeight, 21.0f), false, wallPosColl1, true);  //left
        Collider wallColl2(glm::vec3(17.825f, wallHeight, 0.05f), false, wallPosColl2, true);  //up
        Collider wallColl3(glm::vec3(9.3145f, wallHeight, 0.05f), false, wallPosColl3, true);  //down
        Collider wallColl4(glm::vec3(0.05f, wallHeight, 4.747f), false, wallPosColl4, true); //inside down
        Collider wallColl5(glm::vec3(8.5f, wallHeight, 0.005f), false, wallPosColl5, true); //inside up
        Collider wallColl6(glm::vec3(0.05f, wallHeight+0.69f, 15.75f), false, wallPosColl6, true);  //right
        root_node->add_child(wallsptr);
        wallsptr->setProperties(shaderShad, texturewall, glm::vec3(0.0f,-1.6f,0.0f), MODEL, walls, 0.01f, false);
        wallsptr->additionalColliders.push_back(wallColl1);
        wallsptr->additionalColliders.push_back(wallColl2);
        wallsptr->additionalColliders.push_back(wallColl3);
        wallsptr->additionalColliders.push_back(wallColl4);
        wallsptr->additionalColliders.push_back(wallColl5);
        wallsptr->additionalColliders.push_back(wallColl6);

        Collider heartCollider(glm::vec3(0.005f, 1.0f, 0.005f), false, heartPos, true);
        Collider heartTrigger(glm::vec3(0.25f, 2.0f, 0.25f), true, heartPos, true);
        Collider heartTrigger2(glm::vec3(0.25f, 2.0f, 0.25f), true, heartPos2, true);
        Collider colaTrigger(glm::vec3(0.35f, 2.0f, 0.35f), true, colaPos, true);
        Collider mentosTrigger(glm::vec3(0.30f, 2.0f, 0.30f), true, mentosPos, true);
        Collider bucketblackTrigger(glm::vec3(0.25f, 2.0f, 0.25f), true, bucketBlackPos, true);
        Collider bucketpinkTrigger(glm::vec3(0.25f, 2.0f, 0.25f), true, bucketPinkPos, true);
        Collider bucketredTrigger(glm::vec3(0.25f, 2.0f, 0.25f), true, bucketRedPos, true);
        
        /*root_node->add_child(heartptr);
        heartptr->setProperties(shaderShad, texturewin10, heartPos, MODEL, postac_test, 0.05f, false);
        heartptr->trigger = heartTrigger;*/

        Collider showelGravitationer(0.01f, false, colaPos, true);
        root_node->add_child(heartptr2);
        heartptr2->setProperties(shaderShad, texshowel, heartPos2, MODEL, shovel, 0.01f, true, showelGravitationer);
        heartptr2->trigger = heartTrigger2;
        heartptr2->movableType = TOSANDPIT;
        heartptr2->modelOutline = shovelOut;


        Collider colaGravitationer(0.01f, false, colaPos, true);
        root_node->add_child(colaptr);
        colaptr->setProperties(shaderShad, texcola, colaPos, MODEL, cola, 1.0f, true, colaGravitationer);
        colaptr->trigger = colaTrigger;
        colaptr->modelOutline = colaOut;

        Collider mentosGravitationer(0.01f, false, mentosPos, true);
        root_node->add_child(mentosptr);
        mentosptr->setProperties(shaderShad, texmentos, mentosPos, MODEL, mentos, 0.7f, true, mentosGravitationer);
        mentosptr->trigger = mentosTrigger;
        //mentosptr->get_transform().y_rotation_angle += 30.0f;
        //mentosptr->get_transform().x_rotation_angle += 30.0f;
        mentosptr->modelOutline = mentosOut;

        Collider bucketGravitationer(0.01f, false, mentosPos, true);
        root_node->add_child(bucketredptr);
        bucketredptr->setProperties(shaderShad, texbucketred, bucketRedPos, MODEL, bucket, 0.1f, true, bucketGravitationer);
        bucketredptr->trigger = bucketredTrigger;
        bucketredptr->modelOutline = bucketOut;

        Collider candyCane1Trigger(glm::vec3(0.25f, 2.0f, 0.25f), true, candyCane1Pos, true);
        Collider candyCane2Trigger(glm::vec3(0.25f, 2.0f, 0.25f), true, candyCane2Pos, true);
        Collider candyCane3Trigger(glm::vec3(0.25f, 2.0f, 0.25f), true, candyCane3Pos, true);
        Collider candyCane4Trigger(glm::vec3(0.25f, 2.0f, 0.25f), true, candyCane4Pos, true);
        Collider candyCane5Trigger(glm::vec3(0.25f, 2.0f, 0.25f), true, candyCane5Pos, true);
        Collider candyCane6Trigger(glm::vec3(0.25f, 2.0f, 0.25f), true, candyCane6Pos, true);

        root_node->add_child(candyCane1ptr);
        candyCane1ptr->setProperties(shaderShad, texCandyCane, candyCane1Pos , MODEL, candyCane, 0.5f, false);
        candyCane1ptr->trigger = candyCane1Trigger;

        root_node->add_child(candyCane2ptr);
        candyCane2ptr->setProperties(shaderShad, texCandyCane, candyCane2Pos, MODEL, candyCane, 0.5f, false);
        candyCane2ptr->trigger = candyCane2Trigger;

        root_node->add_child(candyCane3ptr);
        candyCane3ptr->setProperties(shaderShad, texCandyCane, candyCane3Pos, MODEL, candyCane, 0.5f, false);
        candyCane3ptr->trigger = candyCane3Trigger;

        root_node->add_child(candyCane4ptr);
        candyCane4ptr->setProperties(shaderShad, texCandyCane, candyCane4Pos, MODEL, candyCane, 0.5f, false);
        candyCane4ptr->trigger = candyCane4Trigger;

        root_node->add_child(candyCane5ptr);
        candyCane5ptr->setProperties(shaderShad, texCandyCane, candyCane5Pos, MODEL, candyCane, 0.5f, false);
        candyCane5ptr->trigger = candyCane5Trigger;

        root_node->add_child(candyCane6ptr);
        candyCane6ptr->setProperties(shaderShad, texCandyCane, candyCane6Pos, MODEL, candyCane, 0.5f, false);
        candyCane6ptr->trigger = candyCane6Trigger;


        //root_node->add_child(bucketpinkptr);
        //bucketpinkptr->setProperties(shaderShad, texbucketpink, bucketPinkPos, MODEL, bucket, 0.1f, true);
        //bucketpinkptr->trigger = bucketpinkTrigger;
        //bucketpinkptr->modelOutline = bucketOut;


        glm::vec3 Trigger1WallBang(22.25, 0.0f, 21.5f);
        Collider escapeTriggerWallBang(glm::vec3(1.0f, 1.5f, 1.0f), false, Trigger1WallBang, false);

        glm::vec3 Trigger2Tyrolker(33.15, 15.5f, 11.5f);
        Collider escapeTriggerTyrolker(glm::vec3(4.0f, 40.2f, 0.5f), false, Trigger2Tyrolker, false);

        //TODO: Check if adjusments are needed. If displacement is good. Leave it as it is.
        glm::vec3 Trigger3Piaskownicer(-1.0f, 0.0f, -14.0f);
        Collider escapeTriggerPiaskownicer(glm::vec3(2.9f, 0.3f, 5.0f), false, Trigger3Piaskownicer, false);

        glm::vec3 Trigger4Hustawker(1.0f, 5.0f, 6.0f);
        Collider escapeTriggerHustawker(glm::vec3(1.6f, 2.5f, 4.0f), false, Trigger4Hustawker, false);

        glm::vec3 Trigger5Wazker(1.0f, 5.0f, -4.5f);
        Collider escapeTriggerWazker(glm::vec3(1.6f, 2.5f, 4.0f), false, Trigger5Wazker, false);

        glm::vec3 Trigger6liner(39.0f, 3.0f, 5.75f);
        Collider escapeTriggerLiner(glm::vec3(0.69f, 2.0f, 5.0f), false, Trigger6liner, false);

        glm::vec3 Trigger7tree(15.0f, 0.0f, -22.75f);
        Collider escapeTriggerTree(glm::vec3(4.f, 4.0f, 2.1f), false, Trigger7tree, false);

        
        //root_node->add_child(heartptr);
        //heartptr->setProperties(shaderShad, texturewin10, Trigger6liner, MODEL, postac_test, 0.05f, false);

        escapeTriggers.insert(escapeTriggers.end(), { escapeTriggerWallBang, escapeTriggerTyrolker, escapeTriggerPiaskownicer,  escapeTriggerHustawker, escapeTriggerWazker, escapeTriggerLiner, escapeTriggerTree });

        
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

    Sound walkingsound = Sound("res/sounds/Walk-sound.wav");
    Sound jumpingsound = Sound("res/sounds/jump.wav");
    Sound liftingsound = Sound("res/sounds/pick-up.wav");
    
    void update(double dt) {
        //gravity->updateGravityInNegativeY(cube2, dt);
        st = glfwGetTime();
        //walking
        if (player->getPlayerObject()->canJump && player->getMoveAnimation() && !player->getTempCheckCarry() && !player->checkCarry()) {
            if (!(cube3->tempAnim->getCurrentAnimation() == &anim1)) {
                cube3->tempAnim->PlayAnimation(&anim1);
                walkingsound.playLooped();
            }
            cube3->tempAnim->UpdateAnimation(dt * 1.5);
            
        }
        //walking like zombie
        if (player->getPlayerObject()->canJump && player->getMoveAnimation() && !player->getTempCheckCarry() && player->checkCarry()) {
            if (!(cube3->tempAnim->getCurrentAnimation() == &anim5)) {
                cube3->tempAnim->PlayAnimation(&anim5);
                walkingsound.playLooped();
            }
            cube3->tempAnim->UpdateAnimation(dt * 1.5);

        }
        //jumping
        if (!player->getPlayerObject()->canJump && !player->getMoveAnimation() && !player->getTempCheckCarry() && player->getCanJumpAnimation()) {
            if (!(cube3->tempAnim->getCurrentAnimation() == &anim2)) {
                cube3->tempAnim->PlayAnimation(&anim2);
                jumpingsound.play();
                walkingsound.stop();
            }
            cube3->tempAnim->UpdateAnimation(dt * 1.35);
            if (cube3->tempAnim->getCurrentTime() > cube3->tempAnim->getCurrentAnimation()->GetDuration() - 1.35) {
                player->setCanJumpAnimation(false);
            }
        }
        //idle
        if (player->getPlayerObject()->canJump && !player->getMoveAnimation() && !player->getTempCheckCarry()) {
            if (!(cube3->tempAnim->getCurrentAnimation() == &anim3)) {
                cube3->tempAnim->PlayAnimation(&anim3);
                walkingsound.stop();
            }
            cube3->tempAnim->UpdateAnimation(dt * 0.75);
        }
        //picking up
        if (player->checkCarry() && player->getTempCheckCarry()) {
            if (!(cube3->tempAnim->getCurrentAnimation() == &anim4)) {
                cube3->tempAnim->PlayAnimation(&anim4);
                liftingsound.play();
                walkingsound.stop();
            }
            cube3->tempAnim->UpdateAnimation(dt * 5);
            if (cube3->tempAnim->getCurrentTime() > cube3->tempAnim->getCurrentAnimation()->GetDuration() - 5) {
                player->setTempCheckCarry(false);
            }
        }
        if (cubeKid2->frustumCull) {
            cubeKid2->tempAnim->UpdateAnimation(dt);
            bucketblackptr->tempAnim->UpdateAnimation(dt);
        }
        if (cube2->frustumCull) {
            
            if (!player->getWazkerWait()) {
                if (!(cube2->tempAnim->getCurrentAnimation() == &animationKidSeesawIdle)) {
                    cube2->tempAnim->PlayAnimation(&animationKidSeesawIdle);
                    hammerptr->tempAnim->PlayAnimation(&animationHammerIdle);
                    player->setHammerAnimation(false);
                }
                cube2->tempAnim->UpdateAnimation(dt);
                hammerptr->tempAnim->UpdateAnimation(dt);
            }
            if (player->getWazkerWait()) {
                if (!(cube2->tempAnim->getCurrentAnimation() == &animationKidSeesaw)) {
                    cube2->tempAnim->PlayAnimation(&animationKidSeesaw);
                    hammerptr->tempAnim->PlayAnimation(&animationHammer);
                    player->setHammerAnimation(false);
                }
                cube2->tempAnim->UpdateAnimation(dt);
                hammerptr->tempAnim->UpdateAnimation(dt);
                if (cube2->tempAnim->getCurrentTime() > cube2->tempAnim->getCurrentAnimation()->GetDuration() - 30) {
                    player->setHammerAnimation(true);
                }
            }
        }

        if (cubeKid3->frustumCull) {
            if (!player->getHustawkerWait()) {
                if (!(cubeKid3->tempAnim->getCurrentAnimation() == &animationHustawkerIdle)) {
                    cubeKid3->tempAnim->PlayAnimation(&animationHustawkerIdle);
                    lightballptr->tempAnim->PlayAnimation(&animationLightBallIdle);
                    player->setGokuAnimation(false);
                }
                cubeKid3->tempAnim->UpdateAnimation(dt);
                lightballptr->tempAnim->UpdateAnimation(dt);
            }
            if (player->getHustawkerWait()) {
                if (!(cubeKid3->tempAnim->getCurrentAnimation() == &animationHustawker)) {
                    cubeKid3->tempAnim->PlayAnimation(&animationHustawker);
                    lightballptr->tempAnim->PlayAnimation(&animationLightBall);
                    player->setGokuAnimation(false);
                }
                cubeKid3->tempAnim->UpdateAnimation(dt);
                lightballptr->tempAnim->UpdateAnimation(dt);
                if (cubeKid3->tempAnim->getCurrentTime() > cubeKid3->tempAnim->getCurrentAnimation()->GetDuration() - 10) {
                    player->setGokuAnimation(true);
                }
            }
            
        }
        if (cubeKid5->frustumCull) {
            cubeKid5->tempAnim->UpdateAnimation(dt);
            mentosToAnimationptr->tempAnim->UpdateAnimation(dt);
            colaToAnimationptr->tempAnim->UpdateAnimation(dt);

        }


        //std::cout << "FIRST KID: current time: " << cubeKid3->tempAnim->getCurrentTime() << " getDuration: " << cubeKid3->tempAnim->getCurrentAnimation()->GetDuration() << std::endl;
        //std::cout << "bucketblackptr: current time: " << bucketblackptr->tempAnim.getCurrentTime() << " getDuration: " << bucketblackptr->tempAnim.getCurrentAnimation()->GetDuration() << std::endl;
        colaptr->update_transform();
        mentosptr->update_transform();
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
        float area = 32.0f;
        glm::mat4 orthgonalProjection = glm::ortho(-area, area, -area, area, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(lightPos, cube3->get_transform().m_position, glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix = orthgonalProjection * lightView;

        //simpleDepthShader.use();
        //simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glViewport(0, 0, shadowMapWidth, shadowMapHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        root_node->renderScene(true, lightSpaceMatrix);
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

        

        // do animacji
        // 
        animShader.use();
        animShader.setMat4("projection", projection);
        animShader.setMat4("view", view);

        // Make it so the stencil test always passes
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // Enable modifying of the stencil buffer
        //glStencilMask(0xFF);

        // draw our scene graph
        unsigned int total = 0, display = 0;
        root_node->render2(true,depthMap, camFrustum,display,total);
        //std::cout << "Total process in CPU : " << total << " / Total send to GPU : " << display << std::endl; //debugging

        // render Depth map to quad for visual debugging
        // don't delete---------------------------------
        //debugDepthQuad.use();
        //debugDepthQuad.setFloat("near_plane", near_plane);
        //debugDepthQuad.setFloat("far_plane", far_plane);
        //glActiveTexture(GL_TEXTURE0);
        //glBindTexture(GL_TEXTURE_2D, depthMap);
        //renderQuad();

        // Make it so only the pixels without the value 1 pass the test
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        // Disable modifying of the stencil buffer
        glStencilMask(0x00);
        // Disable the depth buffer
      //  glDisable(GL_DEPTH_TEST);

        outlineShader.use();
        outlineShader.setMat4("projection", projection);
        outlineShader.setMat4("view", view);
        //scale
       // outlineShader.setFloat("m_scale", 0.30f);
        outlineShader.setVec3("outlineColor", player->getOutlineColor());

        root_node->renderSceneWithOutline(true, outlineShader);
        glStencilMask(0xFF);
        // Clear stencil buffer
        glStencilFunc(GL_ALWAYS, 0, 0xFF);
        // Enable the depth buffer
      //  glEnable(GL_DEPTH_TEST);
    }

    void renderWater(unsigned int refractiontexture, unsigned int reflectiontexture, unsigned int dudvMap, unsigned int normalMap, float moveFactor)
    {
        root_water->renderWater(true, refractiontexture, reflectiontexture, dudvMap, normalMap, moveFactor);
    }

    unsigned int candyCount(std::shared_ptr<PlayerController> player, unsigned int tex1, unsigned int tex2, unsigned int tex3, unsigned int tex4, unsigned int tex5, unsigned int tex6, unsigned int tex7) {
        

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
        if (player->getCandyCount() <= 0)
            return tex1;
    }

    void checkWin()
    {
        int escape = 0;

        for (const auto& trigger : escapeTriggers)
        {
            if (cube3->collider.boxToBoxCollisioncheck(trigger) && ifWin == false)
            {
                ESC = escape;
                ifWin = true;
                timer = glfwGetTime();
            }

            if (ifWin & glfwGetTime() >= timer + 2) {
                playerWins++;
                std::cout << "Win";
                cube3->get_transform().m_position = playerPos;
                cube3->update_transform();
                ifWin = false;


                if (ESC == 0) { //Ogrodzenie i pilka
                    Model wallsfixed("res/models/level/ogrodzenie_fixed.obj");
                    wallsptr->modelTemp = wallsfixed;
                    Model model0("res/models/level/model0.obj");
                    damagedwallptr->modelTemp = model0;
                    wallsptr->additionalColliders.at(2).setPosition(glm::vec3(12.1845f, 0.0f, 21.0f)); //down
                    wallsptr->additionalColliders.at(3).setPosition(glm::vec3(21.5f, 0.0f, 15.8f)); //right
                    damagedwallptr->trigger.setPosition(glm::vec3(0.f, -100.0f, 0.0f));
                    ball->m_transform.m_position = glm::vec3(12.0f, 2.5f, 15.0f);
                }
                if (ESC == 1) { //Tyrolka
                    Model aerialrunnwayseat("res/models/level/aerialrunnway_seat.obj");

                    aerialrunnwayseatptr->modelTemp = aerialrunnwayseat;
                    aerialrunnwayseatptr->m_transform.m_scale = 1.0f;
                    already = true;
                }
                if (ESC == 2) { //piaskownica
                    piaskownicaMinusUcieczka = true;
                }
                if (ESC == 3) { //hustawka
                    player->setHustawkerBoyPaid(false);
                }
                if (ESC == 4) { //wazka
                    player->setWazkerBoyPaid(false);
                }
                if (ESC == 5) { //liner
                    Model tab("res/models/level/tab.obj");
                    Collider TabColider(glm::vec3(0.2f, 3.0f, 2.0f), false, glm::vec3(38.25f, 3.5f, 5.75f), false);
                    tabptr->modelTemp = tab;
                    //tabptr->additionalColliders.push_back(TabColider);
                    tabptr->collider = TabColider;
                    aerialrunnwaywholeptr->additionalTriggers.at(0).setPosition(glm::vec3(36.5f, -10.0f, 5.5f));
                }
                if (ESC == 6) { //tree
                    Model tre("res/models/level/tree2.obj");
                    tree2ptr->modelTemp = tre;

                    for (int i = 23; i < tree2ptr->additionalColliders.size(); i++)
                    {
                        tree2ptr->additionalColliders.at(i).setPosition(glm::vec3(36.5f, -10.0f, 5.5f));
                    }
                }
                break;
            }
            escape++;
        }
    }

    std::shared_ptr<TutorialState> getTutorialState() {
        return tutorialState;
    }
};