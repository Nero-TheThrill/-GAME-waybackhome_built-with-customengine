/*
*  File Name : BoxController.h
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief:
*	Past(Box) - Present(Box) - Future(Box)
*	Interact: Usable Key -> Box: open the box
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BaseController.h"
#include "ControllerType.h"
#include "Object.h"

namespace BLUE
{
	class BoxController : public BaseController
	{
	public:
		BoxController();
		Object *Spawn(float x, float y, float z);
		Object *GetObject();
		Transform *GetTransform();

		void ChangeToFuture(bool CalledAtStart) override;
		void ChangeToPast(bool CalledAtStart) override;
		ControllerType GetControllerType() override;
		void Reset() override;
		void Interact(ControllerType controller_type = ControllerType_NULL) override;
		CurrentState GetCurrentState() override;
		void SetItemType(ControllerType type);
                void HitPoison() override;
                bool GetIsOpen();
	private:
		void CreateItem() const;

		CurrentState currentstate;
		Object * object;
		Transform *transform;
		Rigidbody *rigidbody;
		Rectangle *rectangle;
		Collision *collision;
		Sprite *sprite;
		ControllerType controllerType;

		ControllerType itemType;
		bool isOpen;
	};
}
