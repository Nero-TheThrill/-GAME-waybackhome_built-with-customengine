/*
*  File Name : Level7.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 7.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level7 : public LevelSystem
	{
	public:
		Level7() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level7() {};
	private:
		LevelCollection level;
	};
}
