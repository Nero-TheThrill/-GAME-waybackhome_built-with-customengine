/*
*  File Name : LogController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief:
*    Past(Log) - Present(Log) - Future(Log)
*    Interact: Cannot cross river -> Can cross river.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include"BaseController.h"
#include"ControllerType.h"

namespace BLUE
{
	class LogController : public BaseController
	{
	public:
		LogController();
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
		CurrentState currentstate;
		Object * obj;
		Transform* transform;
		Rigidbody* rigidbody;
		Rectangle* rectangle;
		Collision* collision;
		Sprite* sprite;
		bool isUsed = false;
		ControllerType controllertype;
	};
}
