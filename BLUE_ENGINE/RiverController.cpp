/*
*  File Name : RiverController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief:
*    Past(River) - Present(River) - Future(River)
*    Interact: Log -> Change Log size
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"RiverController.h"
#include"ObjectController.h"
#include<iostream>
#include "Archiver.h"
#include "GhostRiverController.h"
#include "LogController.h"
#include "WoodBoardController.h"

namespace BLUE
{
	RiverController::RiverController()
	{
		controllertype = ControllerType_RIVER;
	}

	Object* RiverController::Spawn(float x, float y, float z)
	{

		obj = OBJECT_FACTORY->CreateEmptyObject();
		std::string str1("River");
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
		obj->SetName(str1);
		obj->Init();
		sprite->SetTexture(T(Picture::Item_River));
		sprite->SetAnimation()->ActivateAnimation();
		sprite->SetAnimation()->SetFrame(1, 4);
		sprite->SetAnimation()->SetSpeed(30);
		currentstate = PRESENT;
		canMove = false;
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 2560,200 });
		GRAPHICS->AddSprite(sprite);
		OBJECT_CONTROLLER->AddObject(obj);
		call_once = 0;
		return obj;
	}

	Object * RiverController::GetObject()
	{
		return obj;
	}

	Transform * RiverController::GetTransform()
	{
		return transform;
	}

	void RiverController::ChangeToFuture(bool /*CalledAtStart*/)
	{
	}

	void RiverController::ChangeToPast(bool /*CalledAtStart*/)
	{
	}


	ControllerType RiverController::GetControllerType()
	{
		return controllertype;
	}

	void RiverController::Reset()
	{

	}

	void RiverController::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
			// when it release from inventory ( When the user tries to use item in inventory)
		case ControllerType_NULL:
		{
		}
		break;
		case ControllerType_WOODBOARD:
		{
			//make two objects in ghost river controller and split it when collide with LOG and make y value same 

			BaseController* ctrl = OBJECT_CONTROLLER->GetCollideWith(obj, ControllerType_WOODBOARD);
			ControllerType ctype = ctrl->GetControllerType();

			if (ctype == ControllerType_WOODBOARD)
			{

				GhostRiverController* ghost_river_controller1 = new GhostRiverController();
				float x = ((dynamic_cast<WoodBoardController*>(ctrl))->GetObject()->transform)->GetTranslation().x + 690;
				float y = transform->GetTranslation().y;

				ghost_river_controller1->Spawn(x, y, -3);

				OBJECT_CONTROLLER->AddController(ghost_river_controller1);
				GhostRiverController* ghost_river_controller2 = new GhostRiverController();
				ghost_river_controller2->Spawn(x - 1370, y, -3);

				OBJECT_CONTROLLER->AddController(ghost_river_controller2);

				(dynamic_cast<WoodBoardController*>(ctrl))->GetTransform()->SetTranslation(
					{ ((dynamic_cast<WoodBoardController*>(ctrl))->GetObject()->transform)->GetTranslation().x, transform->GetTranslation().y,-3 });





				Object* justspriteobj = OBJECT_FACTORY->CreateEmptyObject();
				Transform* tmptransform = new Transform();
				justspriteobj->AddComponent(tmptransform);
				Sprite* tmpsprite = new Sprite();
				justspriteobj->AddComponent(tmpsprite);
				justspriteobj->Init();
				tmpsprite->SetTexture(T(Picture::Item_River));
				tmptransform->SetTranslation({ transform->GetTranslation().x,transform->GetTranslation().y,-2 });
				tmptransform->SetScale(transform->GetScale());
				tmpsprite->SetAnimation()->ActivateAnimation();
				tmpsprite->SetAnimation()->SetFrame(1, 4);
				tmpsprite->SetAnimation()->SetSpeed(30);
				OBJECT_CONTROLLER->DeleteController(this);
				GRAPHICS->DeleteSprite(sprite);
				OBJECT_FACTORY->Destroy(obj);

			}


		}
		break;
		default:
			break;
		}

	}
	CurrentState RiverController::GetCurrentState()
	{
		return currentstate;
	}

    void RiverController::HitPoison()
    {
    }
}


