/*
*  File Name : PlayerController.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief:  Control player class. To make code simple.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"
namespace BLUE
{
    class CursorController
    {
    public:
        CursorController();
        void Init();
        void Update();
      
    private:


        Object * obj;
        Transform* transform;
        int mx, my;

    };
    extern CursorController* CURSOR_CONTROLLER;

}
