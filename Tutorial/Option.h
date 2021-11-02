/*
*  File Name : Option.h
*  Primary Author : Park Jinwon
*  Secondary Author : Choi Jinwoo, Hyun Jina
*  Brief: It contains credit and function for controlling volume and setting screen.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelSystem.h"
#include "Button.h"

namespace BLUE
{
    class Option : public LevelSystem
    {
    public:
        Option() {}
        void Init() override;
        void Update() override;
        void Close() override;
        ~Option() {}
    private:
		Button credit, main_menu;

        int mouse_x = 0, mouse_y = 0;
        bool nofunction;
    };
}
