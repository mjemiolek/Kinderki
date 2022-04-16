#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Settings.h"

Camera camera(glm::vec3(0.0f, 16.0f, 5.0f));

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
                shaderTemp.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                shaderTemp.setVec3("light.direction", -0.1f, -1.0f, 0.5f);
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
                shaderTemp.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                shaderTemp.setVec3("light.direction", -0.1f, -1.0f, 0.5f);
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
    void setProperties(
        Shader shader,
        unsigned int ttexture,
        glm::vec3 position,
        renderEnum predefined,
        Model model,
        float scale) {
        shaderTemp = shader;
        texture = ttexture;
        m_transform.m_position = position;
        tempRender = predefined;
        modelTemp = model;
        m_transform.m_scale = scale;
    }
    void update_transform() {
        m_transform.m_world_matrix = m_transform.get_combined_matrix();
        m_dirty = true;
    }
    Transform& get_transform() {
        return m_transform;
    }

    Shader shaderTemp = Shader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    Model modelTemp = Model("res/models/box.obj");
    GLuint texture;
    renderEnum tempRender;
    unsigned int VAOTemp;

private:
    std::vector<std::shared_ptr<SceneGraphNode>> m_children;
    Transform m_transform;
    bool m_dirty;
};