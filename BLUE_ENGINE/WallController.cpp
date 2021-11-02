/*
*  File Name : WallController.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  brief :
*		Cannot go through the wall
*		Past(Wall) - Present(Wall) - Future(Wall)
*		Interact: Nothing
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "WallController.h"
#include "ObjectController.h"
#include <iostream>
#include "ObjectFactory.h"
#include"PlayerController.h"

namespace BLUE
{
	Wall::Wall() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_WALL)
	{
	}

	Object* Wall::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Wall");
		object->AddComponent(new Transform());
		transform = (object->transform);
		object->AddComponent(new Rectangle());
		rectangle = (object->rectangle);
		object->AddComponent(new Sprite());
		sprite = (object->sprite);
		sprite->SetTexture("texture/Item/Wall.png");
		object->AddComponent(new Collision());
		collision = (object->collision);
		object->AddComponent(new Rigidbody());
		rigidbody = (object->rigidbody);
		object->Init();
		canMove = false;
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 50.f,50.f });
		OBJECT_CONTROLLER->AddObject(object);
		GRAPHICS->AddSprite(sprite);
		return object;
	}

	Object* Wall::GetObject()
	{
		return object;
	}

	Transform* Wall::GetTransform()
	{
		return transform;
	}

	void Wall::SetWallScale(float width, float height)
	{
		transform->SetScale({ width,height });
	}

	void Wall::ChangeToFuture(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Wall (FUTURE)\n";
	}

	void Wall::ChangeToPast(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Wall (Past)\n";
	}

	ControllerType Wall::GetControllerType()
	{
		return controllerType;
	}

	void Wall::Reset()
	{
	}

	void Wall::Interact(ControllerType /*controller_type*/)
	{
	}
	CurrentState Wall::GetCurrentState()
	{
		return currentstate;
	}

    void Wall::HitPoison()
    {
    }
}
