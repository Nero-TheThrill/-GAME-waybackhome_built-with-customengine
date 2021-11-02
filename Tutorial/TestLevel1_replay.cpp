/*
*  File Name : TestLevel1_replay.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: replay for test_level_1
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "TestLevel1_replay.h"
#include "ReplaySystem.h"
#include "PlayerController.h"
#include "Archiver.h"
#include "StateManager.h"
#include "CursorController.h"

namespace BLUE
{
   

    void Level1_replay::Init()
    {
        CURSOR_CONTROLLER->Init();
        JSONREADER = new rapidjson::JSONreader(ReadFromFile("JSONFILES/level1.txt").c_str());
        AUDIO_MANAGER->PlaySound("BGM");

        JSONREADER->InitializeObject();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////
        background = OBJECT_FACTORY->CreateEmptyObject();
        background->SetName("BackGround");
        background->AddComponent(new Transform());
        background->AddComponent(new Sprite());
        background->Init();
        (background->transform)->SetScale({ 2560, 1440 });
        (background->transform)->SetTranslation({ 0, 0,-999 });
        (background->sprite)->SetTexture(T(Picture::Background_InGame));
        GRAPHICS->AddSprite(background->sprite);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

      
        REPLAY_SYSTEM->Init();
    }

    void Level1_replay::Update()
    {
        CURSOR_CONTROLLER->Update();
        if (REPLAY_SYSTEM->IsDone())
        {
            Close();
            STATEMANAGER->ChangeLevel(LV_CLEAR);
        }
        else
        REPLAY_SYSTEM->replay();
    }

    void Level1_replay::Close()
    {
        REPLAY_SYSTEM->Close();
        delete JSONREADER;
    }
}
