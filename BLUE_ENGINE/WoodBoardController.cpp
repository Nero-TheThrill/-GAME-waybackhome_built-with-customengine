/*
*  File Name : WoodBoardController.cpp
*  Primary Author : Park Jinwon
*  Brief:
*  Past(Log) - Present(Wood Board) - Future(Broken Wood Board)
	Interact: River + Wood Board = Bridge on river
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "WoodBoardController.h"
#include "ObjectController.h"
#include <iostream>
#include "Archiver.h"
#include "TestLevel1.h"
#include "SmokeEffects.h"
#include "Audio.h"
#include "LogController.h"
#include "AxeController.h"
#include "TorchController.h"

namespace BLUE
{
	WoodBoardController::WoodBoardController() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_WOODBOARD),
		canUse(false),
		currentstate(PRESENT)
	{
	}

	Object* WoodBoardController::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("WoodBoard");
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
		sprite->SetTexture(T(Picture::Item_WoodBoard));
		transform->SetTranslation({ x, y, z });
		transform->SetScale({ 100.f, 46.f});
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);

		return object;
	}

	Object* WoodBoardController::GetObject()
	{
		return object;
	}

	Transform* WoodBoardController::GetTransform()
	{
		return transform;
	}

	void WoodBoardController::ChangeToFuture(bool CalledAtStart)
	{
		if (currentstate == PAST)
			PastToPresent(CalledAtStart);
		else if (currentstate == PRESENT)
			PresentToFuture(CalledAtStart);
	}

	void WoodBoardController::ChangeToPast(bool CalledAtStart)
	{
		if (currentstate == PRESENT)
			PresentToPast(CalledAtStart);
		else if (currentstate == FUTURE)
			FutureToPresent(CalledAtStart);
	}

	ControllerType WoodBoardController::GetControllerType()
	{
		return controllerType;
	}

	void WoodBoardController::Reset()
	{
	}

	void WoodBoardController::Interact(ControllerType controller_type)
	{
            switch (controller_type)
            {
            case ControllerType_NULL:
                if (isInInventory)
                {
                    BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(object, ControllerType_ANYTHING);

                    if (collided_controller != nullptr)
                    {
                        if (currentstate == PRESENT)
                        {
							ControllerType cType = collided_controller->GetControllerType();
							if (cType == ControllerType_RIVER)
							{
								AUDIO_MANAGER->PlaySound("putlog");
								collided_controller->Interact(controllerType);
								canMove = false;
								Object* justspriteobj = OBJECT_FACTORY->CreateEmptyObject();
								Transform* tmptransform = new Transform();
								justspriteobj->AddComponent(tmptransform);
								Sprite* tmpsprite = new Sprite();
								justspriteobj->AddComponent(tmpsprite);
								justspriteobj->Init();
								tmpsprite->SetTexture(T(Picture::Item_Bridge));
								tmptransform->SetTranslation({ transform->GetTranslation().x,transform->GetTranslation().y,1 });
								tmptransform->SetScale({ 109,217 });
								OBJECT_CONTROLLER->DeleteController(this);
								GRAPHICS->DeleteSprite(sprite);
								OBJECT_FACTORY->Destroy(object);
							}
                            if (collided_controller->GetControllerType() == ControllerType_BLASTFURNACE)
                            {
                                if (collided_controller->GetCurrentState() == PRESENT)
                                {
									AUDIO_MANAGER->PlaySound("fire");
									//AUDIO_MANAGER->PlaySound("pick");
                                    isUsed = true;
                                    collided_controller->Interact(controllerType);
                                }
                            }
                            if (collided_controller->GetControllerType() == ControllerType_TORCH)
                            {
                                if (collided_controller->GetCurrentState() == PRESENT)
                                {
									AUDIO_MANAGER->PlaySound("fire");
									//AUDIO_MANAGER->PlaySound("pick");
                                    isUsed = true;
                                    TorchController* torchcontroller = new TorchController;
                                    torchcontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y - 30, transform->GetTranslation().z + 10);
                                    OBJECT_CONTROLLER->AddController(torchcontroller);

                                    SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
                                }
                            }
                        }
                        else if (currentstate == FUTURE)
                        {
                            if (collided_controller->GetControllerType() == ControllerType_BLASTFURNACE)
                            {
                                isUsed = true;
                            }
                            else if (collided_controller->GetControllerType() == ControllerType_TORCH)
                            {
                                isUsed = true;
                            }
							else if (collided_controller->GetControllerType() == ControllerType_RIVER)
							{
								AUDIO_MANAGER->PlaySound("putlog");
								OBJECT_CONTROLLER->DeleteController(this);
								GRAPHICS->DeleteSprite(sprite);
								OBJECT_FACTORY->Destroy(object);
							}
                        }
                        else
                        {
							if (collided_controller->GetControllerType() == ControllerType_RIVER)
							{
								AUDIO_MANAGER->PlaySound("putlog");
								OBJECT_CONTROLLER->DeleteController(this);
								GRAPHICS->DeleteSprite(sprite);
								OBJECT_FACTORY->Destroy(object);
							}
                        }
                    }
                }

                break;
         
            case ControllerType_TORCH:
            {			AUDIO_MANAGER->PlaySound("fire");
            isUsed = true;
            TorchController* torchcontroller = new TorchController;
            torchcontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y, transform->GetTranslation().z);
            OBJECT_CONTROLLER->AddController(torchcontroller);

            SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
            break;
            }
		}
            if (isUsed)
            {
                GRAPHICS->DeleteSprite(sprite);
                OBJECT_CONTROLLER->DeleteController(this);
                OBJECT_FACTORY->Destroy(object);
            }
	}

	CurrentState WoodBoardController::GetCurrentState()
	{
		return currentstate;
	}

	void WoodBoardController::HitPoison()
	{
	}

	void WoodBoardController::PastToPresent(bool CalledAtStart)
	{
		canUse = false;
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_WoodBoard));
		transform->SetScale({ 100.f, 46.f });

		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void WoodBoardController::PresentToPast(bool CalledAtStart)
	{
		LogController* logcontroller = new LogController;
		logcontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y, transform->GetTranslation().z);
		GRAPHICS->DeleteSprite(sprite);
		OBJECT_CONTROLLER->AddController(logcontroller);
		OBJECT_CONTROLLER->DeleteController(this);
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void WoodBoardController::PresentToFuture(bool CalledAtStart)
	{
		canUse = false;
		currentstate = FUTURE;
		sprite->SetTexture(T(Picture::Item_WoodBoard_Broken));
		transform->SetScale({ 108.f, 50.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void WoodBoardController::FutureToPresent(bool CalledAtStart)
	{
		canUse = false;
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_WoodBoard));
		transform->SetScale({ 100.f, 46.f });

		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}
}
