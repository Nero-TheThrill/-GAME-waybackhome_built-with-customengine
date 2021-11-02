/*
*  File Name : TutoLevel1.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 1.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"
namespace BLUE
{
	class TutoLevel1 : public LevelSystem
	{
	public:

		TutoLevel1() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~TutoLevel1() {};
	private:
        LevelCollection level;
	};
}
