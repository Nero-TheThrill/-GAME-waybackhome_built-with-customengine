/*
*  File Name : VineController.cpp
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief:
*  Past(Vine) - Present(Vine) - Future(Vine)
        Interact: Torch + Vine = nothing
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "RustKeyController.h"
#include "ObjectController.h"
#include <iostream>
#include "Archiver.h"
#include "TestLevel1.h"
#include "SmokeEffects.h"
#include "Audio.h"
#include "BoxController.h"
#include "VineController.h"
namespace BLUE
{
    VineController::VineController() :
        object(nullptr),
        transform(nullptr),
        rigidbody(nullptr),
        rectangle(nullptr),
        collision(nullptr),
        sprite(nullptr),
        controllerType(ControllerType_VINE),
        canUse(false),
        currentstate(PRESENT)
    {
    }

    Object* VineController::Spawn(float x, float y, float z)
    {
        object = OBJECT_FACTORY->CreateEmptyObject();
        object->SetName("Vine");
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
        sprite->SetTexture(T(Picture::Item_Vine_2));
        transform->SetTranslation({ x, y, z });
        transform->SetScale({ 135.f, 73.f });
        OBJECT_CONTROLLER->AddObject(object);
        GRAPHICS->AddSprite(sprite);

        return object;
    }

    Object* VineController::GetObject()
    {
        return object;
    }

    Transform* VineController::GetTransform()
    {
        return transform;
    }

    void VineController::ChangeToFuture(bool CalledAtStart)
    {
        if (currentstate == PAST)
            PastToPresent(CalledAtStart);
        else if (currentstate == PRESENT)
            PresentToFuture(CalledAtStart);
    }

    void VineController::ChangeToPast(bool CalledAtStart)
    {
        if (currentstate == PRESENT)
            PresentToPast(CalledAtStart);
        else if (currentstate == FUTURE)
            FutureToPresent(CalledAtStart);
    }

    ControllerType VineController::GetControllerType()
    {
        return controllerType;
    }

    void VineController::Reset()
    {
    }

    void VineController::Interact(ControllerType controller_type)
    {


        switch (controller_type)
        {
            // when it release from inventory ( When the user tries to use item in inventory)
        case ControllerType_TORCH:
			AUDIO_MANAGER->PlaySound("fire");
            GRAPHICS->DeleteSprite(sprite);
            OBJECT_CONTROLLER->DeleteController(this);
            OBJECT_FACTORY->Destroy(object);
            break;
       }      
    }
    CurrentState VineController::GetCurrentState()
    {
        return currentstate;
    }

    void VineController::HitPoison()
    {
        //GRAPHICS->DeleteSprite(sprite);
        //OBJECT_CONTROLLER->DeleteController(this);
        //OBJECT_FACTORY->Destroy(object);
    }

	void VineController::PastToPresent(bool CalledAtStart)
	{
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Vine_2));
		transform->SetScale({ 101.f, 57.f });

		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}

	void VineController::PresentToPast(bool CalledAtStart)
	{
		currentstate = PAST;
		sprite->SetTexture(T(Picture::Item_Vine_1));
		transform->SetScale({ 90.f, 73.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}

	void VineController::PresentToFuture(bool CalledAtStart)
	{
		currentstate = FUTURE;
		sprite->SetTexture(T(Picture::Item_Vine_3));
		transform->SetScale({ 135.f, 73.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}


	}

	void VineController::FutureToPresent(bool CalledAtStart)
	{
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Vine_2));
		transform->SetScale({ 101.f, 57.f });

		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}
}
 