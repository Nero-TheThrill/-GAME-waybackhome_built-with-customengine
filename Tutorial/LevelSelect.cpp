/*
*  File Name : LevelSelect.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jina Hyun, Jinwon Park
*  Brief: level select screen
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/


#include"LevelSelect.h"
#include "CursorController.h"
#include "Archiver.h"
#include "Timer.h"
#include "Engine.h"
#include <iostream>
#include "LevelUpdateCollection.h"
#include <thread>
namespace BLUE
{
	void LevelSelect::Init()
	{
		CURSOR_CONTROLLER->Init();
		Timer::GetInstance().Init();

		GRAPHICS->GetCamera()->SetPosition({ 0, 0 });

		AUDIO_MANAGER->PlaySound("BGM");

		constexpr glm::vec2 digit_1(40, 59);
		constexpr glm::vec2 digit_2(77, 59);
		
		if (first)
		{
			MakeObject(player, { 150, 200 }, { -450, 350, 150 }, T(Picture::Player_Parachute), "player");
			player->sprite->SetAnimation()->SetFrame(10);
			player->sprite->SetAnimation()->ActivateAnimation();
		}

		////////////////////////////////////////////
		background = OBJECT_FACTORY->CreateEmptyObject();
		background->SetName("GameName");
		background->AddComponent(new Transform());
		background->AddComponent(new Sprite());
		background->Init();
		(background->transform)->SetScale({ 1280, 720 });
		(background->transform)->SetTranslation({ 0, 0,-500 });
		(background->sprite)->SetTexture(T(Picture::Background_LevelSelect));
		GRAPHICS->AddSprite(background->sprite);
		////////////////////////////////////////////
		x_1 = OBJECT_FACTORY->CreateEmptyObject();
		x_1->SetName("x_1");
		x_1->AddComponent(new Transform());
		x_1->AddComponent(new Sprite());
		x_1->Init();
		(x_1->transform)->SetScale(digit_1);
		(x_1->transform)->SetTranslation({ -314,-198,101 });
		(x_1->sprite)->SetTexture(T(Picture::grey_icon_2));
		GRAPHICS->AddSprite(x_1->sprite);
		////////////////////////////////////////////
		x_2 = OBJECT_FACTORY->CreateEmptyObject();
		x_2->SetName("x_2");
		x_2->AddComponent(new Transform());
		x_2->AddComponent(new Sprite());
		x_2->Init();
		(x_2->transform)->SetScale(digit_1);
		(x_2->transform)->SetTranslation({ -230,-105,101 });
		(x_2->sprite)->SetTexture(T(Picture::grey_icon_3));
		GRAPHICS->AddSprite(x_2->sprite);
		////////////////////////////////////////////
		x_3 = OBJECT_FACTORY->CreateEmptyObject();
		x_3->SetName("x_3");
		x_3->AddComponent(new Transform());
		x_3->AddComponent(new Sprite());
		x_3->Init();
		(x_3->transform)->SetScale(digit_1);
		(x_3->transform)->SetTranslation({ -334,-3,101 });
		(x_3->sprite)->SetTexture(T(Picture::grey_icon_4));
		GRAPHICS->AddSprite(x_3->sprite);
		////////////////////////////////////////////
		x_4 = OBJECT_FACTORY->CreateEmptyObject();
		x_4->SetName("x_4");
		x_4->AddComponent(new Transform());
		x_4->AddComponent(new Sprite());
		x_4->Init();
		(x_4->transform)->SetScale(digit_1);
		(x_4->transform)->SetTranslation({ -271,107,101 });
		(x_4->sprite)->SetTexture(T(Picture::grey_icon_5));
		GRAPHICS->AddSprite(x_4->sprite);
		////////////////////////////////////////////
		x_5 = OBJECT_FACTORY->CreateEmptyObject();
		x_5->SetName("x_5");
		x_5->AddComponent(new Transform());
		x_5->AddComponent(new Sprite());
		x_5->Init();
		(x_5->transform)->SetScale(digit_1);
		(x_5->transform)->SetTranslation({ -135,1,101 });
		(x_5->sprite)->SetTexture(T(Picture::grey_icon_6));
		GRAPHICS->AddSprite(x_5->sprite);
		////////////////////////////////////////////
		x_6 = OBJECT_FACTORY->CreateEmptyObject();
		x_6->SetName("x_6");
		x_6->AddComponent(new Transform());
		x_6->AddComponent(new Sprite());
		x_6->Init();
		(x_6->transform)->SetScale(digit_1);
		(x_6->transform)->SetTranslation({ -73,-112,101 });
		(x_6->sprite)->SetTexture(T(Picture::grey_icon_7));
		GRAPHICS->AddSprite(x_6->sprite);
		////////////////////////////////////////////
		x_7 = OBJECT_FACTORY->CreateEmptyObject();
		x_7->SetName("x_7");
		x_7->AddComponent(new Transform());
		x_7->AddComponent(new Sprite());
		x_7->Init();
		(x_7->transform)->SetScale(digit_1);
		(x_7->transform)->SetTranslation({ 62,-207,101 });
		(x_7->sprite)->SetTexture(T(Picture::grey_icon_8));
		GRAPHICS->AddSprite(x_7->sprite);
		////////////////////////////////////////////
		x_8 = OBJECT_FACTORY->CreateEmptyObject();
		x_8->SetName("x_8");
		x_8->AddComponent(new Transform());
		x_8->AddComponent(new Sprite());
		x_8->Init();
		(x_8->transform)->SetScale(digit_1);
		(x_8->transform)->SetTranslation({ 78,46,101 });
		(x_8->sprite)->SetTexture(T(Picture::grey_icon_9));
		GRAPHICS->AddSprite(x_8->sprite);
		////////////////////////////////////////////
		x_9 = OBJECT_FACTORY->CreateEmptyObject();
		x_9->SetName("x_9");
		x_9->AddComponent(new Transform());
		x_9->AddComponent(new Sprite());
		x_9->Init();
		(x_9->transform)->SetScale(digit_2);
		(x_9->transform)->SetTranslation({ 251, 8,101 });
		(x_9->sprite)->SetTexture(T(Picture::grey_icon_10));
		GRAPHICS->AddSprite(x_9->sprite);
		////////////////////////////////////////////
		x_10 = OBJECT_FACTORY->CreateEmptyObject();
		x_10->SetName("x_10");
		x_10->AddComponent(new Transform());
		x_10->AddComponent(new Sprite());
		x_10->Init();
		(x_10->transform)->SetScale(digit_2);
		(x_10->transform)->SetTranslation({ 391,-67,101 });
		(x_10->sprite)->SetTexture(T(Picture::grey_icon_11));
		GRAPHICS->AddSprite(x_10->sprite);
		////////////////////////////////////////////
		x_11 = OBJECT_FACTORY->CreateEmptyObject();
		x_11->SetName("x_11");
		x_11->AddComponent(new Transform());
		x_11->AddComponent(new Sprite());
		x_11->Init();
		(x_11->transform)->SetScale(digit_2);
		(x_11->transform)->SetTranslation({ 343,-198,101 });
		(x_11->sprite)->SetTexture(T(Picture::grey_icon_12));
		GRAPHICS->AddSprite(x_11->sprite);
		////////////////////////////////////////////



		button.clear();
		for (int i = 0; i < 13; i++)
			button.push_back(Button{});

		button.at(0).Init({ 0,-300,100 }, glm::vec2(86, 82), T(Picture::Button_X));

		button.at(1).Init({ -464,-110,100 }, digit_1, T(Picture::Icon_1));
		button.at(2).Init({ -314,-198,100 }, digit_1, T(Picture::Icon_2));
		button.at(3).Init({ -230,-105,100 }, digit_1, T(Picture::Icon_3));
		button.at(4).Init({ -334,-3,100 }, digit_1, T(Picture::Icon_4));
		button.at(5).Init({ -271,107,100 }, digit_1, T(Picture::Icon_5));
		button.at(6).Init({ -135,1,100 }, digit_1, T(Picture::Icon_6));
		button.at(7).Init({ -73,-112,100 }, digit_1, T(Picture::Icon_7));
		button.at(8).Init({ 62,-207,100 }, digit_1, T(Picture::Icon_8));
		button.at(9).Init({ 78,46,100 }, digit_1, T(Picture::Icon_9));
		button.at(10).Init({ 251, 8,100 }, digit_2, T(Picture::Icon_10));
		button.at(11).Init({ 391,-67,100 }, digit_2, T(Picture::Icon_11));
		button.at(12).Init({ 343,-198,100 }, digit_2, T(Picture::Icon_12));


		wall = OBJECT_FACTORY->CreateEmptyObject();
		wall->SetName("white");
		wall->AddComponent(new Transform());
		wall->AddComponent(new Sprite());
		wall->Init();
		(wall->transform)->SetScale({ 1280, 7200 });
		(wall->transform)->SetTranslation({ 0, 0,200 });
		(wall->sprite)->SetTexture(T(Picture::Effect_Fade));
		(wall->sprite)->SetColor({ 255, 255, 255, 0 });
		GRAPHICS->AddSprite(wall->sprite);

		////////////////////////////////////////////////
		std::cout << "LevelSelect Init" << std::endl;
	}

	void LevelSelect::Update()
	{
		if (play_once[1] == true && x_1)
		{
			if (goingnext[0] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_1);
				GRAPHICS->DeleteSprite(x_1->sprite);
				x_1 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[0] = true;
				STATEMANAGER->ChangeLevel(LV_1);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_1);
				GRAPHICS->DeleteSprite(x_1->sprite);
				x_1 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[2] == true && x_2)
		{
			if (goingnext[1] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_2);
				GRAPHICS->DeleteSprite(x_2->sprite);
				x_2 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[1] = true;
				STATEMANAGER->ChangeLevel(LV_2);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_2);
				GRAPHICS->DeleteSprite(x_2->sprite);
				x_2 = nullptr;
				GRAPHICS->Update();
			}

		}
		if (play_once[3] == true && x_3)
		{
			if (goingnext[2] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_3);
				GRAPHICS->DeleteSprite(x_3->sprite);
				x_3 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[2] = true;
				STATEMANAGER->ChangeLevel(LV_3);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_3);
				GRAPHICS->DeleteSprite(x_3->sprite);
				x_3 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[4] == true && x_4)
		{
			if (goingnext[3] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_4);
				GRAPHICS->DeleteSprite(x_4->sprite);
				x_4 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[3] = true;
				STATEMANAGER->ChangeLevel(LV_4);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_4);
				GRAPHICS->DeleteSprite(x_4->sprite);
				x_4 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[5] == true && x_5)
		{
			if (goingnext[4] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_5);
				GRAPHICS->DeleteSprite(x_5->sprite);
				x_5 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[4] = true;
				STATEMANAGER->ChangeLevel(LV_5);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_5);
				GRAPHICS->DeleteSprite(x_5->sprite);
				x_5 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[6] == true && x_6)
		{
			if (goingnext[5] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_6);
				GRAPHICS->DeleteSprite(x_6->sprite);
				x_6 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[5] = true;
				STATEMANAGER->ChangeLevel(LV_6);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_6);
				GRAPHICS->DeleteSprite(x_6->sprite);
				x_6 = nullptr;
				GRAPHICS->Update();
			}
		}

		if (play_once[7] == true && x_7)
		{
			if (goingnext[6] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_7);
				GRAPHICS->DeleteSprite(x_7->sprite);
				x_7 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[6] = true;
				STATEMANAGER->ChangeLevel(LV_7);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_7);
				GRAPHICS->DeleteSprite(x_7->sprite);
				x_7 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[8] == true && x_8)
		{
			if (goingnext[7] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_8);
				GRAPHICS->DeleteSprite(x_8->sprite);
				x_8 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[7] = true;
				STATEMANAGER->ChangeLevel(LV_8);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_8);
				GRAPHICS->DeleteSprite(x_8->sprite);
				x_8 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[9] == true && x_9)
		{
			if (goingnext[8] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_9);
				GRAPHICS->DeleteSprite(x_9->sprite);
				x_9 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[8] = true;
				STATEMANAGER->ChangeLevel(LV_9);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_9);
				GRAPHICS->DeleteSprite(x_9->sprite);
				x_9 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[10] == true && x_10)
		{
			if (goingnext[9] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_10);
				GRAPHICS->DeleteSprite(x_10->sprite);
				x_10 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[9] = true;
				STATEMANAGER->ChangeLevel(LV_10);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_10);
				GRAPHICS->DeleteSprite(x_10->sprite);
				x_10 = nullptr;
				GRAPHICS->Update();
			}
		}
		if (play_once[11] == true && x_11)
		{
			if (goingnext[10] == false)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				AUDIO_MANAGER->PlaySound("level_change");
				OBJECT_FACTORY->Destroy(x_11);
				GRAPHICS->DeleteSprite(x_11->sprite);
				x_11 = nullptr;
				GRAPHICS->Update();
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Close();
				goingnext[10] = true;
				STATEMANAGER->ChangeLevel(LV_11);
			}
			else
			{
				OBJECT_FACTORY->Destroy(x_11);
				GRAPHICS->DeleteSprite(x_11->sprite);
				x_11 = nullptr;
				GRAPHICS->Update();
			}
		}

		CURSOR_CONTROLLER->Update();
		mouse_x = static_cast<int>(WINDOW_INFORMATION::GetMousePos().x);
		mouse_y = static_cast<int>(WINDOW_INFORMATION::GetMousePos().y);

		if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
		{
			AUDIO_MANAGER->PlaySound("click_mouse");
		}


		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE))
		{
			Close();
			STATEMANAGER->ChangeLevel(LV_MAINMENU);
		}

		if (!button.empty())
		{
			HoverEvent();
			ClickEvent();
		}

		UpdatePlayer();
		UnlockNextLevel();
		OpenAllLevels();

		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_END))
		{
			Close();
			STATEMANAGER->ChangeLevel(LV_CLEAR);
		}
	}

	void LevelSelect::Close()
	{
		for (Button b : button)
		{
			b.Delete();
		}
		button.clear();

		AUDIO_MANAGER->StopSound();
		OBJECT_CONTROLLER->Reset("noTXT");

		OBJECT_FACTORY->Destroy(background);
		GRAPHICS->DeleteSprite(background->sprite);

		player = nullptr;
		first = false;
		GRAPHICS->DeleteAll();
		OBJECT_FACTORY->DestroyAllObjects();
	}

	bool LevelSelect::GoLevel(Button& b, GameLevels level, const std::string sound)
	{
		if (b.IfButtonClickedTurnSound(mouse_x, mouse_y, sound))
		{
			Close();
			STATEMANAGER->ChangeLevel(level);
			return true;
		}
		return false;
	}

	void LevelSelect::ClickEvent()
	{
		if (GoLevel(button.at(0), LV_MAINMENU))
			return;
		if (GoLevel(button.at(1), LV_TUTORIAL1))
			return;
		if (play_once[1] == true)
		{
			if (GoLevel(button.at(2), LV_1))
				return;
		}
		if (play_once[2] == true)
		{
			if (GoLevel(button.at(3), LV_2))
				return;
		}
		if (play_once[3] == true)
		{
			if (GoLevel(button.at(4), LV_3))
				return;
		}
		if (play_once[4] == true)
		{
			if (GoLevel(button.at(5), LV_4))
				return;
		}
		if (play_once[5] == true)
		{
			if (GoLevel(button.at(6), LV_5))
				return;
		}
		if (play_once[6] == true)
		{
			if (GoLevel(button.at(7), LV_6))
				return;
		}
		if (play_once[7] == true)
		{
			if (GoLevel(button.at(8), LV_7))
				return;
		}
		if (play_once[8] == true)
		{
			if (GoLevel(button.at(9), LV_8))
				return;
		}
		if (play_once[9] == true)
		{
			if (GoLevel(button.at(10), LV_9))
				return;
		}
		if (play_once[10] == true)
		{
			if (GoLevel(button.at(11), LV_10))
				return;
		}
		if (play_once[11] == true)
		{
			if (GoLevel(button.at(12), LV_11))
				return;
		}

	}

	void LevelSelect::HoverEvent()
	{
		static constexpr float z = 300.f;

		bool is_hovered_ = false;
		for (int i = 0; i < 13; i++)
		{
			if (button.at(i).SetZifMouseHover(mouse_x, mouse_y, z, i))
			{
				is_hovered_ = true;
				break;
			}
		}

		if (is_hovered_)
			(wall->sprite)->SetColor({ 0, 0, 0, 100 });
		else
			(wall->sprite)->SetColor({ 255, 255, 255, 0 });

	}

	int LevelSelect::FindLockedLevelNum() const
	{
		int index;
		for (index = 0; index < 12; index++)
		{
			if (!play_once[index])
				break;
		}
		return index;
	}

	void LevelSelect::UnlockNextLevel()
	{
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_PAGEUP))
		{
			const int index = FindLockedLevelNum();

			if (index < 12 && index > 0)
			{
				play_once[index] = true;
				goingnext[index - 1] = true;
			}
		}
	}


	void LevelSelect::UpdatePlayer()
	{
		static bool finish = false;
		if (first && !finish && player)
		{
			time = Timer::GetInstance().GetTime() - start_time;

			const float x = 50 * sin(time);
			player->transform->SetPositionX(x - 460.f);

			const float y = player->transform->GetTranslation().y;

			if (y < -60.f)
				finish = true;

			constexpr float speed = 3.f;
			player->transform->SetPositionY(-speed + y);
		}
	}

	void LevelSelect::OpenAllLevels()
	{
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_HOME))
		{
			for (int i = 0; i < 12; i++)
			{
				play_once[i] = true;
				goingnext[i - 1] = true;
			}
		}
	}


	void LevelSelect::MakeObject(Object*& object, glm::vec2 size, glm::vec3 pos, const std::string& texture, const std::string& name)
	{
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName(name);
		object->AddComponent(new Transform());
		object->AddComponent(new Sprite());
		object->Init();
		(object->transform)->SetScale(size);
		(object->transform)->SetTranslation(pos);
		(object->sprite)->SetTexture(texture);
		GRAPHICS->AddSprite(object->sprite);
	}
}