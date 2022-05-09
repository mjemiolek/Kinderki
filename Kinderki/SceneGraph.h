#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Settings.h"
#include "Collider.h"

Camera camera(glm::vec3(0.0f, 16.0f, 5.0f));
glm::vec3 lightPos = glm::vec3(5.0f, 35.0f, -30.0f);

enum renderEnum {
    MODEL, BOX, LIGHT
};

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

            if (tempRender == BOX) {

                shaderTemp.setVec3("viewPos", camera.Position);
                shaderTemp.setVec3("light.position", lightPos);
                shaderTemp.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                //shaderTemp.setVec3("light.direction", -0.1f, -1.0f, 0.5f);
                shaderTemp.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
                shaderTemp.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
                shaderTemp.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
                shaderTemp.setFloat("material.shininess", 64.0f);
                glBindVertexArray(VAOTemp);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            if (tempRender == MODEL) {
                shaderTemp.setVec3("viewPos", camera.Position);
                shaderTemp.setVec3("light.position", lightPos);
                shaderTemp.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                //shaderTemp.setVec3("light.direction", -0.1f, -1.0f, 0.5f);
                shaderTemp.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
                shaderTemp.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
                shaderTemp.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
                shaderTemp.setFloat("material.shininess", 64.0f);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                modelTemp.Draw(shaderTemp);

            }

        }
        for (uint32_t i = 0; i < m_children.size(); ++i) {
            m_children[i]->render();
        }
    }
    void renderScene(bool is_root = false, Shader shader = Shader())
    {
        if (!is_root)
        {
            

            shader.setMat4("model", m_transform.m_world_matrix);
            modelTemp.Draw(shader);
        }
        for (uint32_t i = 0; i < m_children.size(); ++i)
        {
            m_children[i]->renderScene(false, shader);
        }
    }
    void render2(bool is_root = false, unsigned int depthMap = 0,Shader shader = Shader())
    {
        if (!is_root) 
        {
            if (stencil) {
                glStencilMask(0xFF);
            }
            else {
                glStencilMask(0x00);
            }
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, depthMap);
            shader.setMat4("model", m_transform.m_world_matrix);
            modelTemp.Draw(shader);
        }
        for (uint32_t i = 0; i < m_children.size(); ++i) 
        {
            m_children[i]->render2(false,depthMap,shader);
        }
    }
    void renderSceneWithOutline(bool is_root = false, Shader shader = Shader()) {
        {
            if (!is_root)
            {
                if (stencil) {
                    shader.setMat4("model", m_transform.m_world_matrix);
                    modelTemp.Draw(shader);
                }          
            }
            for (uint32_t i = 0; i < m_children.size(); ++i)
            {
                m_children[i]->renderSceneWithOutline(false, shader);
            }
        }
    }
    void setProperties(Shader shader, unsigned int ttexture, glm::vec3 position, renderEnum predefined, Model model, float scale, bool stencilTest, Collider col = Collider(), Collider trig = Collider()) {
        shaderTemp = shader;
        texture = ttexture;
        m_transform.m_position = position;
        tempRender = predefined;
        modelTemp = model;
        m_transform.m_scale = scale;
        collider = col;
        trigger = trig;
        stencil = stencilTest; //add outline to object
    }
    void update_transform() {
        m_transform.m_world_matrix = m_transform.get_combined_matrix();
        m_dirty = true;
    }
    Transform& get_transform() {
        return m_transform;
    }
    
    void updatePositionDest(glm::vec3 destination) {
        if (abs(destination.x - m_transform.m_position.x) > 11) {
            if (m_transform.m_position.x > destination.x) {
                m_transform.m_position.x -= 0.04;
            }
            else
            {
                m_transform.m_position.x += 0.04;
            }
        }
        if ((destination.z - m_transform.m_position.z) < -5 || abs(destination.z - m_transform.m_position.z) > 7.5) {
            if (m_transform.m_position.z > destination.z) {
                m_transform.m_position.z -= 0.04;
            }
            else
            {
                m_transform.m_position.z += 0.04;
            }
        }
        m_dirty = true;
    }

    Shader shaderTemp = Shader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    Model modelTemp = Model("res/models/box.obj");
    GLuint texture;
    renderEnum tempRender;
    unsigned int VAOTemp;
    Collider collider;
    Collider trigger;
    bool stencil;

    std::vector<std::shared_ptr<SceneGraphNode>> m_children;
    Transform m_transform;
    bool m_dirty;

    //Physics
    glm::vec3 gravity = glm::vec3(0.0f, -0.981f, 0.0f);
    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
    float mass = 1.0f;

    void applyGravity(float deltaTime)
    {
        //if (collider.getIsStatic() == false) { force += mass * gravity; } // apply a force of gravity

        velocity += force / mass * deltaTime;
        m_transform.m_position += velocity * deltaTime;

        force = glm::vec3(0.0f, 0.0f, 0.0f); // reset net force
    }
};