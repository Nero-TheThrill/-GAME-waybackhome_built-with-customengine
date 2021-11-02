/*
*  File Name : Option.h
*  Primary Author : Park Jinwon
*  Secondary Author : Choi Jinwoo, Hyun Jina
*  Brief: It contains credit and function for controlling volume and setting screen.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Option.h"
#include "PauseScreen.h"
#include "Audio.h"
#include "CursorController.h"
#include "TexturePath.h"
#include "Graphics.h"
#include "ObjectFactory.h"
#include <iostream>
#include "SmokeEffects.h"

namespace BLUE
{
    void Option::Init()
    {
        CURSOR_CONTROLLER->Init();
        PAUSE_SCREEN->Pause(&nofunction,false);
		GRAPHICS->GetCamera()->SetPosition({0, 0});
        AUDIO_MANAGER->PlaySound("BGM");

		main_menu.Delete();
		credit.Delete();

		credit.Init({ 500, -250, 100 }, { 200, 50 }, T(Picture::Button_Credit));
		main_menu.Init({ -500, -250, 100 }, { 200, 50 }, T(Picture::Button_MainMenu));

        std::cout << "Option Init" << std::endl;
    }
    void Option::Update()
    {
        CURSOR_CONTROLLER->Update();
        PAUSE_SCREEN->Update();
        mouse_x = static_cast<int>(WINDOW_INFORMATION::GetMousePos().x);
        mouse_y = static_cast<int>(WINDOW_INFORMATION::GetMousePos().y);

		//Mouse Click
		if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
		{
			AUDIO_MANAGER->PlaySound("click_mouse");
		}

        //main menu
        if(main_menu.IsButtonClicked(mouse_x, mouse_y))
        {
			AUDIO_MANAGER->PlaySound("click_mouse");
			Close();
			STATEMANAGER->ChangeLevel(LV_MAINMENU);
			return;
        }

		// credit
		if (credit.IsButtonClicked(mouse_x, mouse_y))
		{
			AUDIO_MANAGER->PlaySound("click_mouse");
			Close();
			STATEMANAGER->ChangeLevel(LV_CREDIT);
			return;
		}

        if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE))
        {
            Close();
			STATEMANAGER->ChangeLevel(LV_MAINMENU);
        }
    }
    void Option::Close()
    {
		main_menu.Delete();
		credit.Delete();
		SMOKE_EFFECT->DestroyAll();
        AUDIO_MANAGER->StopSound();
        PAUSE_SCREEN->Resume(&nofunction);
        GRAPHICS->DeleteAll();
        OBJECT_FACTORY->DestroyAllObjects();
	
    }
}
