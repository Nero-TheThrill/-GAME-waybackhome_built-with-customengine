/*
*  File Name : Credit.cpp
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: to show developers.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "Credit.h"
#include "Timer.h"
#include "TexturePath.h"
#include "Graphics.h"
#include "ObjectFactory.h"
#include <iostream>
#include "Audio.h"
#include "CursorController.h"


namespace BLUE
{
	Credit::Credit() :
		background(nullptr),
		camera(nullptr),
		credit_transform(nullptr),
		mouse_x(0),
		mouse_y(0)
	{
	}

	void Credit::Init()
	{
		CURSOR_CONTROLLER->Init();
		camera = GRAPHICS->GetCamera();
		Timer::GetInstance().Init();
		AUDIO_MANAGER->PlaySound("BGM");

		const glm::vec2 size(1280, 5400);
		const glm::vec3 position(0, -2300, 0);

		MakeObject(background, size, position, Picture::Credit, "credit");
		credit_transform = (background->transform);


		main_menu.Delete();
		main_menu.Init({ 520, -310, 100 }, { 200, 50 }, T(Picture::Button_MainMenu));
		main_menu.SetHud(true);

		std::cout << "Credit Init" << std::endl;
	}

	void Credit::Update()
	{
		CURSOR_CONTROLLER->Update();

		if (Timer::GetInstance().GetTime() > 1.0f)
		{
			if (credit_transform->GetTranslation().y < 2300)
			{
				credit_transform->SetTranslation({ 0, credit_transform->GetTranslation().y + 5.0f , 0.0f });
			}
		}

		if (Input::GetInstance().IsKeyPressed(SDL_SCANCODE_UP) && (credit_transform->GetTranslation().y > -2300))
		{
			credit_transform->SetTranslation({ 0, credit_transform->GetTranslation().y - 10.0f, 0.0f });
		}
		if (Input::GetInstance().IsKeyPressed(SDL_SCANCODE_DOWN) && (credit_transform->GetTranslation().y < 2300))
		{
			credit_transform->SetTranslation({ 0, credit_transform->GetTranslation().y + 10.0f, 0.0f });
		}

		mouse_x = WINDOW_INFORMATION::GetMousePos().x;
		mouse_y = WINDOW_INFORMATION::GetMousePos().y;

		//Mouse Click
		if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
		{
			AUDIO_MANAGER->PlaySound("click_mouse");
		}

		// button clicked
		if (main_menu.IsButtonClicked(mouse_x, mouse_y)
			|| Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE))
		{
			AUDIO_MANAGER->PlaySound("click_mouse");
			Close();
			STATEMANAGER->ChangeLevel(LV_MAINMENU);
			return;
		}

	}
	void Credit::Close()
	{
		main_menu.Delete();
		GRAPHICS->DeleteAll();
		OBJECT_FACTORY->DestroyAllObjects();
		AUDIO_MANAGER->StopSound();
	}

	Credit::~Credit()
	{
		Close();
	}

	void Credit::MakeObject(Object*& object, glm::vec2 size, glm::vec3 position, Picture picture, const std::string & name)
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
