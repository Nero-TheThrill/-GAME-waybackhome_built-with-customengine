/*
*  File Name : Level10.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 10.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level10 : public LevelSystem
	{
	public:
		Level10() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level10() {};
	private:
		LevelCollection level;
	};
}
