/*
*  File Name : StateManager.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jinwon Park, Hyun Jina
*  Brief: state managing.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include<vector>
#include "System.h"
#include "LevelSystem.h"

namespace BLUE
{
    //Define enum to manage levels.
    //You have to make sure GameLevels has same order with push_back in Init() function.
    enum GameLevels
    {
        LV_SPLASH,
        LV_MAINMENU,
		LV_TUTORIAL1,
		LV_TUTORIAL2,
		LV_TUTORIAL3,
		LV_TUTORIAL4,
		LV_1,
		LV_2,
        LV_3,
		LV_4,
		LV_5,
		LV_6,
		LV_7,
		LV_8,
		LV_9,
		LV_10,
		LV_11,
        LV_TESTLEVEL1,
		LV_CLEAR,
        LV_OPTION,
        LV_CREDIT,
        LV_LEVEL1_REPLAY,
        LV_LEVELSELECT
        //Add here to make more levels. (LV_Main, LV_Tutorial...etc.)
    };

    //This class manage the state. 
    class StateManager : public System
    {
    public:
        StateManager();
        ~StateManager();
        void Init() override;
        void Update() override;

        //You can change level with this function. To call this function, use " BLUE::STATEMANAGER->ChangeLevel(BLUE::<GameLevels>); " in Level class.
        void ChangeLevel(GameLevels changeLV);

        //Store the current level.
		GameLevels prev_level;
        GameLevels current;
        //Store the levels. You can update multiple levels at the same time with using this.
        std::vector<LevelSystem*> levels;
    };
    extern StateManager* STATEMANAGER;
}
