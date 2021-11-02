/*
*  File Name : BoxController.cpp
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief:
* 	Past(Box) - Present(Box) - Future(Box)
*	Interact: Usable Key -> Box: open the box
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "BoxController.h"
#include "ObjectController.h"
#include "ObjectFactory.h"
#include <iostream>
#include "AxeController.h"
#include "SmokeEffects.h"
#include "Audio.h"
#include "Graphics.h"

namespace BLUE
{
	BoxController::BoxController() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_BOX),
		itemType(ControllerType_AXE),
		isOpen(false)
	{
	}

	Object* BoxController::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Box");
		object->AddComponent(new Transform());
		transform = (object->transform);
		object->AddComponent(new Rectangle());
		rectangle = (object->rectangle);
		object->AddComponent(new Sprite());
		sprite = (object->sprite);
		object->AddComponent(new Collision());
		collision = (object->collision);
		object->AddComponent(new Rigidbody());
		rigidbody = (object->rigidbody);
		object->Init();
		canMove = false;
		sprite->SetTexture(T(Picture::Item_Box_Closed));
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 100.f, 110.f});
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);
		return object;
	}

	Object* BoxController::GetObject()
	{
		return object;
	}

	Transform* BoxController::GetTransform()
	{
		return transform;
	}

	void BoxController::ChangeToFuture(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with box (FUTURE)\n";
	}

	void BoxController::ChangeToPast(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with box (PAST)\n";
	}

	ControllerType BoxController::GetControllerType()
	{
		return controllerType;
	}

	void BoxController::Reset()
	{
	}

	void BoxController::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
		case ControllerType_RUSTKEY:
		{
			if (!isOpen)
			{
				AUDIO_MANAGER->PlaySound("openbox");
				sprite->SetTexture(T(Picture::Item_Box_Opened));
				isOpen = true;
				//std::cout << "Box is opened!\n";
				SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
				CreateItem();
			}
			//else
			//{
			//	sprite->SetTexture(T(Picture::Item_Box_Closed));
			//	isOpen = false;
			//	SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			//	std::cout << "Box is closed!\n";
			//}

		}
		default:
			break;
		}
	}

	CurrentState BoxController::GetCurrentState()
	{
		return currentstate;
	}

	void BoxController::SetItemType(ControllerType type)
	{
		itemType = type;
	}

    void BoxController::HitPoison()
    {
    }

    bool BoxController::GetIsOpen()
    {
        return isOpen;
    }


    void BoxController::CreateItem() const
	{
		BaseController * controller = nullptr;

		switch (itemType)
		{
		case ControllerType_AXE:
		{
			//std::cout << "Found an ax in the box!\n";
			controller = new AxeController;
		}
		break;
		default:
			break;
		}

		controller->Spawn(transform->GetTranslation().x - 50.f, transform->GetTranslation().y, transform->GetTranslation().z + 1);
		OBJECT_CONTROLLER->AddController(controller);
	}
}
