#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "ModelAnimation.h"
#include "Settings.h"
#include "Collider.h"
#include "Frustum.h"
#include "Animator.h"


glm::vec3 lightPos = glm::vec3(5.0f, 35.0f, -30.0f);

enum renderEnum {
    MODEL, BOX, LIGHT, ANIM
};

enum movableType {
    TOSANDPIT, TOSEESAW, TOTRAMPOLINE, TOSLIDE, TOAR, TOSWING
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

    glm::vec3 getRight() const
    {
        return m_world_matrix[0];
    }
    glm::vec3 getUp() const
    {
        return m_world_matrix[1];
    }
    glm::vec3 getBackward() const
    {
        return m_world_matrix[2];
    }
    glm::vec3 getGlobalScale() const
    {
        return { glm::length(getRight()), glm::length(getUp()), glm::length(getBackward()) };
    }
};

struct BoundingVolume
{
    virtual bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const = 0;

    virtual bool isOnOrForwardPlan(const Plan& plan) const = 0;

    bool isOnFrustum(const Frustum& camFrustum) const
    {
        return (isOnOrForwardPlan(camFrustum.leftFace) &&
            isOnOrForwardPlan(camFrustum.rightFace) &&
            isOnOrForwardPlan(camFrustum.topFace) &&
            isOnOrForwardPlan(camFrustum.bottomFace) &&
            isOnOrForwardPlan(camFrustum.nearFace) &&
            isOnOrForwardPlan(camFrustum.farFace));
    };
};

struct Sphere : public BoundingVolume
{
    glm::vec3 center{ 0.f, 0.f, 0.f };
    float radius{ 0.f };

    Sphere(const glm::vec3& inCenter, float inRadius)
        : BoundingVolume{}, center{ inCenter }, radius{ inRadius }
    {}

    bool isOnOrForwardPlan(const Plan& plan) const final
    {
        return plan.getSignedDistanceToPlan(center) > -radius;
    }

    bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const final
    {
        //Get global scale thanks to our transform
        const glm::vec3 globalScale = transform.getGlobalScale();

        //Get our global center with process it with the global model matrix of our transform
        const glm::vec3 globalCenter{ transform.m_world_matrix * glm::vec4(center, 1.f) };

        //To wrap correctly our shape, we need the maximum scale scalar.
        const float maxScale = std::max(std::max(globalScale.x, globalScale.y), globalScale.z);

        //Max scale is assuming for the diameter. So, we need the half to apply it to our radius
        Sphere globalSphere(globalCenter, radius * (maxScale * 0.5f));

        //Check Firstly the result that have the most chance to faillure to avoid to call all functions.
        return (globalSphere.isOnOrForwardPlan(camFrustum.leftFace) &&
            globalSphere.isOnOrForwardPlan(camFrustum.rightFace) &&
            globalSphere.isOnOrForwardPlan(camFrustum.farFace) &&
            globalSphere.isOnOrForwardPlan(camFrustum.nearFace) &&
            globalSphere.isOnOrForwardPlan(camFrustum.topFace) &&
            globalSphere.isOnOrForwardPlan(camFrustum.bottomFace));
    };
};

Sphere generateSphereBV(const Model& model)
{
    glm::vec3 minAABB = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 maxAABB = glm::vec3(std::numeric_limits<float>::min());
    for (auto&& mesh : model.meshes)
    {
        for (auto&& vertex : mesh.vertices)
        {
            minAABB.x = std::min(minAABB.x, vertex.Position.x);
            minAABB.y = std::min(minAABB.y, vertex.Position.y);
            minAABB.z = std::min(minAABB.z, vertex.Position.z);

            maxAABB.x = std::max(maxAABB.x, vertex.Position.x);
            maxAABB.y = std::max(maxAABB.y, vertex.Position.y);
            maxAABB.z = std::max(maxAABB.z, vertex.Position.z);
        }
    }

    return Sphere((maxAABB + minAABB) * 0.5f, glm::length(minAABB - maxAABB));
}


