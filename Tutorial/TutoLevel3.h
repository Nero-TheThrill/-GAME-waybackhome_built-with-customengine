/*
*  File Name : TutoLevel3.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 3.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class TutoLevel3 : public LevelSystem
	{
	public:

		TutoLevel3() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~TutoLevel3() {};
	private:
            LevelCollection level;
	};
}
