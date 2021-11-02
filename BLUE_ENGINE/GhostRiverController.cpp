/*
*  File Name : GhostRiverController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief:
*    Past(GhostRiver) - Present(GhostRiver) - Future(GhostRiver)
*    Interact: NO
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"GhostRiverController.h"
#include"ObjectController.h"
#include<iostream>
#include "Archiver.h"

namespace BLUE
{
	GhostRiverController::GhostRiverController()
	{
		controllertype = ControllerType_GHOSTRIVER;
	}

	Object* GhostRiverController::Spawn(float x, float y, float z)
	{

		obj = OBJECT_FACTORY->CreateEmptyObject();
		std::string str("GhostRiver");
		obj->AddComponent(new Transform());
		transform = obj->transform;
		obj->AddComponent(new Rectangle());
		rectangle = obj->rectangle;
		obj->AddComponent(new Collision());
		collision = obj->collision;
		obj->AddComponent(new Rigidbody());
		rigidbody = obj->rigidbody;
		obj->AddComponent(new Sprite());
		sprite = obj->sprite;
		obj->SetName(str);
		obj->Init();
		canMove = false;
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 1280,200 });
		//sprite->SetTexture("texture/ghostriver.png");
		sprite->SetColor({ 0, 0, 0, 0 });
		isInInventory = false;
		OBJECT_CONTROLLER->AddObject(obj);
		GRAPHICS->AddSprite(sprite);
		call_once = 0;
		return obj;
	}

	Object * GhostRiverController::GetObject()
	{
		return obj;
	}

	Transform * GhostRiverController::GetTransform()
	{
		return transform;
	}

	void GhostRiverController::ChangeToFuture(bool /*CalledAtStart*/)
	{
	}

	void GhostRiverController::ChangeToPast(bool /*CalledAtStart*/)
	{
	}


	ControllerType GhostRiverController::GetControllerType()
	{
		return controllertype;
	}

	void GhostRiverController::Reset()
	{

	}

	void GhostRiverController::Interact(ControllerType /*controller_type*/)
	{
	}
	CurrentState GhostRiverController::GetCurrentState()
	{
		return currentstate;
	}

    void GhostRiverController::HitPoison()
    {
    }
}
