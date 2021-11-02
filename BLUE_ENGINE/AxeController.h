/*
*  File Name : AxeController.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:
*       Past(Axe) - Present(Axe) - Future(Axe)
*		Interact: Axe -> Tree: make tree to log
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/


#pragma once
#include "BaseController.h"
#include "ControllerType.h"
#include "Object.h"

namespace BLUE
{
	class AxeController : public BaseController
	{
	public:
		AxeController();
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
            void PresentToPast(bool CalledAtStart);
            void PresentToFuture(bool CalledAtStart);
            void FutureToPresent(bool CalledAtStart);

		bool IsUsed = false;
		CurrentState currentstate;
		Object * object;
		Transform *transform;
		Rigidbody *rigidbody;
		Rectangle *rectangle;
		Collision *collision;
		Sprite *sprite;
		ControllerType controllerType;
	};
}
