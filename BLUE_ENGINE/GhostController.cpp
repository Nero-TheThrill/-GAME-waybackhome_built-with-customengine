/*
*  File Name : GhostController.cpp
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It has only collision state.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "GhostController.h"
#include "ObjectFactory.h"
#include "ObjectController.h"
#include "PlayerController.h"

namespace BLUE
{
	extern GhostController* GHOST_CONTROLLER = nullptr;
    GhostController::GhostController()
    {
        controllertype = ControllerType_GHOST;
		GHOST_CONTROLLER = this;
    }
    void GhostController::update()
    {
        circle->SetRadius(PLAYER_CONTROLLER->GetTransform()->GetScale().x / 2);
        circle->SetPos({ transform->calculatedMatrix[3][0], transform->calculatedMatrix[3][1] });
        for (int i = 0; i < static_cast<int>(OBJECT_CONTROLLER->objects.size()); ++i)
        {
            collision->update(*circle, *(OBJECT_CONTROLLER->objects.at(i)->rectangle));
            ((OBJECT_CONTROLLER->objects.at(i)->collision))
                ->update(*circle, *OBJECT_CONTROLLER->objects.at(i)->rectangle);
        }
    }
    Object * GhostController::Spawn(float x, float y, float z)
    {
        obj = OBJECT_FACTORY->CreateEmptyObject();
        std::string str("Ghost");
        obj->AddComponent(new Transform());
        transform =  (obj->transform);
        obj->AddComponent(new Circle());
        circle =  (obj->circle);
        obj->AddComponent(new Collision());
        collision =  (obj->collision);
        obj->AddComponent(new Sprite());

        obj->SetName(str);
        obj->Init();
        x = 0;
        y = 1.3f;
        z = 0;
        transform->SetTranslation({ x,y,z });
        transform->SetScale({   1 ,1 });
        transform->parent = PLAYER_CONTROLLER->GetTransform();

        (obj->sprite)->SetTexture(T(Picture::Player));
        (obj->sprite)->SetColor({ 255, 255, 255,0 });
        return obj;
    }
    Object * GhostController::GetObject()
    {
        return obj;
    }
    Transform * GhostController::GetTransform()
    {
        return transform;
    }
    void GhostController::ChangeToFuture(bool /*CalledAtStart*/)
    {
    }
    void GhostController::ChangeToPast(bool /*CalledAtStart*/)
    {
    }
    ControllerType GhostController::GetControllerType()
    {
        return controllertype;
    }
    void GhostController::Reset()
    {
    }
    void GhostController::Interact(ControllerType /*controller_type*/)
    {
    }
	CurrentState GhostController::GetCurrentState()
	{
		return currentstate;
	}

    void GhostController::HitPoison()
    {
    }
}
