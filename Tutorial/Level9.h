/*
*  File Name : Level9.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 9.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class Level9 : public LevelSystem
	{
	public:
		Level9() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~Level9() {};
	private:
		LevelCollection level;
	};
}
