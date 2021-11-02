/*
*  File Name : TorchController.cpp
*  Primary Author : Park Jinwon
*  Brief:
*  Past(Wood Stick) - Present(Torch) - Future(Burn Out Torch)
	Interact: Wood Stick + Bonfire = Torch
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "TorchController.h"
#include "ObjectController.h"
#include <iostream>
#include "Archiver.h"
#include "TestLevel1.h"
#include "SmokeEffects.h"
#include "Audio.h"
#include "WoodBoardController.h"
#include "AxeController.h"

namespace BLUE
{
	TorchController::TorchController() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_TORCH),
		canUse(false),
		currentstate(PRESENT)
	{
	}

	Object* TorchController::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Torch");
		object->AddComponent(new Transform());
		transform = object->transform;
		object->AddComponent(new Rectangle());
		rectangle = (object->rectangle);
		object->AddComponent(new Sprite());
		sprite = (object->sprite);
		object->AddComponent(new Collision());
		collision = (object->collision);
		object->AddComponent(new Rigidbody());
		rigidbody = (object->rigidbody);
		object->Init();
		canMove = true;
		isUsed = false;
		sprite->SetTexture(T(Picture::Item_Torch));
		transform->SetTranslation({ x, y, z });
		transform->SetScale({ 35.f, 122.f });
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);

		return object;
	}

	Object* TorchController::GetObject()
	{
		return object;
	}

	Transform* TorchController::GetTransform()
	{
		return transform;
	}

	void TorchController::ChangeToFuture(bool CalledAtStart)
	{
		if (currentstate == PAST)
			PastToPresent(CalledAtStart);
		else if (currentstate == PRESENT)
			PresentToFuture(CalledAtStart);
	}

	void TorchController::ChangeToPast(bool CalledAtStart)
	{
		if (currentstate == PRESENT)
			PresentToPast(CalledAtStart);
		else if (currentstate == FUTURE)
			FutureToPresent(CalledAtStart);
	}

	ControllerType TorchController::GetControllerType()
	{
		return controllerType;
	}

	void TorchController::Reset()
	{
	}

	void TorchController::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
			// when it release from inventory ( When the user tries to use item in inventory)
		case ControllerType_NULL:
                    if(isInInventory)
                    {
                        BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(object, ControllerType_ANYTHING);

                        if (collided_controller != nullptr)
                        {
							if (collided_controller->GetControllerType() == ControllerType_RIVER)
							{
								AUDIO_MANAGER->PlaySound("putlog");
								OBJECT_CONTROLLER->DeleteController(this);
								GRAPHICS->DeleteSprite(sprite);
								OBJECT_FACTORY->Destroy(object);
							}
							else if (currentstate == PRESENT)
                            {
								if (collided_controller->GetControllerType() == ControllerType_VINE)
								{
									collided_controller->Interact(controllerType);
									GRAPHICS->DeleteSprite(sprite);
									OBJECT_CONTROLLER->DeleteController(this);
									OBJECT_FACTORY->Destroy(object);
								}
								else if (collided_controller->GetControllerType() == ControllerType_TREE)
								{
									collided_controller->Interact(controllerType);
									GRAPHICS->DeleteSprite(sprite);
									OBJECT_CONTROLLER->DeleteController(this);
									OBJECT_FACTORY->Destroy(object);
								}
								else if (collided_controller->GetControllerType() == ControllerType_LOG)
								{
									collided_controller->Interact(controllerType);
									GRAPHICS->DeleteSprite(sprite);
									OBJECT_CONTROLLER->DeleteController(this);
									OBJECT_FACTORY->Destroy(object);
								}
								else if (collided_controller->GetControllerType() == ControllerType_WOODBOARD)
								{
									collided_controller->Interact(controllerType);
									GRAPHICS->DeleteSprite(sprite);
									OBJECT_CONTROLLER->DeleteController(this);
									OBJECT_FACTORY->Destroy(object);
								}
								else if (collided_controller->GetControllerType() == ControllerType_BLASTFURNACE&& collided_controller->GetCurrentState()==PAST)
								{
									AUDIO_MANAGER->PlaySound("fire");
									collided_controller->Interact(controllerType);
									GRAPHICS->DeleteSprite(sprite);
									OBJECT_CONTROLLER->DeleteController(this);
									OBJECT_FACTORY->Destroy(object);
								}
							}
							else if (currentstate == PAST)
							{
								if(collided_controller->GetControllerType() == ControllerType_RUSTKEY&& collided_controller->GetCurrentState()==PAST)
								{
									AUDIO_MANAGER->PlaySound("changeitem");
									collided_controller->Interact(controllerType);
									GRAPHICS->DeleteSprite(sprite);
									OBJECT_CONTROLLER->DeleteController(this);
									OBJECT_FACTORY->Destroy(object);
								}
								if (collided_controller->GetControllerType() == ControllerType_BLASTFURNACE && collided_controller->GetCurrentState() == PRESENT)
								{
									AUDIO_MANAGER->PlaySound("fire");
									collided_controller->Interact(controllerType);
									GRAPHICS->DeleteSprite(sprite);
									OBJECT_CONTROLLER->DeleteController(this);
									OBJECT_FACTORY->Destroy(object);
								}
							}


                        }
                    }
					break;
		case ControllerType_RUSTKEY:
		{	AUDIO_MANAGER->PlaySound("changeitem");
			AxeController* axecontroller = new AxeController;
			axecontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y, transform->GetTranslation().z);
			GRAPHICS->DeleteSprite(sprite);
			OBJECT_CONTROLLER->AddController(axecontroller);
			OBJECT_CONTROLLER->DeleteController(this);

			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
			break;
		}
		default:
			break;
		}
	}
	CurrentState TorchController::GetCurrentState()
	{
		return currentstate;
	}

	void TorchController::HitPoison()
	{
	}

	void TorchController::PastToPresent(bool CalledAtStart)
	{
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Torch));
		transform->SetScale({ 35.f, 122.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}

	void TorchController::PresentToPast(bool CalledAtStart)
	{
		currentstate = PAST;
		sprite->SetTexture(T(Picture::Item_Torch_Yet));
		transform->SetScale({ 17.f, 76.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void TorchController::PresentToFuture(bool CalledAtStart)
	{
		currentstate = FUTURE;
		sprite->SetTexture(T(Picture::Item_Torch_Burned));
		transform->SetScale({ 14.f, 70.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void TorchController::FutureToPresent(bool CalledAtStart)
	{
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Torch));
		transform->SetScale({ 35.f, 122.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}
}
