/*
*  File Name : MainMenu.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: It contains game name, start button, option button, and end button.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include"MainMenu.h"
#include <iostream>
#include "Graphics.h"
#include "Timer.h"
#include "ObjectFactory.h"
#include "Input.h"
#include "StateManager.h"
#include "Engine.h"
#include "ObjectController.h"
#include "Audio.h"
#include <chrono>
#include <thread>
#include "CursorController.h"

#include "TexturePath.h"
#include "PopupMessage.h"

namespace BLUE
{
    void MainMenu::Init()
    {
        CURSOR_CONTROLLER->Init();
        Timer::GetInstance().Init();

		GRAPHICS->GetCamera()->SetPosition({ 0,0 });
        AUDIO_MANAGER->PlaySound("BGM");

        ////////////////////////////////////////////
        background = OBJECT_FACTORY->CreateEmptyObject();
        background->SetName("GameName");
        background->AddComponent(new Transform());
        background->AddComponent(new Sprite());
        background->Init();
        (background->transform)->SetScale({ 1280, 720 });
        (background->transform)->SetTranslation({ 0, 0,-500 });
        (background->sprite)->SetTexture(T(Picture::Background_MainMenu));
        GRAPHICS->AddSprite(background->sprite);

		////////////////////////////////////////////
		constexpr glm::vec2 button_size(400, 100);
		end_button.Init({ 0, -250, -100 }, button_size, T(Picture::Button_Exit));
		start_button.Init({ 0, 30, -100 }, button_size, T(Picture::Button_Start));
		option_button.Init({ 0.f, -110.f, 100.f }, button_size, T(Picture::Button_Option));
        std::cout << "MainMenu Init" << std::endl;
    }

    void MainMenu::Update()
    {
        CURSOR_CONTROLLER->Update();
		mouse_x = WINDOW_INFORMATION::GetMousePos().x;
		mouse_y = WINDOW_INFORMATION::GetMousePos().y;

        //Mouse Click
        if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
        {
            AUDIO_MANAGER->PlaySound("click_mouse");
        }

        constexpr glm::vec2 plus_size({ 10.0f, 10.0f });

		if (!POPUPMESSAGE->isExist())
		{
			if (start_button.IfButtonClickedTurnSound(mouse_x, mouse_y, "click_mouse"))
			{
				//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();

				STATEMANAGER->ChangeLevel(LV_LEVELSELECT);
				return;
			}

			//Option
			if (option_button.IfButtonClickedTurnSound(mouse_x, mouse_y, "click_mouse"))
			{
				Close();
				STATEMANAGER->ChangeLevel(LV_OPTION);
				return;
			}

			//end
			if (end_button.IfButtonClickedTurnSound(mouse_x, mouse_y, "click_mouse"))
			{
				POPUPMESSAGE->Init();
			}
		}
		else
		{
			bool yes;
			if (POPUPMESSAGE->IsClicked(mouse_x, mouse_y, yes))
			{
				if (yes)
				{
					Close();
					ENGINE->Quit();
					return;
				}
				else
					POPUPMESSAGE->Delete();
			}
		}
    }

    void MainMenu::Close()
    {
		start_button.Delete();
		end_button.Delete();
		option_button.Delete();

		POPUPMESSAGE->Delete();

        AUDIO_MANAGER->StopSound();
        OBJECT_CONTROLLER->Reset("noTXT");
        GRAPHICS->DeleteAll();
        OBJECT_FACTORY->DestroyAllObjects();
    }
}
