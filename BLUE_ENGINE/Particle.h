/*
*  File Name : Particle.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: Particle system
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <vector>
#include "Texture.h"
#include "Rigidbody.h"
#include "Sprite.h"

namespace BLUE
{
	enum class ParticleType
	{
		Follow,
		Explosion,
		Continue
	};

	class ParticleGenerator
	{
	public:
		// Constructor
		ParticleGenerator();
		ParticleGenerator(unsigned int amount_, float lifetime_, Rigidbody* rigidbody_, ParticleType particle_types);
		// Init
		void Init();

		// Update all particles
		void Update();

		// spawn until amount of particle
		void Spawn(unsigned int amount_, float lifetime_, Rigidbody* rigidbody_, ParticleType particle_types);

		void SetLifeTime(unsigned int time);

		void SetTexture(const std::string &texture_path = "");

		void SetOffset(float num);

		void DestroyAllParticle();

		void SetScale(float x, float y);

		void DeleteParticle(int index);

		unsigned int GetAmount();
	private:
		// how many particles need to generate
		unsigned int amount = 0;
		float init_lifetime = 0;

		glm::vec2 scale_;

		// live time for particle
		std::vector<float> lifetime;

		// set of particle
		std::vector<Object*> particles;

		std::vector<Transform*> transform;
		std::vector<Rigidbody*> rigidbody;
		std::vector<Sprite*> sprite;
		std::string texture_path_;
		Rigidbody* parent_rigidbody_;

		float rand_pos = 0.f;
		Color rColor;
		std::vector<glm::vec2> rand_vec;
		std::vector<float> rand_for_sign;
		float offset = 0.f;

		float dt = 0.1f;

		ParticleType types_;
	};
}
