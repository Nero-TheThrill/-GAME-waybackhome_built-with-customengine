/*
*  File Name : ControllerType.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Distinguish controller types with enum.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once

namespace BLUE
{
    enum ControllerType
    {
        ControllerType_NULL = 0,
        ControllerType_ANYTHING,
        ControllerType_PLAYER,
        ControllerType_TREE,
        ControllerType_SEED,
        ControllerType_BOX,
        ControllerType_RUSTKEY,
        ControllerType_GHOST,
        ControllerType_AXE,
        ControllerType_LOG,
        ControllerType_RIVER,
        ControllerType_GHOSTRIVER,
        ControllerType_PORTAL,
        ControllerType_WALL,
		ControllerType_WALL1,
		ControllerType_WALL2,
		ControllerType_WALL3,
        ControllerType_SPIKE,
        ControllerType_BLASTFURNACE,
        ControllerType_POISONPLANT,
		ControllerType_DOOR,
        ControllerType_EXCEPTPOISONPLANT,
        ControllerType_VINE,
        ControllerType_TORCH,
		ControllerType_WOODBOARD,
		ControllerType_PUDDLE,
		ControllerType_NUM
        //etc..
    };

    enum CurrentState
    {
        PAST,
        PRESENT,
        FUTURE
    };
}