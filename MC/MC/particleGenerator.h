#pragma once
#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include"Shader.h"
#include"Texture.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Particle {// Represents a single particle and its state
	glm::vec3 Position, Velocity;//粒子速度，位置
	glm::vec4 Color;//粒子颜色
	GLfloat Life;//粒子生命时长

	Particle() : Position(0.0f), Velocity(glm::vec3(0.1f,0.1f,0.1f)), Color(1.0f), Life(0.0f) { }
};
class ParticleGen {
public:
	ParticleGen(Shader& shader, Texture& texture, GLuint amount);//ctor
	// Update all particles
	void Update(GLfloat dt, glm::vec3 blockPos, GLuint newParticles, glm::vec3 offset);
	void Draw();// Render all particles
private:
	// State
	std::vector<Particle> particles;
	GLuint amount;
	// Render state
	Shader shader;
	Texture texture;
	GLuint VAO;

	void init();// Initializes buffer and vertex attributes
	GLuint firstUnusedParticle();//get the first unused particle
	// Respawns particle
	void respawnParticle(Particle &particle, glm::vec3 blockPos, glm::vec3 offset);
};
#endif // !PARTICLEGENERATOR_H
