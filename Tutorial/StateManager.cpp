/*
*  File Name : StateManager.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jinwon Park, Hyun Jina
*  Brief: state managing.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "StateManager.h"
#include "MainMenu.h"
#include "TestLevel1.h"
#include "Option.h"
#include "Credit.h"
#include "Splash.h"
#include "TestLevel1_replay.h"
#include "TutoLevel1.h"
#include "TutoLevel2.h"
#include "TutoLevel3.h"
#include "TutoLevel4.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Level7.h"
#include "Level8.h"
#include "Level9.h"
#include "Level10.h"
#include "Level11.h"
#include "LevelSelect.h"
#include "LevelClear.h"

namespace BLUE
{
    StateManager* STATEMANAGER = nullptr;
    StateManager::StateManager()
    {
        STATEMANAGER = this;
    }
    StateManager::~StateManager() = default;

    void StateManager::Init()
    {
        current = LV_SPLASH;
        levels.push_back(new Splash());
        levels.push_back(new MainMenu());
        levels.push_back(new TutoLevel1);
        levels.push_back(new TutoLevel2);
        levels.push_back(new TutoLevel3);
        levels.push_back(new TutoLevel4);
        levels.push_back(new Level1());
        levels.push_back(new Level2());
        levels.push_back(new Level3());
		levels.push_back(new Level4());
		levels.push_back(new Level5());
		levels.push_back(new Level6());
		levels.push_back(new Level7());
		levels.push_back(new Level8());
		levels.push_back(new Level9());
		levels.push_back(new Level10());
		levels.push_back(new Level11());
        levels.push_back(new TestLevel1());
        levels.push_back(new LevelClear());
        levels.push_back(new Option());
        levels.push_back(new Credit());
        levels.push_back(new Level1_replay());
        levels.push_back(new LevelSelect());
        levels.at(current)->Init();
    }
    void StateManager::Update()
    {
        levels.at(current)->Update();
    }

    void StateManager::ChangeLevel(GameLevels changeLV)
    {
		prev_level = current;
        current = changeLV;
        levels.at(current)->Init();
    }
}
