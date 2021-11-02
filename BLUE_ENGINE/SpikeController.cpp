/*
*  File Name : SpikeController.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:
	Past(Spike) - Present(Spike) - Future(Spike)
	Interact: Player + spike = death

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "SpikeController.h"
#include "ObjectController.h"
#include <iostream>
#include "ObjectFactory.h"
#include "PlayerController.h"
#include "Audio.h"
#include "SmokeEffects.h"

namespace BLUE
{
	SpikeController::SpikeController() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_SPIKE)
	{
	}

	Object* SpikeController::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Spike");
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
		sprite->SetTexture(T(Picture::Item_Spike_2));
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 70.f, 38.f });
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);
		currentstate = PRESENT;
		return object;
	}

	Object* SpikeController::GetObject()
	{
		return object;
	}

	Transform* SpikeController::GetTransform()
	{
		return transform;
	}

	void SpikeController::ChangeToFuture(bool CalledAtStart)
	{
		if (currentstate == PRESENT)
			PresentToFuture(CalledAtStart);
		else if (currentstate == PAST)
			PastToPresent(CalledAtStart);

	}

	void SpikeController::ChangeToPast(bool CalledAtStart)
	{
		if (currentstate == FUTURE)
			FutureToPresent(CalledAtStart);
		else if (currentstate == PRESENT)
			PresentToPast(CalledAtStart);
	}

	ControllerType SpikeController::GetControllerType()
	{
		return controllerType;
	}

	void SpikeController::Reset()
	{
	}

	void SpikeController::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
		case ControllerType_PLAYER:
		{
			PLAYER_CONTROLLER->isDead = true;
		}
		break;
		default:
			break;
		}
	}
	CurrentState SpikeController::GetCurrentState()
	{
		return currentstate;
	}

    void SpikeController::HitPoison()
    {
		AUDIO_MANAGER->PlaySound("destroy_spike");
        OBJECT_CONTROLLER->DeleteController(this);
        GRAPHICS->DeleteSprite(sprite);
        OBJECT_FACTORY->Destroy(object);
    }

	void SpikeController::PastToPresent(bool CalledAtStart)
	{
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Spike_2));
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void SpikeController::PresentToPast(bool CalledAtStart)
	{
		currentstate = PAST;
		sprite->SetTexture(T(Picture::Item_Spike_1));
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}

	void SpikeController::PresentToFuture(bool CalledAtStart)
	{
		currentstate = FUTURE;
		sprite->SetTexture(T(Picture::Item_Spike_3));
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void SpikeController::FutureToPresent(bool CalledAtStart)
	{
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Spike_2));
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}
}
