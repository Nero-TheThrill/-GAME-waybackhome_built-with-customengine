/*
*  File Name : Level3.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Level 3.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelHeaderCollection.h"
#include "LevelUpdateCollection.h"

namespace BLUE
{
    class Level3 : public LevelSystem
    {
    public:
        Level3() {};
        void Init() override;
        void Update() override;
        void Close() override;
        ~Level3() {};
    private:
        LevelCollection level;
    };
}
