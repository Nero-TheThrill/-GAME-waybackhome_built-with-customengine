/*
*  File Name : main.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : 
*  Brief: main function
*
*  Copyright (C) 2018 DigiPen Institute of Technology.
*/

#include "Engine.h"
int main()
{
   // dosomething();
    BLUE::Engine* ENGINE = new BLUE::Engine();

    ENGINE->Init();
    ENGINE->GameLoop();
    delete ENGINE;


    return 0;
}