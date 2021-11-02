/*
*  File Name : SeedController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jina Hyun
*  Brief:
*    Past(Seed) - Present(Seed) - Future(Tree)
*    Interact: No Interact
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include"BaseController.h"
#include"ControllerType.h"
#include"JSONWRITER.h"

namespace BLUE
{
	class SeedController : public BaseController
	{
	public:
		SeedController();
		Object* Spawn(float x, float y, float z) override;
		Object* GetObject();
		Transform* GetTransform();
		void ChangeToFuture(bool CalledAtStart) override;
		void ChangeToPast(bool CalledAtStart) override;
		ControllerType GetControllerType() override;
		void Reset() override;
		void Interact(ControllerType controller_type) override;
		CurrentState GetCurrentState() override;
                void HitPoison() override;
	private:
            void PastToPresent(bool CalledAtStart);
		void PresentToPast(bool CalledAtStart);
		void PresentToFuture(bool CalledAtStart);
		bool canUse;
		bool isUsed = false;
		CurrentState currentstate;
		Object * obj;
		Transform* transform;
		Rigidbody* rigidbody;
		Rectangle* rectangle;
		Collision* collision;
		Sprite* sprite;
		ControllerType controllertype;
		rapidjson::JSONwriter* JSONWRITER;
	};
}
