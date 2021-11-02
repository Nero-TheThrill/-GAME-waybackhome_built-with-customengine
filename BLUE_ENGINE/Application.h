/*
*  File Name : Application.h
*  Primary Author : Choi Jinwoo
*  Secondary Author :
*  Brief: Basic window
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "System.h"
#include <SDL.h>
#include <GL/glew.h>
#include "Input.h"


namespace BLUE
{
    class Application : public System
    {
    public:
        Application();
        ~Application();

        void Init() override;
        void Update() override;


        SDL_Window* GetWindow() { return pWindow; }
        SDL_Event& GetEvent() { return SDLevent; }

    private:
        //Get events
        /////////////////////////////////////////////////
        void PollEvents();
        void PollWindowEvent(SDL_Event& currentEvent);
        void PollKeyboardEvent(SDL_Event& currentEvent);
        void PollMouseEvent(SDL_Event& currentEvent);
        /////////////////////////////////////////////////


        SDL_Event SDLevent;
        SDL_Window* pWindow;
        int ScreenWidth;
        int ScreenHeight;
        bool initialize_success;
        SDL_GLContext glContext = NULL;
    };

}
