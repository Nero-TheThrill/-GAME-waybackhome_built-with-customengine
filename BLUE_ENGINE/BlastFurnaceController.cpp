/*
*  File Name : BlastFurnaceController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief:
*   	Destroy objects
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"BlastFurnaceController.h"
#include"ObjectController.h"
#include<iostream>
#include "Archiver.h"
#include "Audio.h"
#include"SmokeEffects.h"
#include "TorchController.h"
#include "PlayerController.h"

namespace BLUE
{
	BlastFurnaceController::BlastFurnaceController()
	{
		controllertype = ControllerType_BLASTFURNACE;
	}
	Object* BlastFurnaceController::Spawn(float x, float y, float z)
	{
		obj = OBJECT_FACTORY->CreateEmptyObject();
		std::string str("BlastFurnace");
		obj->AddComponent(new Transform());
		transform = obj->transform;
		obj->AddComponent(new Rectangle());
		rectangle = obj->rectangle;
		obj->AddComponent(new Sprite());
		sprite = obj->sprite;
		obj->AddComponent(new Collision());
		collision = obj->collision;
		obj->AddComponent(new Rigidbody());
		rigidbody = obj->rigidbody;
		obj->SetName(str);
		obj->Init();
		(obj->sprite)->SetTexture(T(Picture::Item_BonFire));
		currentstate = PRESENT;
		canMove = false;
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 82.f, 103.f });
		OBJECT_CONTROLLER->AddObject(obj);
		GRAPHICS->AddSprite(sprite);
		return obj;
	}

	Object * BlastFurnaceController::GetObject()
	{
		return obj;
	}

	Transform * BlastFurnaceController::GetTransform()
	{
		return transform;
	}


        void BlastFurnaceController::ChangeToFuture(bool CalledAtStart)
        {
            if (currentstate == PAST)
                PastToPresent(CalledAtStart);
            else if (currentstate == PRESENT)
                PresentToFuture(CalledAtStart);
        }

        void BlastFurnaceController::ChangeToPast(bool CalledAtStart)
        {
            if (currentstate == PRESENT)
                PresentToPast(CalledAtStart);
            else if (currentstate == FUTURE)
                FutureToPresent(CalledAtStart);
        }

	ControllerType BlastFurnaceController::GetControllerType()
	{
		return controllertype;
	}

	void BlastFurnaceController::Reset()
	{

	}

	void BlastFurnaceController::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
			// when it release from inventory ( When the user tries to use item in inventory)
		case ControllerType_NULL:
			break;
		case ControllerType_WOODBOARD:
			if (canUse)
			{
				AUDIO_MANAGER->PlaySound("fire");
				TorchController* torchcontroller = new TorchController;
				torchcontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y - 30, transform->GetTranslation().z + 10);
				OBJECT_CONTROLLER->AddController(torchcontroller);

				SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
			}
			break;
		case ControllerType_TORCH:
			
			if (canUse)
			{
				AUDIO_MANAGER->PlaySound("fire");
				TorchController* torchcontroller = new TorchController;
				torchcontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y - 30, transform->GetTranslation().z + 10);
				OBJECT_CONTROLLER->AddController(torchcontroller);

				SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
			}
			if(currentstate==PAST)
			{
				PastToPresent(false);
			}
			break;
		case ControllerType_PLAYER:
		{
			if (currentstate == PRESENT)
			{
				PLAYER_CONTROLLER->isDead = true;
			}
		}
		break;
		}

	}
	CurrentState BlastFurnaceController::GetCurrentState()
	{
		return currentstate;
	}

    void BlastFurnaceController::HitPoison()
    {
    }

    void BlastFurnaceController::PastToPresent(bool CalledAtStart)
    {
       
        canUse = true;
        currentstate = PRESENT;
        sprite->SetTexture(T(Picture::Item_BonFire));
		transform->SetScale({ 82.f, 103.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			//AUDIO_MANAGER->PlaySound("changeitem");
			AUDIO_MANAGER->PlaySound("fire");
		}
    }

    void BlastFurnaceController::PresentToPast(bool CalledAtStart)
    {
        canUse = false;
        currentstate = PAST;
        sprite->SetTexture(T(Picture::Item_BonFire_Yet));
		transform->SetScale({ 82.f, 55.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
    }

    void BlastFurnaceController::PresentToFuture(bool CalledAtStart)
    {
        canUse = false;
        currentstate = FUTURE;
        sprite->SetTexture(T(Picture::Item_BonFire_Burned));
		transform->SetScale({ 82.f, 43.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
    }

    void BlastFurnaceController::FutureToPresent(bool CalledAtStart)
    {
        canUse = true;
        currentstate = PRESENT;
        sprite->SetTexture(T(Picture::Item_BonFire));
		transform->SetScale({ 82.f, 103.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			//AUDIO_MANAGER->PlaySound("changeitem");
			AUDIO_MANAGER->PlaySound("fire");
		}
    }
}
