/*
*  File Name : main.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: main loop of the engine.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#define _CRTDBG_MAP_ALLOC
#include<cstdlib>
#include<crtdbg.h>
#ifdef _DEBUG
#define NEW new (_NORMAL_BLOCK, __FILE__,__LINE__)
#else
#define NEW new
#endif

#include "Engine.h"
#include "windows.h"	

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //make new Engine
    BLUE::Engine* ENGINE = new BLUE::Engine();

    //Initialize Engine
    ENGINE->Init();

    //GameLoop
    ENGINE->GameLoop();

    ENGINE->Quit();
    //If the gameloop ends, delete Engine
    delete ENGINE;

    return 0;
}
