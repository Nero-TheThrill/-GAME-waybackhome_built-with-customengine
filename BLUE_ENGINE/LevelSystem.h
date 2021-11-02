/*
*  File Name : LevelSystem.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Base of level.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
namespace BLUE
{
    class LevelSystem
    {
    public:

        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Close() = 0;
        virtual ~LevelSystem()
        {
        }

    };

};