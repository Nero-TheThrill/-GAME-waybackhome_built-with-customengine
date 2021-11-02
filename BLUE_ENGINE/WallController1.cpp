/*
*  File Name : WallController1.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  brief :
*		Cannot go through the wall
*		Past(Wall) - Present(Wall) - Future(Wall)
*		Interact: Nothing
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "WallController1.h"
#include "ObjectController.h"
#include <iostream>
#include "ObjectFactory.h"
#include"PlayerController.h"

namespace BLUE
{
	Wall1::Wall1() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_WALL1)
	{
	}

	Object* Wall1::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Wall1");
		object->AddComponent(new Transform());
		transform = (object->transform);
		object->AddComponent(new Rectangle());
		rectangle = (object->rectangle);
		object->AddComponent(new Sprite());
		sprite = (object->sprite);
		sprite->SetTexture("texture/Item/Wall1.png");
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

	Object* Wall1::GetObject()
	{
		return object;
	}

	Transform* Wall1::GetTransform()
	{
		return transform;
	}

	void Wall1::SetWall1Scale(float width, float height)
	{
		transform->SetScale({ width,height });
	}

	void Wall1::ChangeToFuture(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Wall (FUTURE)\n";
	}

	void Wall1::ChangeToPast(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Wall (Past)\n";
	}

	ControllerType Wall1::GetControllerType()
	{
		return controllerType;
	}

	void Wall1::Reset()
	{
	}

	void Wall1::Interact(ControllerType /*controller_type*/)
	{
	}
	CurrentState Wall1::GetCurrentState()
	{
		return currentstate;
	}

	void Wall1::HitPoison()
	{
	}
}
