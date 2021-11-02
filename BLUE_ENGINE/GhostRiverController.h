/*
*  File Name : GhostRiverController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief:
*    Past(GhostRiver) - Present(GhostRiver) - Future(GhostRiver)
*    Interact: NO
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include"BaseController.h"
#include"ControllerType.h"

namespace BLUE
{
	class GhostRiverController : public BaseController
	{
	public:
		GhostRiverController();
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
		CurrentState currentstate;
		Object * obj;
		Transform *transform;
		Rigidbody *rigidbody;
		Rectangle *rectangle;
		Collision *collision;
		Sprite* sprite;
		ControllerType controllertype;
		unsigned call_once = 0;
	};
}
