/*
*  File Name : WallController3.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  brief :
*		Cannot go through the wall
*		Past(Wall) - Present(Wall) - Future(Wall)
*		Interact: Nothing
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "WallController3.h"
#include "ObjectController.h"
#include <iostream>
#include "ObjectFactory.h"
#include"PlayerController.h"

namespace BLUE
{
	Wall3::Wall3() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_WALL3)
	{
	}

	Object* Wall3::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Wall3");
		object->AddComponent(new Transform());
		transform = (object->transform);
		object->AddComponent(new Rectangle());
		rectangle = (object->rectangle);
		object->AddComponent(new Sprite());
		sprite = (object->sprite);
		sprite->SetTexture("texture/Item/Wall_1.png");
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

	Object* Wall3::GetObject()
	{
		return object;
	}

	Transform* Wall3::GetTransform()
	{
		return transform;
	}

	void Wall3::SetWall3Scale(float width, float height)
	{
		transform->SetScale({ width,height });
	}

	void Wall3::ChangeToFuture(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Wall (FUTURE)\n";
	}

	void Wall3::ChangeToPast(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Wall (Past)\n";
	}

	ControllerType Wall3::GetControllerType()
	{
		return controllerType;
	}

	void Wall3::Reset()
	{
	}

	void Wall3::Interact(ControllerType /*controller_type*/)
	{
	}
	CurrentState Wall3::GetCurrentState()
	{
		return currentstate;
	}

	void Wall3::HitPoison()
	{
	}
}
