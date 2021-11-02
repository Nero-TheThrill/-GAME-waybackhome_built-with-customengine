/*
*  File Name : TestLevel1.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 1.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include"TestLevel1.h"
namespace BLUE
{
	TestLevel1::TestLevel1()
	{
	}

    void TestLevel1::Init()
    {
        level.InitLEVEL("JSONFILES/test.txt",LV_TESTLEVEL1);
    }

    void TestLevel1::Update()
    {
        level.UpdateLEVEL("JSONFILES/test.txt",LV_MAINMENU);
    }

    void TestLevel1::Close()
    {
        level.CloseLEVEL("JSONFILES/test.txt");
    }
}
