/*
*  File Name : Level6.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 6.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level6 : public LevelSystem
	{
	public:
		Level6() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level6() {};
	private:
		LevelCollection level;
	};
}
