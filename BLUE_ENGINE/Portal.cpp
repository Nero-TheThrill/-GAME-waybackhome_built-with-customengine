/*
*  File Name : ExitDoorController.cpp
*  Primary Author : Hyun Jina
*  Secondary Author : Choi Jinwoo
*  Brief:
*  Determine whether the game is cleared or not.
	(If the player collide with this object, it means he clear the game)
	Past(Potal) - Present(Potal) - Future(Potal)
	Interact: Player -> Potal: clear the game
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Portal.h"
#include "ObjectController.h"
#include <iostream>
#include "ObjectFactory.h"
#include"PlayerController.h"

namespace BLUE
{
	Portal::Portal() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_PORTAL)
	{
	}

	Object* Portal::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Portal");
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
		sprite->SetTexture(T(Picture::Item_Portal));
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 81.f,81.f });
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);
		return object;
	}

	Object* Portal::GetObject()
	{
		return object;
	}

	Transform* Portal::GetTransform()
	{
		return transform;
	}

	void Portal::ChangeToFuture(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Door (FUTURE)\n";
	}

	void Portal::ChangeToPast(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Door (Past)\n";
	}

	ControllerType Portal::GetControllerType()
	{
		return controllerType;
	}

	void Portal::Reset()
	{
	}

	void Portal::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
			// when it release from inventory ( When the user tries to use item in inventory)
		case ControllerType_PLAYER:
		{
			PLAYER_CONTROLLER->isClearTheGame = true;
		}
		break;
		default:
			break;
		}
	}
	CurrentState Portal::GetCurrentState()
	{
		return currentstate;
	}

    void Portal::HitPoison()
    {
    }
}
