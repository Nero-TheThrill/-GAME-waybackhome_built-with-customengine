/*
*  File Name : Level5.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 5.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level5 : public LevelSystem
	{
	public:
		Level5() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level5() {};
	private:
		LevelCollection level;
	};
}
