/*
*  File Name : RustKeyController.h
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief:
*  Past(Usable Key) - Present(Rust Key) - Future(Metallic Powder)
	Interact: Usable Key -> Box: open the box
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BaseController.h"
#include "ControllerType.h"
#include "Object.h"

namespace BLUE
{
	class RustKeyController : public BaseController
	{
	public:
		RustKeyController();
		Object *Spawn(float x, float y, float z);
		Object *GetObject();
		Transform *GetTransform();

		void ChangeToFuture(bool CalledAtStart) override;
		void ChangeToPast(bool CalledAtStart) override;
		ControllerType GetControllerType() override;
		void Reset() override;
		void Interact(ControllerType controller_type = ControllerType_NULL) override;
		CurrentState GetCurrentState() override;
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