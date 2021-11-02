/*
*  File Name : TreeController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jina Hyun
*  Brief:
*    Past(Seed) - Present(Tree) - Future(Tree)
*    Interact: Axe -> Change tree to log
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "BaseController.h"
#include"ControllerType.h"
#include"JSONWRITER.h"

namespace BLUE
{
	class TreeController : public BaseController
	{
	public:
		TreeController();
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
            void PresentToPast(bool CalledAtStart);

		void CreateItem(ControllerType type) const;
		void DeleteThis();
		CurrentState currentstate;
		bool isUsed = false;
		Object * obj;
		Transform* transform;
		Rigidbody* rigidbody;
		Rectangle* rectangle;
		Collision* collision;
		Sprite* sprite;
		ControllerType controllertype;
		rapidjson::JSONwriter* JSONWRITER;
	};
}
