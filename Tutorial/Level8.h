/*
*  File Name : Level8.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 8.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level8 : public LevelSystem
	{
	public:
		Level8() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level8() {};
	private:
		LevelCollection level;
	};
}
