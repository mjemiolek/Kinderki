#ifndef PARTICLE_GEN_H
#define PARTICLE_GEN_H
#include <vector>

//#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "GameManager.h"


// Represents a single particle and its state
struct Particle {
    glm::vec2 Position, Velocity;
    glm::vec4 Color;
    GLfloat Life;

    Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) { }
};


// ParticleGenerator acts as a container for rendering a large number of 
// particles by repeatedly spawning and updating particles and killing 
// them after a given amount of time.

class ParticleGen
{
private:
    // State
    std::vector<Particle> particles;
    GLuint amount;
    // Render state
    Shader shader;
    unsigned int texture;
    GLuint VAO;

public:
    ParticleGen(Shader shader, unsigned int texture, GLuint amount)
        : shader(shader), texture(texture), amount(amount)
    {
        this->init();
    }

    void Update(GLfloat dt, SceneGraphNode& object, GLuint newParticles, glm::vec3 offset)
    {
        // Add new particles 
        for (GLuint i = 0; i < newParticles; ++i)
        {
            int unusedParticle = this->firstUnusedParticle();
            this->respawnParticle(this->particles[unusedParticle], object, offset);
        }
        // Update all particles
        for (GLuint i = 0; i < this->amount; ++i)
        {
            Particle& p = this->particles[i];
            p.Life -= dt; // reduce life
            if (p.Life > 0.0f)
            {	// particle is alive, thus update
                p.Position -= p.Velocity * dt;
                p.Color.a -= dt * 2.5;
            }
        }
    }

    // Render all particles
    void Draw()
    {
        // Use additive blending to give it a 'glow' effect
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        this->shader.use();
        for (Particle particle : this->particles)
        {
            if (particle.Life > 0.0f)
            {
                this->shader.setVec2("offset", particle.Position);
                this->shader.setVec4("color", particle.Color);
                glBindTexture(GL_TEXTURE_2D, texture);
                glBindVertexArray(this->VAO);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);
            }
        }
        // Don't forget to reset to default blending mode
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void init()
    {
        // Set up mesh and attribute properties
        GLuint VBO;
        GLfloat particle_quad[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };
        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(this->VAO);
        // Fill mesh buffer
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
        // Set mesh attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindVertexArray(0);

        // Create this->amount default particle instances
        for (GLuint i = 0; i < this->amount; ++i)
            this->particles.push_back(Particle());
    }

    // Stores the index of the last particle used (for quick access to next dead particle)
    GLuint lastUsedParticle = 0;
    GLuint firstUnusedParticle()
    {
        // First search from last used particle, this will usually return almost instantly
        for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
            if (this->particles[i].Life <= 0.0f) {
                lastUsedParticle = i;
                return i;
            }
        }
        // Otherwise, do a linear search
        for (GLuint i = 0; i < lastUsedParticle; ++i) {
            if (this->particles[i].Life <= 0.0f) {
                lastUsedParticle = i;
                return i;
            }
        }
        // All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
        lastUsedParticle = 0;
        return 0;
    }

    void respawnParticle(Particle& particle, SceneGraphNode& object, glm::vec3 offset)
    {
        GLfloat random = ((rand() % 100) - 50) / 10.0f;
        GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
        particle.Position = object.m_transform.m_position + random + offset;
        particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
        particle.Life = 1.0f;
        particle.Velocity = -object.gravity * 11.1f;  ////tu bedzie potrzebna zmiana
    }

};

#endif