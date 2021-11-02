/*
*  File Name : Level11.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 11.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level11 : public LevelSystem
	{
	public:
		Level11() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level11() {};
	private:
		LevelCollection level;
	};
}
