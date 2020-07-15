#include "particleGenerator.h"

ParticleGen::ParticleGen(Shader shader, Texture2D texture, GLuint amount)
	: shader(shader), texture(texture), amount(20)
{
	this->init();
}

void ParticleGen::Update(GLfloat dt, glm::vec3 blockPos, GLuint newParticles, glm::vec3 offset=glm::vec3(0.0f,0.0f,0.0f))
{//dt:时间间隔，newParticles:新增粒子数, blockPos:被破碎的方块的位置, offset:粒子偏移量
	for (GLuint i = 0; i < newParticles; ++i)
	{// Add new particles 
		int unusedParticle = this->firstUnusedParticle();
		this->respawnParticle(this->particles[unusedParticle], blockPos, offset);
	}
	
	for (GLuint i = 0; i < this->amount; i++)
	{// Update all particles
		Particle &p = this->particles[i];
		p.Life -= dt; // reduce life
		if (p.Life > 0.0f)
		{	// particle is alive, thus update
			p.Position -= p.Velocity * dt;//粒子位置更新
			p.Color.a -= dt * 2.5;//透明度更新
		}
	}
}

// Render all particles
void ParticleGen::Draw()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);// Use additive blending to give it a 'glow' effect
	this->shader.use();
	for (Particle particle : this->particles)
	{
		if (particle.Life > 0.0f)
		{
			this->shader.set3fv("offset", glm::value_ptr(particle.Position));
			this->shader.set4fv("color", glm::value_ptr(particle.Color));
			this->texture.Bind();
			glBindVertexArray(this->VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
			glBindVertexArray(0);
		}
	}
	// Don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGen::init()
{
	// Set up mesh and attribute properties
	GLuint VBO;
GLfloat particle_quad[] = {
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
// Front face
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
// Left face
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
// Right face
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
// Bottom face
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
// Top face
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left 
};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	// Fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// Set mesh attributes
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)3);//texture coordinate
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	// Create this->amount default particle instances
	for (GLuint i = 0; i < this->amount; ++i)
		this->particles.push_back(Particle());
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGen::firstUnusedParticle()
{
	// First search from last used particle, this will usually return almost instantly
	for (GLuint i = lastUsedParticle; i < this->amount; i++) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (GLuint i = 0; i < lastUsedParticle; i++) {
		if (this->particles[i].Life <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

void ParticleGen::respawnParticle(Particle &particle, glm::vec3 blockPos, glm::vec3 offset)
{//particle:操作的粒子对象，blockPos:被破碎的方块的位置, offset:粒子偏移量
	GLfloat random = ((rand() % 100) - 50) / 10.0f;
	GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
	particle.Position = blockPos + random + offset;
	particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.Life = 1.0f;
	//particle.Velocity = 1.0f;
}