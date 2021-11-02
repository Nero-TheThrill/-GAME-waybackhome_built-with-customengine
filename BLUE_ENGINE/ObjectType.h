/*
*  File Name : ObjectType.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Distinguish object types with enum.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once

namespace BLUE
{
    enum ObjectType
    {
        ObjectType_NULL = 0,
        ObjectType_Destroyed,
        ObjectType_Player,
        ObjectType_Ground
        //etc..
    };

    //Collision Shape
    enum ShapeType
    {
        ShapeType_NULL = 0,
        ShapeType_Circle,
        ShapeType_Box,
        ShapeType_Line
    };
}