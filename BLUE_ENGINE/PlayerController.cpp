/*
*  File Name : PlayerController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Control player class. To make code simple.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"PlayerController.h"
#include"ObjectController.h"
#include"BaseController.h"
#include"GhostController.h"
#include <iostream>
#include <SDL.h>
#include "Audio.h"
#include "PoisonBulletController.h"

namespace BLUE
{
    extern PlayerController* PLAYER_CONTROLLER = nullptr;

    PlayerController::PlayerController() : usedBullet(0)
    {
        PLAYER_CONTROLLER = this;
    }

    Object* PlayerController::Spawn()
    {
        obj = OBJECT_FACTORY->CreateEmptyObject();

        obj->AddComponent(new Transform());
        transform = obj->transform;
        obj->AddComponent(new Rectangle());
        rectangle = obj->rectangle;
        obj->AddComponent(new Sprite());
        obj->AddComponent(new Collision());
        collision = obj->collision;
        obj->AddComponent(new Line2D());
        obj->AddComponent(new Rigidbody());
        rigidbody = obj->rigidbody;
        obj->AddComponent(new OBB_Collision());
        obb = obj->obb;
        obj->Init();
        transform->SetScale({ 79.f,71.f });
        transform->SetTranslation({ 0,0,5 });
		(obj->sprite)->SetTexture(T(Picture::Player_Animation_Flip));
		obj->sprite->SetAnimation()->ActivateAnimation();
		obj->sprite->SetAnimation()->SetFrame(6);
        return obj;
    }

    void PlayerController::update()
    {
        RotatePlayer(static_cast<float>(GRAPHICS->GetCamera()->GetPosition().x), static_cast<float>(GRAPHICS->GetCamera()->GetPosition().y));
        rigidbody->update(1.0f);

        CheckCollide();
        for (int i = 0; i < static_cast<int>(OBJECT_CONTROLLER->objects.size()); ++i)
        {
            if ((OBJECT_CONTROLLER->objects[i]->collision)->GetCollisionState())
            {
                BaseController* controller = OBJECT_CONTROLLER->GetCollideWith(obj);
                if (controller != nullptr&&!(controller->isInInventory))
                {
                    controller->Interact(ControllerType_PLAYER);
                }
            }
        }
        for(int i=0;i<static_cast<int>(POISONBULLET_CONTROLLER->bullet.size());i++)
        {
			collision->update(*rectangle, *POISONBULLET_CONTROLLER->bullet.at(i)->rectangle);
			if (collision->GetCollisionState())
			{
				isDead = true;
			}
        }

        if (Input::GetInstance().IsKeyPressed(SDL_SCANCODE_D))
        {
            moveright();
        }
        if (Input::GetInstance().IsKeyReleased(SDL_SCANCODE_D))
        {
            resetright();
        }
        if (Input::GetInstance().IsKeyPressed(SDL_SCANCODE_A))
        {
            moveleft();
        }
        if (Input::GetInstance().IsKeyReleased(SDL_SCANCODE_A))
        {
            resetleft();
        }
        if (Input::GetInstance().IsKeyPressed(SDL_SCANCODE_W))
        {
            moveup();
        }
        if (Input::GetInstance().IsKeyReleased(SDL_SCANCODE_W))
        {
            resetup();
        }
        if (Input::GetInstance().IsKeyPressed(SDL_SCANCODE_S))
        {
            movedown();
        }
        if (Input::GetInstance().IsKeyReleased(SDL_SCANCODE_S))
        {
            resetdown();
        }
    }

    void PlayerController::movedown() const
    {
        rigidbody->velocity.y = -Player::speed;
    }

    void PlayerController::moveup() const
    {
        rigidbody->velocity.y = Player::speed;
    }

    void PlayerController::moveleft()
    {
        rigidbody->velocity.x = -Player::speed;
    }

    void PlayerController::moveright()
    {
        rigidbody->velocity.x = Player::speed;
    }

    void PlayerController::resetdown()
    {
        rigidbody->velocity.y = 0;
    }

    void PlayerController::resetup()
    {
        rigidbody->velocity.y = 0;
    }

    void PlayerController::resetleft()
    {
        rigidbody->velocity.x = 0;
    }

    void PlayerController::resetright()
    {
        rigidbody->velocity.x = 0;
    }

    void PlayerController::reset()
    {
        resetdown();
        resetup();
        resetright();
        resetleft();
    }

    void PlayerController::FindCollideItem(Object * object)
    {
        if (object != nullptr)
            item = object;
    }

    void PlayerController::interaction()
    {
        for (int i = 0; i < static_cast<int>(OBJECT_CONTROLLER->objects.size()); ++i)
        {
            if (CanUsingInventory)
            {
                if (OBJECT_CONTROLLER->controllers.at(i)->CanGetObject())
                {
                    bool IsCollide = ((OBJECT_CONTROLLER->objects[i]->collision)->GetCollisionState());
                    if (IsCollide)
                    {
                        AUDIO_MANAGER->PlaySound("pick");
                        const glm::vec2 prev_scale = (OBJECT_CONTROLLER->objects.at(i)->transform)->GetScale();
                        OBJECT_CONTROLLER->controllers.at(i)->previouswidth = prev_scale.x;
                        OBJECT_CONTROLLER->controllers.at(i)->previousheight = prev_scale.y;
                        (OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation(Inventory::location);
                        //OBJECT_CONTROLLER->objects.at(i)->transform->SetTranslation(	transform->GetTranslation() );
						glm::vec2 setscale = glm::vec2{ Inventory::scale.y*prev_scale.x / prev_scale.y,Inventory::scale.y };
						if(setscale.x> Inventory::scale.x)
						{
							setscale = glm::vec2{ Inventory::scale.x , setscale.y / setscale.x*Inventory::scale.x };
						}
						(OBJECT_CONTROLLER->objects.at(i)->transform)->SetScale(setscale);
                        CanUsingInventory = false;
                        OBJECT_CONTROLLER->controllers.at(i)->isInInventory = true;
                        OBJECT_CONTROLLER->objects.at(i)->sprite->isHud = true;
                        break;
                    }
                }
            }
			//else
			//{
			//	for (unsigned int i = 0; i < OBJECT_CONTROLLER->controllers.size(); ++i)
			//	{
			//		if (OBJECT_CONTROLLER->controllers.at(i)->isInInventory)
			//		{
			//			(OBJECT_CONTROLLER->objects.at(i)->sprite)->isHud = false;

			//			Transform* ghost_transform = new Transform();
			//			ghost_transform->SetTranslation({ 0,1,0 });
			//			ghost_transform->SetScale({ 1,1 });
			//			ghost_transform->parent = transform;
			//			ghost_transform->GetTransformMatrix();
			//			//Translation
			//			(OBJECT_CONTROLLER->objects.at(i)->transform)->SetTranslation(
			//				{ ghost_transform->calculatedMatrix[3][0], ghost_transform->calculatedMatrix[3][1],
			//				transform->GetTranslation().z
			//				});
			//			//Scale
			//			const glm::vec2 prev_scale = { OBJECT_CONTROLLER->controllers.at(i)->previouswidth, OBJECT_CONTROLLER->controllers.at(i)->previousheight };
			//			(OBJECT_CONTROLLER->objects.at(i)->transform)->SetScale(prev_scale);

			//			BaseController* tmpbasecontroller = nullptr;
			//			size_t previous_size = OBJECT_CONTROLLER->controllers.size();
			//			for (unsigned int i = 0; i < previous_size; ++i)
			//			{
			//				if (OBJECT_CONTROLLER->controllers.at(i)->isInInventory)
			//				{
			//					tmpbasecontroller = OBJECT_CONTROLLER->controllers.at(i);
			//					OBJECT_CONTROLLER->controllers.at(i)->Interact(ControllerType_NULL);
			//					break;
			//				}
			//			}
			//			previous_size = OBJECT_CONTROLLER->controllers.size();
			//			for (unsigned int i = 0; i < previous_size; ++i)
			//			{
			//				if (tmpbasecontroller == OBJECT_CONTROLLER->controllers.at(i) && tmpbasecontroller != nullptr)
			//				{
			//					AUDIO_MANAGER->PlaySound("pick");
			//					OBJECT_CONTROLLER->controllers.at(i)->isInInventory = false;
			//				}
			//			}
			//			PLAYER_CONTROLLER->SetInventoryState(true);
			//			delete(ghost_transform);
			//		}
			//	}
			//}
        }
    }

    Transform * PlayerController::GetTransform() const
    {
        return transform;
    }

    bool PlayerController::GetInventoryState() const
    {
        return CanUsingInventory;
    }

    void PlayerController::SetInventoryState(bool can_using_invectory)
    {
        CanUsingInventory = can_using_invectory;
    }

    // check player's collision and move back when collides
    void PlayerController::CheckCollide()
    {
        rectangle->update(Player::collision_scale);

        for (int i = 0; i < static_cast<int>(OBJECT_CONTROLLER->objects.size()); ++i)
        {
            if (!OBJECT_CONTROLLER->controllers.at(i)->isInInventory)
            {
                collision->update(*rectangle, *OBJECT_CONTROLLER->objects.at(i)->rectangle);
                ((OBJECT_CONTROLLER->objects.at(i)->collision))
                    ->update(*rectangle, *OBJECT_CONTROLLER->objects.at(i)->rectangle);
                if (collision->GetInsideState())
                {
                    if (OBJECT_CONTROLLER->objects.at(i)->rigidbody->GetBodyType() != RigidbodyType::None)
                        transform->SetTranslation({ rigidbody->oldpos, 5 });
                }
            }
        }
    }

    Object* PlayerController::GetObject() const
    {
        return obj;
    }

    void PlayerController::RotatePlayer(float cameraposx, float cameraposy) const
    {
        int mouse_x = static_cast<int>(WINDOW_INFORMATION::GetMousePos().x + cameraposx - transform->GetTranslation().x);
        int mouse_y = static_cast<int>(WINDOW_INFORMATION::GetMousePos().y + cameraposy - transform->GetTranslation().y);

        const float angle = Angle::RadianToDegree(atan(abs(mouse_y) / abs(static_cast<float>(mouse_x))));

        if (mouse_x > 0 && mouse_y > 0)
            transform->SetRotation(angle - 90.0f);
        else if (mouse_x < 0 && mouse_y >0)
            transform->SetRotation(-angle + 90.0f);
        else if (mouse_x < 0 && mouse_y < 0)
            transform->SetRotation(angle + 90.0f);
        else if (mouse_x > 0 && mouse_y < 0)
            transform->SetRotation(-angle - 90.0f);

    }

    void PlayerController::ReplayRotatePlayer(glm::vec2 mousePos, glm::vec2 cameraPos) const
    {
        int mouse_x = static_cast<int>(mousePos.x + cameraPos.x - transform->GetTranslation().x);
        int mouse_y = static_cast<int>(mousePos.y + cameraPos.y - transform->GetTranslation().y);

        const float angle = Angle::RadianToDegree(atan(abs(mouse_y) / abs(static_cast<float>(mouse_x))));

        if (mouse_x > 0 && mouse_y > 0)
            transform->SetRotation(angle - 90.0f);
        else if (mouse_x < 0 && mouse_y >0)
            transform->SetRotation(-angle + 90.0f);
        else if (mouse_x < 0 && mouse_y < 0)
            transform->SetRotation(angle + 90.0f);
        else if (mouse_x > 0 && mouse_y < 0)
            transform->SetRotation(-angle - 90.0f);
    }

    void PlayerController::SetPosition(glm::vec3 trans)
    {
        transform->SetTranslation(trans);
    }

    void PlayerController::SetRotate(float rot)
    {
        transform->SetRotation(rot);
    }
}
