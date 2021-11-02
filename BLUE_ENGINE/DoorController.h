/*
*  File Name : DoorController.cpp
*  Primary Author : JinWon Park
*  Secondary Author :
*  Brief: Door 
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#pragma once
#include "BaseController.h"

namespace BLUE
{
	//enum Ctype
	//{
	//	ControllerType_SEED,
	//	ControllerType_RUSTKEY,
	//	ControllerType_AXE,
	//	ControllerType_LOG,
	//	ControllerType_POISONPLANT
	//};

	class DoorController : public BaseController
	{
	public:
		DoorController();
		Object* Spawn(float x, float y, float z) override;
		Object* GetObject();
		Transform* GetTransform();
		void ChangeToFuture(bool CalledAtStart) override;
		void ChangeToPast(bool CalledAtStart) override;
		ControllerType GetControllerType() override;
		void Reset() override;
		void Interact(ControllerType controller_type) override;
		CurrentState GetCurrentState() override;
		void SetItemType(const ControllerType ctype);
		ControllerType GetItemType() const;
                void HitPoison() override;
				bool isDead = false;
	private:
		ControllerType item_type = ControllerType_RUSTKEY;

		CurrentState currentstate;
		Object * obj;
		Sprite * type_sprite;
		Transform* transform;
		Rigidbody* rigidbody;
		Rectangle* rectangle;
		Collision* collision;
		Sprite* sprite;
		ControllerType controllertype;

		//Ctype ctype;
	};
	extern DoorController* DOOR_CONTROLLER;
}
