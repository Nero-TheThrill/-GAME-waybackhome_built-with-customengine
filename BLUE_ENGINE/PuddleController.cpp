/*
*  File Name : PuddleController.h
*  Primary Author : Park Jinwon
*  Brief:
*  Past(Pond) - Present(Puddle) - Future(Ground)
	Interact:
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/


#include "PuddleController.h"
#include "ObjectController.h"
#include <iostream>
#include "Archiver.h"
#include "TestLevel1.h"
#include "SmokeEffects.h"
#include "Audio.h"
#include "WoodBoardController.h"

namespace BLUE
{
	PuddleController::PuddleController() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_PUDDLE),
		canUse(false),
		currentstate(PRESENT)
	{
	}

	Object* PuddleController::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Puddle");
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
		canMove = false;
		isUsed = false;
		sprite->SetTexture(T(Picture::Item_Puddle));
		transform->SetTranslation({ x, y, z });
		transform->SetScale({ 97.f, 33.f });
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);

		return object;
	}

	Object* PuddleController::GetObject()
	{
		return object;
	}

	Transform* PuddleController::GetTransform()
	{
		return transform;
	}

	void PuddleController::ChangeToFuture(bool CalledAtStart)
	{
		if (currentstate == PAST)
			PastToPresent(CalledAtStart);
		else if (currentstate == PRESENT)
			PresentToFuture(CalledAtStart);
	}

	void PuddleController::ChangeToPast(bool CalledAtStart)
	{
		if (currentstate == PRESENT)
			PresentToPast(CalledAtStart);
		else if (currentstate == FUTURE)
			FutureToPresent(CalledAtStart);
	}

	ControllerType PuddleController::GetControllerType()
	{
		return controllerType;
	}

	void PuddleController::Reset()
	{
	}

	void PuddleController::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
			// when it release from inventory ( When the user tries to use item in inventory)
		case ControllerType_NULL:
		default:
			break;
		}
	}
	CurrentState PuddleController::GetCurrentState()
	{
		return currentstate;
	}

	void PuddleController::HitPoison()
	{
	}

	void PuddleController::PastToPresent(bool CalledAtStart)
	{
		canUse = false;
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Puddle));
		transform->SetScale({ 97.f, 33.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void PuddleController::PresentToPast(bool CalledAtStart)
	{
		canUse = false;
		currentstate = PAST;
		sprite->SetTexture(T(Picture::Item_Mud));
		transform->SetScale({ 85.f, 33.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void PuddleController::PresentToFuture(bool CalledAtStart)
	{
		canUse = false;
		currentstate = FUTURE;
		sprite->SetTexture(T(Picture::Item_Pond));
		transform->SetScale({ 300.f, 115.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}

	void PuddleController::FutureToPresent(bool CalledAtStart)
	{
		canUse = false;
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Puddle));
		transform->SetScale({ 97.f, 33.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}
}
