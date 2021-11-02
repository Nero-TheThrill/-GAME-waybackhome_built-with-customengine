/*
*  File Name : AxeController.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:
*       Past(Axe) - Present(Axe) - Future(Axe)
*		Interact: Axe -> Tree: make tree to log
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "AxeController.h"
#include "ObjectController.h"
#include <iostream>
#include "ObjectFactory.h"
#include "Graphics.h"
#include "Audio.h"
#include "SmokeEffects.h"
#include "LogController.h"
#include "RustKeyController.h"
#include "WoodBoardController.h"
#include "TorchController.h"

namespace BLUE
{
    AxeController::AxeController() :
        object(nullptr),
        transform(nullptr),
        rigidbody(nullptr),
        rectangle(nullptr),
        collision(nullptr),
        sprite(nullptr),
        controllerType(ControllerType_AXE)
    {
    }

    Object* AxeController::Spawn(float x, float y, float z)
    {
        object = OBJECT_FACTORY->CreateEmptyObject();
        object->SetName("Axe");
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
        canMove = true;
        sprite->SetTexture(T(Picture::Item_Axe));
        transform->SetTranslation({ x,y,z });
        transform->SetScale({ 46.f, 78.f });
        OBJECT_CONTROLLER->AddObject(object);
        GRAPHICS->AddSprite(sprite);
        currentstate = PRESENT;
        return object;
    }

    Object* AxeController::GetObject()
    {
        return object;
    }

    Transform* AxeController::GetTransform()
    {
        return transform;
    }

    void AxeController::ChangeToFuture(bool /*CalledAtStart*/)
    {
       // std::cout << "Nothing has changed with Axe (FUTURE)\n";
    }

    void AxeController::ChangeToPast(bool CalledAtStart)
    {
        PresentToPast(CalledAtStart);
    }

    ControllerType AxeController::GetControllerType()
    {
        return controllerType;
    }

    void AxeController::Reset()
    {
    }

    void AxeController::Interact(ControllerType controller_type)
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
                    if (collided_controller->GetControllerType() == ControllerType_TREE)
                    {
                        if (!IsUsed)
                        {
                            IsUsed = true;
                          
                            collided_controller->Interact(controllerType);
                         
                            isInInventory = false; // if the object isn't consumable item.
                            OBJECT_CONTROLLER->DeleteController(this);
                            GRAPHICS->DeleteSprite(sprite);
                            OBJECT_FACTORY->Destroy(object);
                        }
                    }
                    else if (collided_controller->GetControllerType() == ControllerType_DOOR)
                    {

                        if (!IsUsed)
                        {
                            collided_controller->Interact(controllerType);
                            if (isDoortype)
                            {
								AUDIO_MANAGER->PlaySound("door");
                                OBJECT_CONTROLLER->DeleteController(this);
                                GRAPHICS->DeleteSprite(sprite);
                                OBJECT_FACTORY->Destroy(object);

                                IsUsed = true;
                            }
                        }
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
                    // if there is nothing that collide with
                    //std::cout << "Nothing has collided with the this object!\n";
                    // put this on the ground
                    isInInventory = false;
                }
            }
        }
        break;
        default:
            break;
        }
    }
    CurrentState AxeController::GetCurrentState()
    {
        return currentstate;
    }

    void AxeController::HitPoison()
    {
    }

    void AxeController::PresentToPast(bool CalledAtStart)
    {
		if (!CalledAtStart)
		{
			AUDIO_MANAGER->PlaySound("changeitem");
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*3.0f);
		}
            TorchController* torchcontroller = new TorchController;
            RustKeyController* rustkeycontroller = new RustKeyController;
			torchcontroller->Spawn(transform->GetTranslation().x+40, transform->GetTranslation().y, transform->GetTranslation().z);
			torchcontroller->ChangeToPast(true);
            rustkeycontroller->Spawn(transform->GetTranslation().x-40, transform->GetTranslation().y, transform->GetTranslation().z);
            rustkeycontroller->ChangeToPast(false);
            GRAPHICS->DeleteSprite(sprite);
            OBJECT_CONTROLLER->AddController(torchcontroller);
            OBJECT_CONTROLLER->AddController(rustkeycontroller);
            OBJECT_CONTROLLER->DeleteController(this);
    }

    void AxeController::PresentToFuture(bool /*CalledAtStart*/)
    {
    }

    void AxeController::FutureToPresent(bool /*CalledAtStart*/)
    {
    }
}