struct SceneGraphNode {
    SceneGraphNode() : m_dirty(true) {}
    explicit SceneGraphNode(const Transform& t) : m_transform(t), m_dirty(true) {}
    void add_child(const std::shared_ptr<SceneGraphNode>& sgn) {
        m_children.push_back(sgn);
    }
    bool detach_child(const std::shared_ptr<SceneGraphNode>& sgn) {
        for (int i = 0; i < m_children.size(); i++) {
            if (m_children[i] == sgn) {
                m_children[i] = nullptr;
                m_children.erase(m_children.begin() + i);
                return true;
            }
        }
        return false;
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
    void render(bool is_root = false, glm::vec4 clip = glm::vec4(0.0f, -1.0f, 0.0f, 2.4f)) {
        if (!is_root) {
            shaderTemp2.use();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            shaderTemp2.setMat4("projection", projection);

            glm::mat4 view = camera.GetViewMatrix();
            shaderTemp2.setMat4("view", view);
            shaderTemp2.setMat4("u_world", m_transform.m_world_matrix);
            shaderTemp2.setVec4("plane", clip.x, clip.y, clip.z, clip.w);
            

            if (tempRender == BOX) {

                shaderTemp2.setVec3("viewPos", camera.Position);
                shaderTemp2.setVec3("light.position", lightPos);
                shaderTemp2.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                //shaderTemp.setVec3("light.direction", -0.1f, -1.0f, 0.5f);
                shaderTemp2.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
                shaderTemp2.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
                shaderTemp2.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
                shaderTemp2.setFloat("material.shininess", 64.0f);
                glBindVertexArray(VAOTemp);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
            if (tempRender == MODEL) {
                shaderTemp2.setVec3("viewPos", camera.Position);
                shaderTemp2.setVec3("light.position", lightPos);
                shaderTemp2.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                //shaderTemp.setVec3("light.direction", -0.1f, -1.0f, 0.5f);
                shaderTemp2.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
                shaderTemp2.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
                shaderTemp2.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
                shaderTemp2.setFloat("material.shininess", 64.0f);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                modelTemp.Draw(shaderTemp2);
            }

        }
        for (uint32_t i = 0; i < m_children.size(); ++i) {
            m_children[i]->render(false, clip);
        }
    }
    void renderScene(bool is_root = false, glm::mat4 lightSpaceMatrix = glm::mat4(1.0f))
    {
        if (!is_root)
        {
            shaderTemp3.use();
            shaderTemp3.setMat4("lightSpaceMatrix", lightSpaceMatrix);
            if (isAnimated) {
                auto transforms = tempAnim->GetFinalBoneMatrices();
                for (int i = 0; i < transforms.size(); ++i) {
                    //      animator.GetFinalBoneMatrices().at(i) = glm::scale(animator.GetFinalBoneMatrices().at(i), glm::vec3(0.05f, 0.05f, 0.05f));
                    shaderTemp3.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                }
            }
            shaderTemp3.setMat4("model", m_transform.m_world_matrix);
            modelTemp.Draw(shaderTemp3);
        }
        for (uint32_t i = 0; i < m_children.size(); ++i)
        {
            m_children[i]->renderScene(false, lightSpaceMatrix);
        }
    }
    void render2(bool is_root, unsigned int depthMap, const Frustum& frustum, unsigned int& display, unsigned int& total)
    {
        if (!is_root) 
        {
            if (boundingVolume->isOnFrustum(frustum, m_transform))
            {
                frustumCull = true;
                if (stencil) {
                    glStencilMask(0xFF);
                }
                else {
                    glStencilMask(0x00);
                }
                shaderTemp.use();
                if (isAnimated) {
                    auto transforms = tempAnim->GetFinalBoneMatrices();
                    for (int i = 0; i < transforms.size(); ++i) {
                        //      animator.GetFinalBoneMatrices().at(i) = glm::scale(animator.GetFinalBoneMatrices().at(i), glm::vec3(0.05f, 0.05f, 0.05f));
                        shaderTemp.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
                    }
                }
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, depthMap);
                shaderTemp.setMat4("model", m_transform.m_world_matrix);
                modelTemp.Draw(shaderTemp);
                display++;
            }
            else {
                frustumCull = false;
            }
            total++;
        }
        for (uint32_t i = 0; i < m_children.size(); ++i) 
        {
            m_children[i]->render2(false,depthMap,frustum,display,total);
        }
    }
    void renderSceneWithOutline(bool is_root = false, Shader shader = Shader()) {
        {
            if (!is_root)
            {
                if (stencil) {
                    shader.setMat4("model", m_transform.m_world_matrix);
                    modelOutline.Draw(shader);
                }          
            }
            for (uint32_t i = 0; i < m_children.size(); ++i)
            {
                m_children[i]->renderSceneWithOutline(false, shader);
            }
        }
    }
    void renderWater(bool is_root, unsigned int refractionTexture, unsigned int reflectionTexture, unsigned int dudvMap, unsigned int normalMap, float moveFactor)
    {
        if (!is_root) {
            shaderTemp.use();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
            shaderTemp.setMat4("projection", projection);

            glm::mat4 view = camera.GetViewMatrix();
            shaderTemp.setMat4("view", view);
            shaderTemp.setMat4("u_world", m_transform.m_world_matrix);
            shaderTemp.setFloat("moveFactor", moveFactor); //distortion
            shaderTemp.setVec3("cameraPosition", camera.Position);
            shaderTemp.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            shaderTemp.setVec3("lightPosition", lightPos);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, refractionTexture);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, reflectionTexture);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, dudvMap);
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, normalMap);
            modelTemp.Draw(shaderTemp);

        }
        for (uint32_t i = 0; i < m_children.size(); ++i) {
            m_children[i]->renderWater(false, refractionTexture, reflectionTexture, dudvMap, normalMap, moveFactor);
        }
    }
    void setProperties(Shader shader, unsigned int ttexture, glm::vec3 position, renderEnum predefined, Model model, float scale, bool stencilTest, Collider col = Collider(), Collider trig = Collider()) {
        shaderTemp = shader;
        texture = ttexture;
        m_transform.m_position = position;
        tempRender = predefined;
        modelTemp = model;
        boundingVolume = std::make_unique<Sphere>(generateSphereBV(model));
        m_transform.m_scale = scale;
        collider = col;
        trigger = trig;
        stencil = stencilTest; //add outline to object
    }
    void setRotation(float x, float y, float z)
    {
        m_transform.x_rotation_angle = x;
        m_transform.y_rotation_angle = y;
        m_transform.z_rotation_angle = z;
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

    bool getStencil() {
        return stencil;
    }
    void setStencil(bool temp) {
        stencil = temp;
    }
    movableType getMovableType() {
        return movableType;
    }
    void setMovableType(movableType temp) {
        movableType = temp;
    }


    Shader shaderTemp = Shader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    Shader shaderTemp2 = Shader("res/shaders/lightcaster.vert", "res/shaders/lightcaster.frag");
    Shader shaderTemp3 = Shader("res/shaders/shadow_mapping_depth.vert", "res/shaders/shadow_mapping_depth.frag");
    Model modelTemp = Model("res/models/box.obj");
    Model modelOutline = Model("res/models/box.obj");
    Animator* tempAnim;
    bool isAnimated = false;
    GLuint texture;
    renderEnum tempRender;
    unsigned int VAOTemp;
    Collider collider;
    std::vector<Collider> additionalColliders;
    std::vector<Collider> additionalTriggers;
    Collider trigger;
    bool stencil;
    movableType movableType;
    bool frustumCull = false;

    std::unique_ptr<Sphere> boundingVolume; //Frustrum

    std::vector<std::shared_ptr<SceneGraphNode>> m_children;
    Transform m_transform;
    bool m_dirty;

    //jumping
    bool canJump = false;

    //Physics
    glm::vec3 gravity = glm::vec3(0.0f, -9.81f, 0.0f);
    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 force = glm::vec3(0.0f, 0.0f, 0.0f);
    float mass = 1.0f;

    bool canInToGround = false;

    void applyGravity(float deltaTime)
    {
        force += mass * gravity; // apply a force of gravity

        velocity += force / mass * deltaTime;
        
        force = glm::vec3(0.0f, 0.0f, 0.0f); // reset net force
    }
    void applyOppositeGravity(float deltaTime)
    {
        force += mass * gravity; // apply a force of gravity

        velocity -= force / mass * deltaTime;

        force = glm::vec3(0.0f, 0.0f, 0.0f); // reset net force
    }
    void moveObject(float deltaTime)
    {
        m_transform.m_position += velocity * deltaTime;
        collider.setPosition(m_transform.m_position);
    }
};