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


class GameManager {
    public:
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
    const GLuint SCR_WIDTH = 1280;
    const GLuint SCR_HEIGHT = 720;
    std::shared_ptr<SceneGraphNode> collidingObjects[6];



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
	void init() {
        glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
        // settings
        

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

        

        
        Shader lightingShader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");


        lightingShader.use();
        lightingShader.setInt("material.diffuse", 0);
        lightingShader.setInt("material.specular", 64);
        lightingShader.setVec3("lightPos", lightPos);

        

        Model box("res/models/box.obj");
        Model sphere("res/models/sphere.obj");
        Model floor("res/models/floor.obj");
        Model meshes("res/models/meshes.obj");
        Model sands("res/models/sands.obj");

        unsigned int texturekupa = loadTexture("res/textures/win.png");
        unsigned int texturegrass = loadTexture("res/textures/grasstexture.png");
        unsigned int texturemetal = loadTexture("res/textures/metaltexture.png");
        unsigned int texturesand = loadTexture("res/textures/sandtexture.png");
        unsigned int diffuseMap = loadTexture("res/textures/diff.jpg");
        unsigned int specularMap = loadTexture("res/textures/spec.jpg");
        unsigned int texture = loadTexture("res/textures/stone.jpg");



        root_node = std::make_shared<SceneGraphNode>();
        cube1 = std::make_shared<SceneGraphNode>();
        cube2 = std::make_shared<SceneGraphNode>();
        cube3 = std::make_shared<SceneGraphNode>();
        test1 = std::make_shared<SceneGraphNode>();
        modelTest = std::make_shared<SceneGraphNode>();
        floorTest = std::make_shared<SceneGraphNode>();
        meshesTest = std::make_shared<SceneGraphNode>();
        sandsTest = std::make_shared<SceneGraphNode>();

        collidingObjects[0] = cube1;
        collidingObjects[1] = cube2;
        collidingObjects[2] = modelTest;
        collidingObjects[3] = floorTest;
        collidingObjects[4] = meshesTest;
        collidingObjects[5] = sandsTest;

        root_node->add_child(cube1);
        cube1->shaderTemp = lightingShader;
        cube1->texture = texture;
        cube1->get_transform().m_position = cubePositions[0];
        cube1->tempRender = MODEL;
        cube1->modelTemp = box;
        cube1->get_transform().m_scale = 0.15f;

        root_node->add_child(cube2);
        cube2->shaderTemp = lightingShader;
        cube2->texture = texturekupa;
        cube2->get_transform().m_position = cubePositions[2];
        cube2->tempRender = BOX;
        cube2->tempRender = MODEL;
        cube2->modelTemp = box;
        cube2->get_transform().m_scale = 0.15f;

        root_node->add_child(cube3);
        cube3->shaderTemp = lightingShader;
        cube3->texture = texturekupa;
        cube3->get_transform().m_position = cubePositions[4];
        cube3->tempRender = BOX;
        cube3->tempRender = MODEL;
        cube3->modelTemp = box;
        cube3->get_transform().m_scale = 0.15f;

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
	}
    void update(float dt) {
        //if (x < -0.50f) {
        //    x = x + 0.01f;
        //    bar[4] = x;
        //    bar[6] = x;
        //    bar[8] = x;

        //    //std::cout << bar[4] << " " << std::endl;

        //}
        //else {
        //    x = -0.90f;
        //}
        //strs.str(std::string());

        //strs << passed_time;
        cube2->update_transform();
        cube3->update_transform();
        root_node->update(Transform(), false);
    }
    void render() {
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        root_node->render(true);
    }
};