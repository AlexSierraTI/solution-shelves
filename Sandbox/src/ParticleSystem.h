#pragma once

#include <SolutionShelves.h>

struct ParticleProps
{
	glm::vec2 Position = glm::vec2(1.0f) = glm::vec2(1.0f);
	glm::vec2 Velocity = glm::vec4(1.0f), VelocityVariation = glm::vec2(1.0f);
	glm::vec4 ColorBegin = glm::vec4(1.0f), ColorEnd = glm::vec4(1.0f);
	float SizeBegin = 0.0f, SizeEnd = 0.0f, SizeVariation = 0.0f;
	float LifeTime = 1.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(uint32_t maxParticles = 1500);

	void OnUpdate(SolutionShelves::Timestep ts);
	void OnRender(SolutionShelves::Camera& camera);

	void Emit(const ParticleProps& particleProps);
private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex;
};