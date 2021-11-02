/*
*  File Name : MouseController.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Choi Jinwoo, Hyun Jina
*  Brief: It does pick up and down from inventory
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"
namespace  BLUE
{
    class MouseController
    {
    public:
        MouseController();
        ~MouseController();
        void update(Sprite* sprite, bool& IsGunFuture, bool& IsFuture);
        void picking();
        void pick_done();
        void resetPickState();
        glm::vec2 getMousePos();
		bool GetPickState();
    private:
        Object * obj;
        Transform* transform;
        int mouseX = 0, mouseY = 0;
        bool CanPicking = false;
        float store_z = 0;
    };
}