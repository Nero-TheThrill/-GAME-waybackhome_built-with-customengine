/*
*  File Name : Level4.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 4.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level4 : public LevelSystem
	{
	public:
		Level4() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level4() {};
	private:
		LevelCollection level;
	};
}
