/*
*  File Name : PoisonplantController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Past(Poison Sprout) - Present(Poison Plant) - Future(Dead Poison Plant)
		Interact : 

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#pragma once
#include "BaseController.h"
#include "ControllerType.h"
#include "Object.h"

namespace BLUE
{
	class PoisonplantController : public BaseController
	{
	public:
		PoisonplantController();
		Object *Spawn(float x, float y, float z);
		Object *Spawn(float x, float y, float z, glm::vec2 direction);
		Object *GetObject();
		Transform *GetTransform();

		void ChangeToFuture(bool CalledAtStart) override;
		void ChangeToPast(bool CalledAtStart) override;
		ControllerType GetControllerType() override;
		void Reset() override;
		void Interact(ControllerType controller_type = ControllerType_NULL) override;
		CurrentState GetCurrentState() override;
		void ShootPoision(glm::vec2 position);
                void HitPoison() override;

	private:
		void PastToPresent(bool CalledAtStart);
		void PresentToPast(bool CalledAtStart);
		void PresentToFuture(bool CalledAtStart);
		void FutureToPresent(bool CalledAtStart);

		Object *object;
		Transform *transform;
		Rigidbody *rigidbody;
		Rectangle *rectangle;
		Collision *collision;
		Sprite *sprite;
		ControllerType controllerType;
		bool isUsed;
		bool canUse;
		CurrentState currentstate;

	};
}