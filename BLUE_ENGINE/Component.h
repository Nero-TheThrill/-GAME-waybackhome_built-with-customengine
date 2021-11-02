/*
*  File Name : Component.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Base for the component. Basic functions are in here.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once

#include"ComponentType.h"

namespace BLUE
{
    class Object;
    //Every component should inheritance this class and implement virtual function
    class Component
    {
    public:
        Component(ComponentType ctype) :ComponentType(ctype) {}
        virtual ~Component() {}
        virtual void Init(){}
        void SetOwner(Object* pobj)
        {
            pObject = pobj;
        }
        Object* GetOwner()
        {
            return pObject;
        }
        ComponentType GetComponentType()
        {
            return ComponentType;
        }

    private:
        friend class Object;
        Component() = delete;
        Object* pObject = nullptr;
        ComponentType ComponentType;
    };

}