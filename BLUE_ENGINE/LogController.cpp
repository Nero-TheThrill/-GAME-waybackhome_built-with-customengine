/*
*  File Name : LogController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief:
*    Past(Log) - Present(Log) - Future(Log)
*    Interact: Cannot cross river -> Can cross river.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"LogController.h"
#include"ObjectController.h"
#include<iostream>
#include "Archiver.h"
#include"SmokeEffects.h"
#include "Audio.h"
#include "WoodBoardController.h"

namespace BLUE
{
    LogController::LogController()
    {
        controllertype = ControllerType_LOG;
    }

    Object* LogController::Spawn(float x, float y, float z)
    {
        obj = OBJECT_FACTORY->CreateEmptyObject();
        std::string str("Log");
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
        (obj->sprite)->SetTexture(T(Picture::Item_Log));
        currentstate = PRESENT;
        canMove = true;
        isUsed = false;
        transform->SetTranslation({ x,y,z });
        transform->SetScale({ 110.f, 90.f});
        OBJECT_CONTROLLER->AddObject(obj);
        GRAPHICS->AddSprite(sprite);
        return obj;
    }

    Object * LogController::GetObject()
    {
        return obj;
    }

    Transform * LogController::GetTransform()
    {
        return transform;
    }

    void LogController::ChangeToFuture(bool CalledAtStart)
    {
        PastToPresent(CalledAtStart);
    }

    void LogController::ChangeToPast(bool /*CalledAtStart*/)
    {
    }


    ControllerType LogController::GetControllerType()
    {
        return controllertype;
    }

    void LogController::Reset()
    {

    }

    void LogController::Interact(ControllerType controller_type)
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

                BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(obj, ControllerType_ANYTHING);

                if (collided_controller != nullptr)
                {
                    //std::cout << "Can use this object!\n";
                    ControllerType cType = collided_controller->GetControllerType();
                    // delete this object after usage if the object is consumable item.
                    isInInventory = false; // if the object isn't consumable item. 
                 
                    if (cType == ControllerType_DOOR)
                    {
                            collided_controller->Interact(controllertype);
                            if (isDoortype)
                            {
								AUDIO_MANAGER->PlaySound("door");
                                OBJECT_CONTROLLER->DeleteController(this);
                                GRAPHICS->DeleteSprite(sprite);
                                OBJECT_FACTORY->Destroy(obj);
                            }
                    }
                    if (cType == ControllerType_BLASTFURNACE)
                    {
						AUDIO_MANAGER->PlaySound("fire");
                        isUsed = true;
                    }
                    if(cType == ControllerType_TORCH)
                    {
						AUDIO_MANAGER->PlaySound("fire");
                        isUsed = true;
                    }
					if (collided_controller->GetControllerType() == ControllerType_RIVER)
					{
						AUDIO_MANAGER->PlaySound("putlog");
						OBJECT_CONTROLLER->DeleteController(this);
						GRAPHICS->DeleteSprite(sprite);
						OBJECT_FACTORY->Destroy(obj);
					}

                }
                else
                {
                    // if there is nothing that collide with
                   //std::cout << "Nothing has collided with the this object!\n";
                    // put this on the ground
                    isInInventory = false;
                }

            }
        }
        break;
        case ControllerType_TORCH:
			AUDIO_MANAGER->PlaySound("fire");
            GRAPHICS->DeleteSprite(sprite);
            OBJECT_CONTROLLER->DeleteController(this);
            OBJECT_FACTORY->Destroy(obj);
            break;
        default:
            break;
        }
        if (isUsed)
        {
            GRAPHICS->DeleteSprite(sprite);
            OBJECT_CONTROLLER->DeleteController(this);
            OBJECT_FACTORY->Destroy(obj);
        }
    }
    CurrentState LogController::GetCurrentState()
    {
        return currentstate;
    }

    void LogController::HitPoison()
    {

    }

    void LogController::PastToPresent(bool CalledAtStart)
    {
		if (!CalledAtStart)
		{
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
			AUDIO_MANAGER->PlaySound("changeitem");
		}

        WoodBoardController* woodbaordcontroller = new WoodBoardController;
        woodbaordcontroller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y, transform->GetTranslation().z);
        GRAPHICS->DeleteSprite(sprite);
        OBJECT_CONTROLLER->AddController(woodbaordcontroller);
        OBJECT_CONTROLLER->DeleteController(this);

    }
}
