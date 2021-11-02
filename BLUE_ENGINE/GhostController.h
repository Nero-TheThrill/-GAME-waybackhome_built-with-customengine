/*
*  File Name : GhostController.h
*  Primary Author : Park Jinwon
*  Secondary Author :
*  Brief: It has only collision state.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"
#include "BaseController.h"

namespace BLUE
{
    class GhostController : public BaseController
    {
    public:
        GhostController();
        void update();
        Object* Spawn(float x, float y, float z) override;
        Object* GetObject();
        Transform* GetTransform();
        void ChangeToFuture(bool CalledAtStart) override;
        void ChangeToPast(bool CalledAtStart) override;
        ControllerType GetControllerType() override;
        void Reset() override;
        void Interact(ControllerType controller_type) override;
		CurrentState GetCurrentState() override;
                void HitPoison() override;
    private:
        Object * obj;
        Transform* transform;
        Rectangle* rectangle;
        Collision* collision;
        ControllerType controllertype;
        Circle* circle;
		CurrentState currentstate;
    };
	extern GhostController* GHOST_CONTROLLER;
};