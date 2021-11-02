/*
*  File Name : SeedController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jina Hyun
*  Brief:
*    Past(Seed) - Present(Seed) - Future(Tree)
*    Interact: No Interact
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"SeedController.h"
#include"ObjectController.h"
#include<iostream>
#include "Archiver.h"
#include "SmokeEffects.h"
#include "Audio.h"

namespace BLUE
{
    SeedController::SeedController()
    {
        controllertype = ControllerType_SEED;
    }

    Object* SeedController::Spawn(float x, float y, float z)
    {
        obj = OBJECT_FACTORY->CreateEmptyObject();
        std::string str("Seed");
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
        sprite->SetTexture(T(Picture::Item_Sprout));
        currentstate = PRESENT;
        canMove = true;
        isUsed = false;
        canUse = true;
        transform->SetTranslation({ x,y,z });
        transform->SetScale({ 70.f, 50.f });
        OBJECT_CONTROLLER->AddObject(obj);
        GRAPHICS->AddSprite(sprite);
        return obj;
    }

    Object * SeedController::GetObject()
    {
        return obj;
    }

    Transform * SeedController::GetTransform()
    {
        return transform;
    }

    void SeedController::ChangeToFuture(bool CalledAtStart)
    {

        if (currentstate == PRESENT)
            PresentToFuture(CalledAtStart);
        if (currentstate == PAST)
            PastToPresent(CalledAtStart);
    }

    void SeedController::ChangeToPast(bool CalledAtStart)
    {
        if (currentstate == PRESENT)
            PresentToPast(CalledAtStart);
    }


    ControllerType SeedController::GetControllerType()
    {
        return controllertype;
    }

    void SeedController::Reset()
    {

    }

    void SeedController::Interact(ControllerType controller_type)
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

                BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(obj, ControllerType_ANYTHING);

                if (collided_controller != nullptr)
                {
                    //std::cout << "Can use this object!\n";
                    if (collided_controller->GetControllerType() == ControllerType_DOOR)
                    {
                        collided_controller->Interact(controllertype);
                        if (isDoortype)
                        {
							AUDIO_MANAGER->PlaySound("door");
                            canMove = false;
                            OBJECT_CONTROLLER->DeleteController(this);
                            GRAPHICS->DeleteSprite(sprite);
                            OBJECT_FACTORY->Destroy(obj);
                        }
                    }
                    else if (collided_controller->GetControllerType() == ControllerType_TORCH)
                    {
						AUDIO_MANAGER->PlaySound("fire");
                        OBJECT_CONTROLLER->DeleteController(this);
                        GRAPHICS->DeleteSprite(sprite);
                        OBJECT_FACTORY->Destroy(obj);
                    }
                    else if (collided_controller->GetControllerType() == ControllerType_BLASTFURNACE)
                    {
						AUDIO_MANAGER->PlaySound("fire");
                        OBJECT_CONTROLLER->DeleteController(this);
                        GRAPHICS->DeleteSprite(sprite);
                        OBJECT_FACTORY->Destroy(obj);
                    }
                    else if (collided_controller->GetControllerType() == ControllerType_RIVER)
                    {
						AUDIO_MANAGER->PlaySound("putlog");
                        OBJECT_CONTROLLER->DeleteController(this);
                        GRAPHICS->DeleteSprite(sprite);
                        OBJECT_FACTORY->Destroy(obj);
                    }

                    else
                        collided_controller->Interact(controllertype);
                }
                else
                {
                    //std::cout << "Nothing has collided with the this object!\n";
                    //isInInventory = false;
                }


            }
            break;
        }
        case ControllerType_TORCH:
            {			AUDIO_MANAGER->PlaySound("fire");
            OBJECT_CONTROLLER->DeleteController(this);
            GRAPHICS->DeleteSprite(sprite);
            OBJECT_FACTORY->Destroy(obj);
            break;
            }
        default:
            break;
        }
    }

    CurrentState SeedController::GetCurrentState()
    {
        return currentstate;
    }

    void SeedController::HitPoison()
    {
        //GRAPHICS->DeleteSprite(sprite);
        //OBJECT_CONTROLLER->DeleteController(this);
        //OBJECT_FACTORY->Destroy(obj);
    }

	void SeedController::PresentToPast(bool CalledAtStart)
	{
		canUse = true;
		currentstate = PAST;
		sprite->SetTexture(T(Picture::Item_Seed));
		transform->SetScale({ 20.f, 31.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}
	void SeedController::PastToPresent(bool CalledAtStart)
	{
		canUse = true;
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Sprout));
		transform->SetScale({ 70.f, 50.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}

	}
	void SeedController::PresentToFuture(bool CalledAtStart)
	{
		//std::cout << "Seed will grow up!\n";
		TreeController* treecontroller = new TreeController;
		treecontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y + 100, transform->GetTranslation().z);
		GRAPHICS->DeleteSprite(sprite);
		OBJECT_CONTROLLER->AddController(treecontroller);
		OBJECT_CONTROLLER->DeleteController(this);
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(glm::vec3(transform->GetTranslation().x, transform->GetTranslation().y + 100, transform->GetTranslation().z), transform->GetScale()*3.0f);
			AUDIO_MANAGER->PlaySound("changeitem");
		}
	}
}
