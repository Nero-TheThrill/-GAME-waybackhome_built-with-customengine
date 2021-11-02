/*
*  File Name : RustKeyController.h
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief:
*  Past(Usable Key) - Present(Rust Key) - Future(Metallic Powder)
        Interact: Usable Key -> Box: open the box
*
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
#include "AxeController.h"

namespace BLUE
{
    RustKeyController::RustKeyController() :
        object(nullptr),
        transform(nullptr),
        rigidbody(nullptr),
        rectangle(nullptr),
        collision(nullptr),
        sprite(nullptr),
        controllerType(ControllerType_RUSTKEY),
        canUse(false),
        currentstate(PRESENT)
    {
    }

    Object* RustKeyController::Spawn(float x, float y, float z)
    {
        object = OBJECT_FACTORY->CreateEmptyObject();
        object->SetName("Key");
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
        sprite->SetTexture(T(Picture::Item_Key));
        transform->SetTranslation({ x, y, z });
        transform->SetScale({ 45.f, 55.f });
        OBJECT_CONTROLLER->AddObject(object);
        GRAPHICS->AddSprite(sprite);

        return object;
    }

    Object* RustKeyController::GetObject()
    {
        return object;
    }

    Transform* RustKeyController::GetTransform()
    {
        return transform;
    }

    void RustKeyController::ChangeToFuture(bool CalledAtStart)
    {
        if (currentstate == PAST)
            PastToPresent(CalledAtStart);
        else if (currentstate == PRESENT)
            PresentToFuture(CalledAtStart);
    }

    void RustKeyController::ChangeToPast(bool CalledAtStart)
    {
        if (currentstate == PRESENT)
            PresentToPast(CalledAtStart);
        else if (currentstate == FUTURE)
            FutureToPresent(CalledAtStart);
    }

    ControllerType RustKeyController::GetControllerType()
    {
        return controllerType;
    }

    void RustKeyController::Reset()
    {
    }

    void RustKeyController::Interact(ControllerType controller_type)
    {


        switch (controller_type)
        {
            // when it release from inventory ( When the user tries to use item in inventory)
        case ControllerType_NULL:
        {
            if (isInInventory)
            {
                /* make CanInteractWith()
                *  :When you release this object, check if there is a collidable object and get its BaseController.
                */
                BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(object, ControllerType_ANYTHING);

                if (collided_controller != nullptr)
                {
                    //if there is something collide with
                    if (currentstate==PRESENT)
                    {
                       // std::cout << "Can use this object!\n";
                        if (collided_controller->GetControllerType() == ControllerType_BOX)
                        {
                            if (!dynamic_cast<BoxController*>(collided_controller)->GetIsOpen())
                            {
                                isUsed = true;
                                canUse = false;
                                collided_controller->Interact(controllerType);
                            }
                        }

                        if (collided_controller->GetControllerType() == ControllerType_DOOR)
                        {
                            if (!isUsed)
                            {
                                collided_controller->Interact(controllerType);
                                if (isDoortype)
                                {
									AUDIO_MANAGER->PlaySound("door");
                                    canMove = false;
                                    OBJECT_CONTROLLER->DeleteController(this);
                                    GRAPHICS->DeleteSprite(sprite);
                                    OBJECT_FACTORY->Destroy(object);

                                    isUsed = true;
                                    canUse = false;
                                }
                            }
                        }
						if (collided_controller->GetControllerType() == ControllerType_RIVER)
						{
							AUDIO_MANAGER->PlaySound("putlog");
							OBJECT_CONTROLLER->DeleteController(this);
							GRAPHICS->DeleteSprite(sprite);
							OBJECT_FACTORY->Destroy(object);
						}

                    }
                    else if(currentstate==PAST)
                    {
                        if (collided_controller->GetControllerType() == ControllerType_TORCH&& collided_controller->GetCurrentState()==PAST)
                        {
                            isUsed = true;
                            collided_controller->Interact(controllerType);
                        }
                    }
                    else
                    {
                        //std::cout << "Can not use this object!\n";
                        // still in inventory 
                    }
                }
                else
                {
                    // if there is nothing that collide with
                   // std::cout << "Nothing has collided with the this object!\n";
                    // put this on the ground
                }
            }
            break;
        case ControllerType_TORCH:
            if (currentstate == PAST)
            {
				AUDIO_MANAGER->PlaySound("changeitem");
                AxeController* axecontroller = new AxeController;
                axecontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y, transform->GetTranslation().z);
                GRAPHICS->DeleteSprite(sprite);
                OBJECT_CONTROLLER->AddController(axecontroller);
                OBJECT_CONTROLLER->DeleteController(this);

                SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
            }
            break;

        }
        }
        if (isUsed)
        {
            //std::cout << "The Key item disappeared after usage!\n";
            GRAPHICS->DeleteSprite(sprite);
            OBJECT_CONTROLLER->DeleteController(this);
            OBJECT_FACTORY->Destroy(object);
        }

    }
    CurrentState RustKeyController::GetCurrentState()
    {
        return currentstate;
    }

    void RustKeyController::HitPoison()
    {
    }

	void RustKeyController::PastToPresent(bool CalledAtStart)
	{
		//std::cout << "The rust key has changed to rust key!\n";
		canUse = true;
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Key));
		transform->SetScale({ 45.f, 55.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		// useable key to rust key


	}

	void RustKeyController::PresentToPast(bool CalledAtStart)
	{
		//std::cout << "The rust key has changed to useable key!\n";
		canUse = false;
		currentstate = PAST;
		sprite->SetTexture(T(Picture::Item_Metal));
		transform->SetScale({ 43.f, 30.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		// rust key to key

	}

	void RustKeyController::PresentToFuture(bool CalledAtStart)
	{
		//std::cout << "The rust key has changed to metallic powder!\n";
		canUse = false;
		currentstate = FUTURE;
		sprite->SetTexture(T(Picture::Item_RustKey));
		transform->SetScale({ 30.f, 50.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		// rust key to powder

	}

	void RustKeyController::FutureToPresent(bool CalledAtStart)
	{
		//std::cout << "The metallic powder key has changed to rust key!\n";
		canUse = true;
		currentstate = PRESENT;
		sprite->SetTexture(T(Picture::Item_Key));
		transform->SetScale({ 45.f, 55.f });
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
			AUDIO_MANAGER->PlaySound("changeitem");
		}
		// metallic powder to rust key


	}
}
