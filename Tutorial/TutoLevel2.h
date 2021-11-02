/*
*  File Name : TutoLevel.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 2.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class TutoLevel2 : public LevelSystem
	{
	public:

		TutoLevel2() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~TutoLevel2() {};
	private:
            LevelCollection level;
	};
}
