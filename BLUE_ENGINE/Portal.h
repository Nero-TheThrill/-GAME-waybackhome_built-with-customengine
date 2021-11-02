/*
*  File Name : Portal.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:
*  Determine whether the game is cleared or not.
	(If the player collide with this object, it means he clear the game)
	Past(Potal) - Present(Potal) - Future(Potal)
	Interact: Player -> Potal: clear the game

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BaseController.h"
#include "ControllerType.h"
#include "Object.h"

namespace BLUE
{
	class Portal : public BaseController
	{
	public:
		Portal();
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
