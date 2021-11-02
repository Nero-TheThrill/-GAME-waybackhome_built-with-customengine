/*
*  File Name : WallController2.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  brief :
*		Cannot go through the wall
*		Past(Wall) - Present(Wall) - Future(Wall)
*		Interact: Nothing
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "WallController2.h"
#include "ObjectController.h"
#include <iostream>
#include "ObjectFactory.h"
#include"PlayerController.h"

namespace BLUE
{
	Wall2::Wall2() :
		object(nullptr),
		transform(nullptr),
		rigidbody(nullptr),
		rectangle(nullptr),
		collision(nullptr),
		sprite(nullptr),
		controllerType(ControllerType_WALL2)
	{
	}

	Object* Wall2::Spawn(float x, float y, float z)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName("Wall2");
		object->AddComponent(new Transform());
		transform = (object->transform);
		object->AddComponent(new Rectangle());
		rectangle = (object->rectangle);
		object->AddComponent(new Sprite());
		sprite = (object->sprite);
		sprite->SetTexture("texture/Item/Wall2.png");
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

	Object* Wall2::GetObject()
	{
		return object;
	}

	Transform* Wall2::GetTransform()
	{
		return transform;
	}

	void Wall2::SetWall2Scale(float width, float height)
	{
		transform->SetScale({ width,height });
	}

	void Wall2::ChangeToFuture(bool /*CalledAtStart*/)
	{
	//	std::cout << "Nothing has changed with Wall (FUTURE)\n";
	}

	void Wall2::ChangeToPast(bool /*CalledAtStart*/)
	{
		//std::cout << "Nothing has changed with Wall (Past)\n";
	}

	ControllerType Wall2::GetControllerType()
	{
		return controllerType;
	}

	void Wall2::Reset()
	{
	}

	void Wall2::Interact(ControllerType /*controller_type*/)
	{
	}
	CurrentState Wall2::GetCurrentState()
	{
		return currentstate;
	}

	void Wall2::HitPoison()
	{
	}
}
