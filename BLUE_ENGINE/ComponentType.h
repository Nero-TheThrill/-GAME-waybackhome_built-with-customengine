/*
*  File Name : ComponentType.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Distinguish components with defining enum
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
namespace BLUE
{
    enum ComponentType
    {
        ComponentType_NULL = 0,
        ComponentType_TRANSFORM,
        ComponentType_SPRITE,
        ComponentType_CAMERA,
        ComponentType_RIGIDBODY,
        ComponentType_COLLISION,
        ComponentType_PARTICLE,
        ComponentType_LINE,
        ComponentType_CIRCLE,
        ComponentType_RECTANGLE,
        ComponentType_SPRITETEXT,
		ComponentType_OBB
      //...etc
    };

}