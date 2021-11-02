/*
*  File Name : TestLevel1.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 1.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelSystem.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	enum class Picture;

	class TestLevel1 : public LevelSystem
    {
    public:

		TestLevel1();
        void Init() override;
        void Update() override;
        void Close() override;
        ~TestLevel1() {};
    private:
		LevelCollection level;
    };
}
