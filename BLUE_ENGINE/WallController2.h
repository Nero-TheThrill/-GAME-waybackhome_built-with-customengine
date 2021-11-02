/*
*  File Name : WallController2.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  brief :
*		Cannot go through the wall
*		Past(Wall) - Present(Wall) - Future(Wall)
*		Interact: Nothing
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BaseController.h"
#include "ControllerType.h"
#include "Object.h"

namespace BLUE
{
	class Wall2 : public BaseController
	{
	public:
		Wall2();
		Object *Spawn(float x, float y, float z);
		Object *GetObject();
		Transform *GetTransform();

		void SetWall2Scale(float width, float height);
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
