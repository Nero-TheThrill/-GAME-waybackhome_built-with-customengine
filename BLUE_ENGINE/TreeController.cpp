/*
*  File Name : TreeController.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author :Jina Hyun
*  Brief:
*    Past(Seed) - Present(Tree) - Future(Tree)
*    Interact: Axe -> Change tree to log
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"TreeController.h"
#include"ObjectController.h"
#include<iostream>
#include "Archiver.h"
#include "LogController.h"
#include "SmokeEffects.h"
#include "Audio.h"

namespace BLUE
{
	TreeController::TreeController()
	{
		controllertype = ControllerType_TREE;
	}

	Object* TreeController::Spawn(float x, float y, float z)
	{
		obj = OBJECT_FACTORY->CreateEmptyObject();
		std::string str("Tree");
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
		(obj->sprite)->SetTexture(T(Picture::Item_Tree));
		transform->SetTranslation({ x,y,z });
		transform->SetScale({ 224.f, 315.f });
		OBJECT_CONTROLLER->AddObject(obj);
		GRAPHICS->AddSprite(sprite);
		currentstate = PRESENT;
		canMove = false;
                controllertype = ControllerType_TREE;
		return obj;
	}
	Object * TreeController::GetObject()
	{
		return obj;
	}
	Transform * TreeController::GetTransform()
	{
		return transform;
	}

    void TreeController::ChangeToFuture(bool /*CalledAtStart*/)
    {
    }

    void TreeController::ChangeToPast(bool CalledAtStart)
    {
        if (currentstate == PRESENT)
            PresentToPast(CalledAtStart);
    }


    ControllerType TreeController::GetControllerType()
	{
		return controllertype;
	}

	void TreeController::Reset()
	{

	}

	void TreeController::Interact(ControllerType controller_type)
	{
		switch (controller_type)
		{
		case ControllerType_AXE:
		{
			AUDIO_MANAGER->PlaySound("cuttree");
			//std::cout << "The tree becomes the log!\n";
			CreateItem(ControllerType_LOG);
			isUsed = true;
		}
		break;
                case ControllerType_TORCH:
				{
					DeleteThis();
					AUDIO_MANAGER->PlaySound("fire"); }
                    break;
		default:
			break;
		}

		if (isUsed)
		{
			DeleteThis();
		}
	}

	CurrentState TreeController::GetCurrentState()
	{
		return currentstate;
	}

    void TreeController::HitPoison()
    {
        //DeleteThis();
    }

    void TreeController::CreateItem(ControllerType type) const
	{
	
		BaseController * controller = nullptr;
		switch (type)
		{
		case ControllerType_SEED:
			controller = new SeedController;
			break;
		case ControllerType_LOG:
			controller = new LogController;
		default:
			break;
		}
		controller->Spawn(transform->GetTranslation().x, transform->GetTranslation().y-100, transform->GetTranslation().z);
		OBJECT_CONTROLLER->AddController(controller);
	}

	void TreeController::DeleteThis()
	{
		GRAPHICS->DeleteSprite(sprite);
		OBJECT_CONTROLLER->DeleteController(this);
		OBJECT_FACTORY->Destroy(obj);
	}
	void TreeController::PresentToPast(bool CalledAtStart)
	{
		if (!CalledAtStart)

		{
			AUDIO_MANAGER->PlaySound("changeitem");
			SMOKE_EFFECT->Spawn(transform->GetTranslation(), transform->GetScale()*0.5f);
		}
		//std::cout << "Tree will change to a seed!\n";
		CreateItem(ControllerType_SEED);
		DeleteThis();
	}
}
