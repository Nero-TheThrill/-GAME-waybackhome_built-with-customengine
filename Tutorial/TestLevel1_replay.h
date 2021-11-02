/*
*  File Name : TestLevel1_replay.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: replay for test_level_1
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/


#pragma once
#include "LevelSystem.h"
#include "Object.h"
#include "Camera.h"
#include "JSONREADER.h"
#include "JSONWRITER.h"
#include "BulletController.h"
#include "LerpSmoothing.h"

namespace BLUE
{
    class Level1_replay : public LevelSystem
    {
    public:

        Level1_replay() {};
        void Init() override;
        void Update() override;
        void Close() override;
        ~Level1_replay() {};
    private:
    
        Object* background;
        bool IsGunFuture = true;
        //RemainBullet remain_bullet;
        rapidjson::JSONwriter* JSONWRITER;
        rapidjson::JSONreader* JSONREADER;

    };
}
