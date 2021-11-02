/*
*  File Name : Level2.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 2.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level2 : public LevelSystem
	{
	public:
		Level2() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level2() {};
	private:
		LevelCollection level;
	};
}
