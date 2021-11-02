/*
*  File Name : Splash.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Splash digipen logo.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Splash.h"
#include "Timer.h"
#include "ObjectFactory.h"
#include "Graphics.h"
#include <iostream>
#include "StateManager.h"
#include "ObjectController.h"
#include "SDL.h"
#include "CursorController.h"
#include "TexturePath.h"

namespace BLUE
{
    void Splash::Init()
    {
        CURSOR_CONTROLLER->Init();
        go_next_level = false;
        fmod = false;
        Timer::GetInstance().Init();
        input = Input::GetInstance();
        ////////////////////////////////////////////
        splash = OBJECT_FACTORY->CreateEmptyObject();
        splash->SetName("splash");
        splash->AddComponent(new Transform());
        splash->AddComponent(new Sprite());
        splash->Init();
        (splash->transform)->SetScale({ 2200, 1400 });
        (splash->transform)->SetTranslation({ 0, 0,0 });
        splash_sprite = (splash->sprite);
        splash_sprite->SetTexture(T(Picture::Splash_Digipen));
        GRAPHICS->AddSprite(splash_sprite);
        ////////////////////////////////////////////
        text = OBJECT_FACTORY->CreateEmptyObject();
        text->SetName("text");
        text->AddComponent(new Transform());
        text->AddComponent(new SpriteText());
        text->Init();
        (text->transform)->SetScale({ 30, 30 });
        (text->transform)->SetTranslation({ -150, 340 , 300 });
        (text->spritetext)->SetFontPath("font/trench100free.ttf");
        GRAPHICS->AddSpriteText(text->spritetext);
        ////////////////////////////////////////////
        animation = OBJECT_FACTORY->CreateEmptyObject();
        animation->SetName("text");
        animation->AddComponent(new Transform());
        animation->AddComponent(new Sprite());
        animation->Init();
        (animation->transform)->SetScale({ 1400, 800 });
        (animation->transform)->SetTranslation({ 0, 0,200 });
		animation->transform->SetRotation(30);
        (animation->sprite)->SetTexture("texture/etc/splash_animation.png");

        (animation->sprite)->SetColor({ 255, 255, 255, 0 });
        (animation->sprite)->SetAnimation()->SetFrame(5);
        (animation->sprite)->SetAnimation()->SetSpeed(20);
        GRAPHICS->AddSprite(animation->sprite);
        ////////////////////////////////////////////////

		first = true;

        std::cout << "Splash Init" << std::endl;
    }
    void Splash::Update()
    {
        CURSOR_CONTROLLER->Update();
        if (go_next_level)
        {
            if (input.IsAnyKeyTriggered() || input.IsMouseTriggered(SDL_BUTTON_LEFT) || input.IsMouseTriggered(SDL_BUTTON_RIGHT))
            {
                Close();

                STATEMANAGER->ChangeLevel(LV_MAINMENU);
            }
        }
        else if (fmod)
        {
            if (Timer::GetInstance().GetTime() - time > 1.8f || input.IsAnyKeyTriggered() || input.IsMouseTriggered(SDL_BUTTON_LEFT) || input.IsMouseTriggered(SDL_BUTTON_RIGHT))
            {
                splash_sprite->SetTexture(T(Picture::Splash_Game));
                (text->spritetext)->SetText("Press any key to start!");
                (animation->sprite)->SetColor({ 255, 255, 255, 100 });
				(animation->sprite)->SetAnimation()->ActivateAnimation();

                go_next_level = true;
            }
        }
        else if (!fmod && !go_next_level)
        {
			if(!first && !is_all_textures_loaded)
			{
				is_all_textures_loaded = GRAPHICS->InitAllTextures();

				if(is_all_textures_loaded)
					time = Timer::GetInstance().GetTime();
			}
			
            if (Timer::GetInstance().GetTime() - time > 2.f || input.IsAnyKeyTriggered() || input.IsMouseTriggered(SDL_BUTTON_LEFT) || input.IsMouseTriggered(SDL_BUTTON_RIGHT))
            {
                (splash->transform)->SetScale({ 1280, 720 });
                splash_sprite->SetTexture(T(Picture::Splash_FMOD));
                fmod = true;
                time = Timer::GetInstance().GetTime();
            }
        }

		first = false;
    }
    void Splash::Close()
    {
        OBJECT_CONTROLLER->Reset("noTXT");
        GRAPHICS->DeleteAll();
        OBJECT_FACTORY->DestroyAllObjects();
    }
}
