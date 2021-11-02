/*
*  File Name : DoorController.cpp
*  Primary Author : Jinwon Park
*  Secondary Author :
*  Brief:
*    Past(Broken Door) - Present(Door) - Future(Broken Door)
*    Interact: open door
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "DoorController.h"
#include "ObjectController.h"
#include <iostream>
#include "Archiver.h"
#include "Audio.h"
#include "SmokeEffects.h"

namespace BLUE
{
    extern DoorController* DOOR_CONTROLLER = nullptr;
    DoorController::DoorController()
    {
        controllertype = ControllerType_DOOR;
        DOOR_CONTROLLER = this;
    }

    Object* DoorController::Spawn(float x, float y, float z)
    {
        obj = OBJECT_FACTORY->CreateEmptyObject();
        std::string str("Door");
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
        isInInventory = false;
        SetItemType(item_type);
        currentstate = PRESENT;
        canMove = false;
        transform->SetTranslation({ x,y,z });
        transform->SetScale({ 90,   110 });
        OBJECT_CONTROLLER->AddObject(obj);
        GRAPHICS->AddSprite(sprite);

        return obj;
    }

    Object * DoorController::GetObject()
    {
        return obj;
    }

    Transform * DoorController::GetTransform()
    {
        return transform;
    }

    void DoorController::ChangeToFuture(bool /*CalledAtStart*/)
    {
    }

    void DoorController::ChangeToPast(bool /*CalledAtStart*/)
    {
    }


    ControllerType DoorController::GetControllerType()
    {
        return controllertype;
    }

    void DoorController::Reset()
    {

    }

    void DoorController::Interact(ControllerType controller_type)
    {
        if (currentstate == PRESENT)
        {
            switch (controller_type)
            {
            case ControllerType_SEED:
            {
                if (isDead == false)
                {
                    if (item_type == controller_type)
                    {
                        BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(obj, ControllerType_SEED);
                        if (collided_controller->GetCurrentState() == PRESENT)
                        {
                            collided_controller->isDoortype = true;
                            rigidbody->SetBodyType(RigidbodyType::None);
                            isDead = true;
                            sprite->SetTexture(T(Picture::Item_Door_Opened));
                            SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
                        }
                    }
                }
            }
            break;
            case ControllerType_RUSTKEY:
            {
                if (isDead == false)
                {
                    if (item_type == controller_type)
                    {
                        BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(obj, ControllerType_RUSTKEY);
                        if (collided_controller->GetCurrentState() == PRESENT)
                        {
                            collided_controller->isDoortype = true;
                            rigidbody->SetBodyType(RigidbodyType::None);
                            isDead = true;
                            sprite->SetTexture(T(Picture::Item_Door_Opened));
                            SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
                        }
                    }
                }
            }
            break;
            case ControllerType_AXE:
            {
                if (isDead == false)
                {
                    if (item_type == controller_type)
                    {
                        BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(obj, ControllerType_AXE);
                        if (collided_controller->GetCurrentState() == PRESENT)
                        {
                            collided_controller->isDoortype = true;
                            rigidbody->SetBodyType(RigidbodyType::None);
                            isDead = true;
                            sprite->SetTexture(T(Picture::Item_Door_Opened));
                            SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
                        }
                    }
                }
            }
            break;
            case ControllerType_LOG:
            {
                if (isDead == false)
                {
                    BaseController *collided_controller = OBJECT_CONTROLLER->GetCollideWith(obj, ControllerType_LOG);
                    if (collided_controller->GetCurrentState() == PRESENT)
                    {
                        if (item_type == controller_type)
                        {
                            collided_controller->isDoortype = true;
                            rigidbody->SetBodyType(RigidbodyType::None);
                            isDead = true;
                            sprite->SetTexture(T(Picture::Item_Door_Opened));
                            SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale());
                        }
                    }
                }
            }
            break;
            case BLUE::ControllerType_POISONPLANT: //past
            {
            }
            break;
            default:
                break;
            }
        }
    }
    CurrentState DoorController::GetCurrentState()
    {
        return currentstate;
    }

    void DoorController::SetItemType(const ControllerType ctype)
    {
        item_type = ctype;
        obj->item_type = ctype;
        switch (item_type)
        {
        case BLUE::ControllerType_SEED:
            sprite->SetTexture(T(Picture::Item_Door_Seed));
            break;
        case BLUE::ControllerType_RUSTKEY:
            sprite->SetTexture(T(Picture::Item_Door_Key));
            break;
        case BLUE::ControllerType_AXE:
            sprite->SetTexture(T(Picture::Item_Door_Axe));
            break;
        case BLUE::ControllerType_LOG:
            sprite->SetTexture(T(Picture::Item_Door_Log));
            break;
        case BLUE::ControllerType_POISONPLANT: //past
            break;
        default:
            break;
        }
    }
    ControllerType DoorController::GetItemType() const
    {
        return item_type;
    }

    void DoorController::HitPoison()
    {
    }

}
