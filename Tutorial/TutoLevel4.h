/*
*  File Name : TutoLevel4.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Park Jinwon, Hyun Jina
*  Brief: Level 4.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
	class TutoLevel4 : public LevelSystem
	{
	public:

		TutoLevel4() {};
		void Init() override;
		void Update() override;
		void Close() override;
		~TutoLevel4() {};
	private:
            LevelCollection level;
	};
}	