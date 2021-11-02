/*
*  File Name : PlayerController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief:  Control player class. To make code simple.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "ObjectFactory.h"
#include "Graphics.h"
#include "Object.h"
namespace BLUE
{
	namespace Inventory
	{
		static constexpr glm::vec3 location = { 555.f, -280.f,960.f };
		static constexpr glm::vec2 scale = { 100.f,100.f };
	}

	namespace Player
	{
		static constexpr float speed = 5.f;
		static constexpr glm::vec2 collision_scale = { 65.f,65.f };
	}
	class PlayerController
	{
	public:
		PlayerController();
		Object* Spawn();
		void update();
		void movedown() const;
		void moveup() const;
		void moveleft();
		void moveright();
		void resetdown();
		void resetup();
		void resetleft();
		void resetright();
                void reset();
		void FindCollideItem(Object* object);
		void interaction();
		Transform* GetTransform() const;
		bool GetInventoryState() const;
		void SetInventoryState(bool can_using_invectory);
		void CheckCollide();
		Object *GetObject() const;
		void RotatePlayer(float cameraposx, float cameraposy) const;
		void ReplayRotatePlayer(glm::vec2 mousePos, glm::vec2 cameraPos) const;
		bool isClearTheGame = false;
		bool isDead = false;
		void SetPosition(glm::vec3 trans);
		void SetRotate(float rot);
                bool CanUsingInventory = true;
                int usedBullet;
	private:


		Object * obj;
		Transform* transform;
		Rigidbody* rigidbody;
		Rectangle* rectangle;
		Object * item;
		Collision* collision;
		OBB_Collision * obb;
	
	};
	extern PlayerController* PLAYER_CONTROLLER;
}
