/*
*  File Name : PoisonplantController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Past(Poison Sprout) - Present(Poison Plant) - Future(Dead Poison Plant)
		Interact : 

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "PoisonplantController.h"
#include "ObjectController.h"
#include <iostream>
#include "Archiver.h"
#include "TestLevel1.h"
#include "SmokeEffects.h"
#include "Audio.h"
#include "PoisonBulletController.h"
#include "PoisonPlantManager.h"

namespace BLUE
{
	PoisonplantController::PoisonplantController() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_POISONPLANT),
		canUse(false),
		currentstate(PRESENT)
	{
	}

	Object* PoisonplantController::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("PoisonPlant");
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
		isUsed = false;
		sprite->SetTexture(T(Picture::Item_Poison_Plant));
		transform->SetTranslation({ x, y, z });
		transform->SetScale({ 78.f, 95.f });


		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);
		POISONPLANT_MANAGER->AddPoisionPlant(this, glm::vec2(transform->GetTranslation().x + 10, transform->GetTranslation().y + 10));
		return object;
	}

	Object* PoisonplantController::Spawn(float x, float y, float z, glm::vec2 direction)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("PoisonPlant");
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
		isUsed = false;
		sprite->SetTexture(T(Picture::Item_Poison_Plant));
		transform->SetTranslation({ x, y, z });
		transform->SetScale({ 78.f, 95.f });
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);
		object->direction = direction;
		POISONPLANT_MANAGER->AddPoisionPlant(this, direction);
		return object;
	}


	Object* PoisonplantController::GetObject()
	{
		return object;
	}

	Transform* PoisonplantController::GetTransform()
	{
		return transform;
	}

	void PoisonplantController::ChangeToFuture(bool CalledAtStart)
	{
		if (currentstate == PAST)
			PastToPresent(CalledAtStart);
		else if (currentstate == PRESENT)
			PresentToFuture(CalledAtStart);
	}

	void PoisonplantController::ChangeToPast(bool CalledAtStart)
	{
		if (currentstate == PRESENT)
			PresentToPast(CalledAtStart);
		else if (currentstate == FUTURE)
			FutureToPresent(CalledAtStart);
	}

	ControllerType PoisonplantController::GetControllerType()
	{
		return controllerType;
	}

	void PoisonplantController::Reset()
	{
	}

	void PoisonplantController::Interact(ControllerType controller_type)
	{
            switch (controller_type)
            {
            case ControllerType_PLAYER:
            {

            }
            case ControllerType_NULL:
            {
                if (isInInventory)
                {

                    BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(object, ControllerType_ANYTHING);

                    if (collided_controller != nullptr)
                    {
                        if (collided_controller->GetControllerType() == ControllerType_TORCH)
                        {
							AUDIO_MANAGER->PlaySound("fire");
                            OBJECT_CONTROLLER->DeleteController(this);
                            GRAPHICS->DeleteSprite(sprite);
                            OBJECT_FACTORY->Destroy(object);
                        }
                        else if (collided_controller->GetControllerType() == ControllerType_BLASTFURNACE)
                        {
							AUDIO_MANAGER->PlaySound("fire");
                            OBJECT_CONTROLLER->DeleteController(this);
                            GRAPHICS->DeleteSprite(sprite);
                            OBJECT_FACTORY->Destroy(object);
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
                       // std::cout << "Nothing has collided with the this object!\n";
                        //isInInventory = false;
                    }


                }
            }
            break;
            case ControllerType_TORCH:
            {			AUDIO_MANAGER->PlaySound("fire");
                OBJECT_CONTROLLER->DeleteController(this);
                GRAPHICS->DeleteSprite(sprite);
                OBJECT_FACTORY->Destroy(object);
                break;
            }
            default:
                break;
            }
	}

	CurrentState PoisonplantController::GetCurrentState()
	{
		return currentstate;
	}

	void PoisonplantController::ShootPoision(glm::vec2 position)
	{
		POISONBULLET_CONTROLLER->Init(*object, position);
	}

    void PoisonplantController::HitPoison()
    {
    }

	void PoisonplantController::PastToPresent(bool CalledAtStart)
	{
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		currentstate = PRESENT;
		transform->SetScale({ 78.f, 95.f });
		sprite->SetTexture(T(Picture::Item_Poison_Plant));
		canMove = false;
	}

	void PoisonplantController::PresentToPast(bool CalledAtStart)
	{
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		currentstate = PAST;

		transform->SetScale({ 62.f,44.f });
		sprite->SetTexture(T(Picture::Item_Poison_Sprout));

		canMove = true;
	}

	void PoisonplantController::PresentToFuture(bool CalledAtStart)
	{
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		currentstate = FUTURE;
		transform->SetScale({ 76.f, 69.f });
		sprite->SetTexture(T(Picture::Item_Poison_Dead));
		canMove = true;
	}

	void PoisonplantController::FutureToPresent(bool CalledAtStart)
	{
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		currentstate = PRESENT;
		transform->SetScale({ 78.f, 95.f });
		sprite->SetTexture(T(Picture::Item_Poison_Plant));
		canMove = false;
	}
}
