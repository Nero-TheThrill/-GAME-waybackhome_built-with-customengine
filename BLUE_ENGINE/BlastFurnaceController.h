/*
*  File Name : BlastFurnaceController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Destroy objects
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BaseController.h"

namespace BLUE
{
	class BlastFurnaceController : public BaseController
	{
	public:
		BlastFurnaceController();
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
            void FutureToPresent(bool CalledAtStart);

		CurrentState currentstate;
		Object * obj;
		Transform* transform;
		Rigidbody* rigidbody;
		Rectangle* rectangle;
		Collision* collision;
		Sprite* sprite;
                bool canUse=true;
		ControllerType controllertype;
	};

}
