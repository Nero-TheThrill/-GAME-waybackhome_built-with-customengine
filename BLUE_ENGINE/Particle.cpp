/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
/*
*  File Name : Particle.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: Particle system
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Particle.h"
#include "Archiver.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

namespace BLUE
{
	ParticleGenerator::ParticleGenerator()
	{
		parent_rigidbody_ = nullptr;
	}
	ParticleGenerator::ParticleGenerator(unsigned int amount_, float lifetime_, Rigidbody* rigidbody_, ParticleType particle_types)
		: amount(amount_), init_lifetime(lifetime_), parent_rigidbody_(rigidbody_), types_(particle_types)
	{
	}

	void ParticleGenerator::Init()
	{
		particles.push_back(OBJECT_FACTORY->CreateEmptyObject());
		transform.push_back(new Transform());
		rigidbody.push_back(new Rigidbody());
		sprite.push_back(new Sprite());
		lifetime.push_back(init_lifetime);

		particles[amount]->SetName("Particle");
		particles[amount]->AddComponent(transform[amount]);
		particles[amount]->AddComponent(rigidbody[amount]);
		particles[amount]->AddComponent(sprite[amount]);
		particles.at(amount)->Init();

		GRAPHICS->AddSprite(sprite[amount]);
		sprite[amount]->SetTexture(texture_path_);
		transform[amount]->SetScaleX(static_cast<int>(scale_.x));
		transform[amount]->SetScaleY(static_cast<int>(scale_.y));
		//srand(time(NULL));
		rand_pos = static_cast<float>(rand() % 20);
		rColor = { static_cast<unsigned>(rand() % 255), static_cast<unsigned>(rand() % 255), static_cast<unsigned>(rand() % 255) };
		float rand_for_vec_x = static_cast<float>(rand() % 99);
		float rand_for_vec_y = static_cast<float>(rand() % 99);
		rand_vec.push_back({ rand_for_vec_x / 10.f, rand_for_vec_y / 10.f });
		rand_for_sign.push_back(static_cast<float>(rand() % 4));

		if (rand_for_sign.at(amount) == 1)
			transform.at(amount)->SetTranslation(parent_rigidbody_->transform->GetTranslation() + rand_pos + offset);
		else
			transform.at(amount)->SetTranslation(parent_rigidbody_->transform->GetTranslation() - rand_pos + offset);

		transform.at(amount)->SetTranslation({ transform.at(amount)->GetTranslation().x, transform.at(amount)->GetTranslation().y, 0 });
		rigidbody.at(amount)->velocity = parent_rigidbody_->velocity;
		amount = static_cast<unsigned>(lifetime.size());
	}

	void ParticleGenerator::Update()
	{
		if (particles.size() == 0)
		{
			return;
		}
		if (amount <= 0)
		{
			return;
		}
		for (int i = amount - 1; i >= 0; --i)
		{
			//random = ((rand() % 100) - 50) / 10.0f;
			//rColor = 0.5 + ((rand() % 100) / 100.0f);
			//transform.at(i)->SetTranslation(parent_rigidbody_->transform->GetTranslation() + random + offset);
			//sprite[i]->SetColor({ rColor, rColor, rColor, 1.0f });
			rigidbody.at(i)->velocity = parent_rigidbody_->velocity;
			switch (types_)
			{
			case ParticleType::Follow:
			{
				lifetime[i] -= dt; // reduce life
				if (lifetime[i] > 0.0f)
				{
					// particle is alive, thus update
					transform[i]->SetTranslation(transform[i]->GetTranslation() -= glm::vec3{ rigidbody[i]->velocity.x, rigidbody[i]->velocity.y, 0.1f });

					Color temp_color = sprite[i]->GetMesh().GetColor(0);
					if (temp_color.alpha - 15 > 0)
							sprite[i]->SetColor({ temp_color.red, temp_color.green, temp_color.blue, temp_color.alpha - 15 });
				}
				else
				{
					DeleteParticle(i);
				}
				amount = static_cast<unsigned>(particles.size());
			}
			break;
			case ParticleType::Explosion:
			{
				lifetime[i] -= dt; // reduce life
				if (lifetime[i] > 0.0f)
				{
					Color temp_color = sprite[i]->GetMesh().GetColor(0);
					//if (temp_color.alpha - 7 > 0)
					//		sprite[i]->SetColor({ temp_color.red, temp_color.green, temp_color.blue, temp_color.alpha - 7});
					if (rand_for_sign[i] == 0)
						transform[i]->SetTranslation(transform[i]->GetTranslation() += glm::vec3{ rand_vec[i].x, rand_vec[i].y, 0 });
					else if (rand_for_sign[i] == 1)
						transform[i]->SetTranslation(transform[i]->GetTranslation() += glm::vec3{ rand_vec[i].x, -rand_vec[i].y, 0 });
					else if (rand_for_sign[i] == 2)
						transform[i]->SetTranslation(transform[i]->GetTranslation() -= glm::vec3{ rand_vec[i].x, -rand_vec[i].y, 0 });
					else if (rand_for_sign[i] == 3)
						transform[i]->SetTranslation(transform[i]->GetTranslation() -= glm::vec3{ rand_vec[i].x, rand_vec[i].y, 0 });
				}
				else
				{
					DeleteParticle(i);
				}
				amount = static_cast<unsigned>(particles.size());
			}
			break;
			case ParticleType::Continue:
			{
				amount = static_cast<unsigned>(particles.size());
			}
			break;
			}
		}
	}

	void ParticleGenerator::Spawn(unsigned int amount_, float lifetime_, Rigidbody* rigidbody_, ParticleType particle_types)
	{
		types_ = particle_types;
		amount = static_cast<unsigned>(lifetime.size());
		init_lifetime = lifetime_;
		parent_rigidbody_ = rigidbody_;
		for (unsigned int i = 0; i < amount_; ++i)
		{
			Init();
		}
	}

	void ParticleGenerator::SetLifeTime(unsigned int time)
	{
		for (unsigned int i = 0; i < amount; ++i)
		{
			lifetime[i] = static_cast<float>(time);
		}
	}

	void BLUE::ParticleGenerator::SetTexture(const std::string & texture_path)
	{
		texture_path_ = texture_path;
	}

	void BLUE::ParticleGenerator::SetOffset(float num)
	{
		offset = num;
	}

	void ParticleGenerator::DestroyAllParticle()
	{
		for (unsigned int i = 0; i < amount; ++i)
		{
			GRAPHICS->DeleteSprite(sprite.at(i));
			particles.at(i)->Destroy(particles.at(i));
		}
		particles.clear();
		sprite.clear();
		transform.clear();
		rigidbody.clear();
		lifetime.clear();
		rand_vec.clear();
		rand_for_sign.clear();
		amount = 0;
	}

	void BLUE::ParticleGenerator::SetScale(float x, float y)
	{
		scale_ = { x, y };
	}

	void BLUE::ParticleGenerator::DeleteParticle(int index)
	{
		GRAPHICS->DeleteSprite(sprite.at(index));
		particles.at(index)->Destroy(particles.at(index));
		particles.erase(particles.begin() + index);
		sprite.erase(sprite.begin() + index);
		transform.erase(transform.begin() + index);
		rigidbody.erase(rigidbody.begin() + index);
		lifetime.erase(lifetime.begin() + index);
		rand_vec.erase(rand_vec.begin() + index);
		rand_for_sign.erase(rand_for_sign.begin() + index);
	}

	unsigned int BLUE::ParticleGenerator::GetAmount()
	{
		return amount;
	}

}
