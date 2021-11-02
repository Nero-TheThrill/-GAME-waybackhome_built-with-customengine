/*
*  File Name : BaseController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Base for the controllers. Controllers will inherit this class.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "ControllerType.h"
#include "Object.h"
#include "TexturePath.h"

namespace BLUE
{
    class BaseController
    {
    public:
        virtual Object* Spawn(float x, float y, float z) = 0;
        virtual void ChangeToPast(bool CalledAtStart=false) = 0;
        virtual void ChangeToFuture(bool CalledAtStart = false) = 0;
        virtual ControllerType GetControllerType() = 0;
        virtual void Reset() = 0;
        virtual void Interact(ControllerType controller_type = ControllerType_NULL) = 0;
		virtual CurrentState GetCurrentState() = 0;
                virtual void HitPoison()=0;
        bool CanGetObject();
        bool isInInventory = false;
        bool canMove = false;
        bool isDoortype = false;
        float previouswidth = 0.0f;
        float previousheight = 0.0f;
        ~BaseController() = default;
    };

    inline bool BaseController::CanGetObject()
    {
        return canMove;
    }
}
