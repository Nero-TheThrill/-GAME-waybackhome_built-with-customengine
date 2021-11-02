/*
*  File Name : MouseController.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Choi Jinwoo, Hyun Jina
*  Brief: It does pick up and down from inventory
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include <iostream>
#include "MouseController.h"
#include "Graphics.h"
#include "Audio.h"
#include "ObjectFactory.h"
#include "TexturePath.h"
#include "PlayerController.h"
#include "ObjectController.h"


namespace BLUE {
    MouseController::MouseController()
    {
        obj = OBJECT_FACTORY->CreateEmptyObject();

        obj->AddComponent(new Transform());
        transform = obj->transform;
    }


    MouseController::~MouseController()
    {
    }

    void MouseController::update(Sprite* sprite, bool& IsGunFuture, bool& IsFuture)
    {
        mouseX = static_cast<int>(WINDOW_INFORMATION::GetMousePos().x);
        mouseY = static_cast<int>(-WINDOW_INFORMATION::GetMousePos().y);
        if (Input::GetMouseWheelState() > 0 && !IsFuture)
        {
            IsFuture = true;
            AUDIO_MANAGER->PlaySound("changebullet");
            IsGunFuture = true;
            sprite->SetTexture(T(Picture::Hud_BulletState_Future));
        }
        if (Input::GetMouseWheelState() < 0 && IsFuture)
        {
            IsFuture = false;
            AUDIO_MANAGER->PlaySound("changebullet");
            IsGunFuture = false;
            sprite->SetTexture(T(Picture::Hud_BulletState_Past));
        }
    }

    void MouseController::picking()
    {
		if (mouseX >= Inventory::location.x - Inventory::scale.x / 2 && mouseX <= Inventory::location.x + Inventory::scale.x / 2 && mouseY >= -Inventory::location.y - Inventory::scale.y / 2 && mouseY <= -Inventory::location.y + Inventory::scale.y / 2)
		{
			CanPicking = true;
			OBJECT_CONTROLLER->Help();
		}
        if (CanPicking)
        {
            for (unsigned int i = 0; i < OBJECT_CONTROLLER->controllers.size(); ++i)
            {
                if (OBJECT_CONTROLLER->controllers.at(i)->isInInventory)
                {
                    mouseX += static_cast<int>(GRAPHICS->GetCamera()->GetPosition().x);
                    mouseY -= static_cast<int>(GRAPHICS->GetCamera()->GetPosition().y);
                    (OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation({ mouseX, -mouseY, 999 });
                    (OBJECT_CONTROLLER->objects.at(i)->sprite)->isHud = false;
                }
            }
        }
    }


    void MouseController::pick_done()
    {
        if (CanPicking)
        {
			OBJECT_CONTROLLER->HelpDone();
            BaseController* tmpbasecontroller = nullptr;
            size_t previous_size = OBJECT_CONTROLLER->controllers.size();
            for (unsigned int i = 0; i < previous_size; ++i)
            {
                if (OBJECT_CONTROLLER->controllers.at(i)->isInInventory)
                {
					if (mouseX >= Inventory::location.x - Inventory::scale.x / 2 && mouseX <= Inventory::location.x + Inventory::scale.x / 2 && mouseY >= -Inventory::location.y - Inventory::scale.y / 2 && mouseY <= -Inventory::location.y + Inventory::scale.y / 2)
					{
						(OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation(Inventory::location);
						OBJECT_CONTROLLER->objects.at(i)->sprite->isHud = true;
						CanPicking = false;
						return;
					}
					int PlayerX = static_cast<int>(PLAYER_CONTROLLER->GetTransform()->GetTranslation().x);
					int PlayerY = static_cast<int>(PLAYER_CONTROLLER->GetTransform()->GetTranslation().y);
					PlayerX -= static_cast<int>(GRAPHICS->GetCamera()->GetPosition().x);
					PlayerY -= static_cast<int>(GRAPHICS->GetCamera()->GetPosition().y);
				

					if (mouseX >= PlayerX - PLAYER_CONTROLLER->GetTransform()->GetScale().x &&
						mouseX <= PlayerX + PLAYER_CONTROLLER->GetTransform()->GetScale().x &&
						mouseY >= -PlayerY - PLAYER_CONTROLLER->GetTransform()->GetScale().y &&
						mouseY <= -PlayerY + PLAYER_CONTROLLER->GetTransform()->GetScale().y 
						)
					{
						CanPicking = false;
						(OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation(Inventory::location);
						OBJECT_CONTROLLER->objects.at(i)->sprite->isHud = true;
						return;
					}

                    tmpbasecontroller = OBJECT_CONTROLLER->controllers.at(i);
                    OBJECT_CONTROLLER->controllers.at(i)->Interact(ControllerType_NULL);
                    break;
                }
            }
            previous_size = OBJECT_CONTROLLER->controllers.size();
            for (unsigned int i = 0; i < previous_size; ++i)
            {
                if (tmpbasecontroller == OBJECT_CONTROLLER->controllers.at(i) && tmpbasecontroller != nullptr)
                {
                    AUDIO_MANAGER->PlaySound("pick");
                    (OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation(
                        { GRAPHICS->GetCamera()->GetPosition().x + mouseX,GRAPHICS->GetCamera()->GetPosition().y - mouseY, 200 });
                    const glm::vec2 prev_scale = { OBJECT_CONTROLLER->controllers.at(i)->previouswidth, OBJECT_CONTROLLER->controllers.at(i)->previousheight };
                    (OBJECT_CONTROLLER->objects.at(i)->transform)->SetScale(prev_scale);
                    OBJECT_CONTROLLER->controllers.at(i)->isInInventory = false;
                }
            }
            PLAYER_CONTROLLER->SetInventoryState(true);
            CanPicking = false;
        }
    }

    void MouseController::resetPickState()
    {
        CanPicking = false;
    }

    glm::vec2 MouseController::getMousePos()
    {
        return { mouseX,mouseY };
    }
	bool MouseController::GetPickState()
	{
		return CanPicking;
	}
}
