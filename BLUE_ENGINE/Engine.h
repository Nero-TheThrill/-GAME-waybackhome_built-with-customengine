/*
*  File Name : Engine.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Base of the engine. All systems will managed by this class.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include<vector>

namespace BLUE
{
    class System;
    class Engine
    {
    public:
        Engine();
        ~Engine();

        void Init();

        //Loop here while GAMERUN is true
        void GameLoop();

        //Stop engine. You can call with using "BLUE::ENGINE->QUIT()"
        void Quit();

        //Add systems like application, stagemanager to update all.
        void AddSystem(System* system);

        void calculateFPS();

    private:
        std::vector<System*> Systems; //Store systems here and update all.
        bool GAMERUN;  //Check game is running. If it is false, stop the gameloop.
        float fps_;
    };
    extern Engine* ENGINE; // global pointer of the instance of engine.
}