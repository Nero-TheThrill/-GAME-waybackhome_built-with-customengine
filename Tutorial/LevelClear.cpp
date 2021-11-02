/*
*  File Name : LevelClear.cpp
*  Primary Author : Hyun Jina
*  Secondary Author : 
*  Brief: Clear name
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "LevelClear.h"
#include "ObjectFactory.h"
#include "Graphics.h"
#include "Audio.h"
#include "CursorController.h"
#include <iostream>
#include "TexturePath.h"
#include "Timer.h"

namespace BLUE
{
	LevelClear::LevelClear()
		: 
			mouse_x(0),
			mouse_y(0),
			start_time(0),
			time(0),
			plus_size(0.f, 0.f),
			background(nullptr),
			birds(nullptr),
			ship(nullptr),
			light(nullptr),
			ribbon(nullptr),
			ship_t(nullptr),
			birds_t(nullptr),
			player_t(nullptr),
			text(nullptr),
			player(nullptr)
	{
	}

	void LevelClear::Init()
	{
		CURSOR_CONTROLLER->Init();
		GRAPHICS->GetCamera()->SetPosition({ 0,0 });
		AUDIO_MANAGER->PlaySound("winstate");
		std::cout << "Clear Level Init" << std::endl;

		constexpr glm::vec2 size(1280, 720);
		MakeObject(background, size, { 0, 0, -500 }, Picture::Background_Sea, "sea");
		MakeObject(ribbon, size, { 0, 0, 550 }, Picture::Clear_Ribbon, "ribbon");
		MakeObject(ship, { 452, 607 }, { -800.f, 0, 0 }, Picture::Clear_Ship, "ship");
		ship_t = ship->transform;
		MakeObject(player, { 452, 607 }, { -800.f, 0, 10 }, Picture::Clear_Player, "player");
		player->sprite->SetAnimation()->SetFrame(6);
		player->sprite->SetAnimation()->ActivateAnimation();
		player_t = player->transform;

		MakeObject(birds, { 330, 160 }, { 0, 220, 10 }, Picture::Clear_Bird, "birds");
		birds->sprite->SetAnimation()->SetFrame(6);
		birds->sprite->SetAnimation()->ActivateAnimation();
		birds_t = birds->transform;

		MakeObject(light, size, { 0, 0, 100 }, Picture::Background_Sea_Light_Effect, "light");
		light->sprite->SetColor({ 255, 255, 255, 100 });

		text = OBJECT_FACTORY->CreateEmptyObject();
		text->SetName("text");
		text->AddComponent(new Transform());
		text->AddComponent(new SpriteText());
		text->Init();
		(text->transform)->SetScale({ 30, 30 });
		(text->transform)->SetTranslation({ -150, 340 , 300 });
		(text->spritetext)->SetFontPath("font/trench100free.ttf");
		text->spritetext->SetText("Press ESC Key to go to the main menu!");
		GRAPHICS->AddSpriteText(text->spritetext);

		time = 0;
		start_time = Timer::GetInstance().GetTime();
		plus_size = { 0.0f, 0.0f };
    }

    void LevelClear::Update()
    {
		CURSOR_CONTROLLER->Update();
		mouse_x = static_cast<int>(WINDOW_INFORMATION::GetMousePos().x);
		mouse_y = static_cast<int>(WINDOW_INFORMATION::GetMousePos().y);

		time = Timer::GetInstance().GetTime() - start_time;


		/* MOVE BIRDS */
		const float b_x = birds_t->GetTranslation().x;

		constexpr float x_bird_min = -900.f, x_bird_max = 900.f;
		if(x_bird_min <= b_x && b_x <= x_bird_max)
		{
			constexpr float speed = 3;
			birds_t->SetPositionX(b_x - speed);
		}
		else if(b_x < x_bird_min)
		{
			birds_t->SetPositionX(x_bird_max);
		}

		/* MOVE SHIP */
		const float ship_y = 100 * sin(time / 30);
		ship_t->SetPositionY(ship_y);
		player_t->SetPositionY(ship_y);

		const float s_x = ship_t->GetTranslation().x;

		constexpr float x_ship_min = -1000.f, x_ship_max = 1000.f;
		if (x_ship_min <= s_x && s_x <= x_ship_max)
		{
			constexpr float speed = 0.5;
			ship_t->SetPositionX(s_x + speed);
			ship_t->SetScale(glm::vec2{ 452, 607 } + plus_size);

			player_t->SetPositionX(s_x + speed);
			player_t->SetScale(glm::vec2{ 452, 607 } +plus_size);

			plus_size += glm::vec2{ 0.1f, 0.1f };
		}
		else if (s_x > x_ship_max)
		{
			ship_t->SetPositionX(x_ship_min);
			ship_t->SetScale({ 452, 607 });
			player_t->SetPositionX(x_ship_min);
			player_t->SetScale({ 452, 607 });

			plus_size = { 0.f, 0.f };
		}

		/* Oscillation */
		constexpr float amplitude = 10;
		constexpr float division = 10;
		ship_t->SetPositionY(amplitude * std::sin(s_x / division) - 70.f + (plus_size.x / 5.f));
		player_t->SetPositionY(amplitude * std::sin(s_x / division) - 70.f + (plus_size.x / 5.f));
		

		if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
		{
			AUDIO_MANAGER->PlaySound("click_mouse");
		}
        if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE))
        {
			Close();
			STATEMANAGER->ChangeLevel(LV_MAINMENU);
			return;
        }
    }

    void LevelClear::Close()
    {
        GRAPHICS->DeleteAllSprites();
		GRAPHICS->DeleteAllSpriteTexts();
        OBJECT_FACTORY->DestroyAllObjects();
    }

	LevelClear::~LevelClear()
	{
		Close();
	}


	void LevelClear::MakeObject(Object*& object, glm::vec2 size, glm::vec3 position, Picture picture, const std::string & name)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName(name);
		object->AddComponent(new Transform());
		object->AddComponent(new Sprite());
		object->Init();

		object->transform->SetScale(size);
		object->transform->SetTranslation(position);

		object->sprite->SetTexture(T(picture));

		GRAPHICS->AddSprite(object->sprite);
	}
}
