/*
*  File Name : PauseScreen.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Class for pause screen.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "PauseScreen.h"
#include "ObjectFactory.h"
#include "Archiver.h"
#include "Audio.h"
#include "TexturePath.h"
#include "LevelHeaderCollection.h"
#include "PopupMessage.h"

namespace original_scale
{
	glm::vec2 volume_up;
	glm::vec2 volume_down;
	glm::vec2 full_screen;
	glm::vec2 exit;
	glm::vec2 level_select;
	glm::vec2 replay;
}

namespace BLUE
{
    extern PauseScreen* PAUSE_SCREEN = nullptr;
    PauseScreen::PauseScreen()
		: mouse_x(0),
		mouse_y(0),
		option(nullptr),
		volume_up(nullptr),
		volume_down(nullptr),
		audio_icon(nullptr),
		fullscreen(nullptr),
		check_box(nullptr),
		exit(nullptr),
		level_select(nullptr),
		background(nullptr),
		replay(nullptr),
		is_fullscreen(nullptr),
		is_in_game(false),
		is_paused(nullptr),
		go_level_select(false),
		is_replay(false),
		pop_type(None)
	{
    }

    PauseScreen::~PauseScreen()
    {
    }

    void PauseScreen::Pause(bool* ispaused, bool isingame)
    {
        is_paused = ispaused;
        is_in_game = isingame;
		go_level_select = false;
        *ispaused = true;
        Init();
    }

    void PauseScreen::Resume(bool* ispaused)
    {
		go_level_select = false;
        *ispaused = false;
        Quit();
    }

	void PauseScreen::Init()
	{
		MakeObject(option, { 0, 0, 500 }, { 500, 649 }, Picture::Option, "option");

		original_scale::volume_up = { 75, 75 };
		MakeObject(volume_up, { 150, 0, 600 }, original_scale::volume_up, Picture::Button_Arrow_Right, "volume_up");

		original_scale::volume_down = { 75, 75 };
		MakeObject(volume_down, { -150, 0, 600 }, original_scale::volume_down, Picture::Button_Arrow_Left, "volume_down");

		MakeObject(audio_icon, { 0, 0, 600 }, { 100, 100 }, Picture::Icon_Audio, "audio");

		original_scale::full_screen = { 200, 50 };
		MakeObject(fullscreen, { 0, -200, 600 }, original_scale::full_screen, Picture::Button_FullScreen, "fullscreen");

    	MakeObject(background, { 0, 0, -500 }, { 1280, 720 }, Picture::Count, "background");
		background->sprite->SetTexture("texture/etc/Background_Option.png");
		
    	MakeObject(check_box, { -150, -200, 600 }, { 50, 50 }, Picture::Count, "check_box");

    	if (*is_fullscreen)
			check_box->sprite->SetTexture(T(Picture::CheckBox_True));
        else
			check_box->sprite->SetTexture(T(Picture::CheckBox_False));
		
        if (is_in_game)
        {
			volume_up->transform->SetPositionY(40.f);
			volume_down->transform->SetPositionY(40.f);
			audio_icon->transform->SetPositionY(40.f);

			background->transform->SetScale({ 475, 200 });
			background->transform->SetTranslation({0, -320, 981});
			background->sprite->SetTexture(T(Picture::Effect_Fade));
			background->sprite->SetColor({ 255, 255, 255, 0 });

			original_scale::exit = { 50, 50 };
			MakeObject(exit, { 200,270,601 }, { 50, 50 }, Picture::Button_X, "exit");

			original_scale::level_select = { 100, 100 };
        	MakeObject(level_select, { -100, -100, 601 }, { 100, 100 }, Picture::Icon_LevelSelect, "level_select");
			
			original_scale::replay = { 100, 100 };
        	MakeObject(replay, { 100, -100, 601 }, { 100, 100 }, Picture::Icon_Replay, "replay");
        }

		go_level_select = false;
		is_replay = false;
		pop_type = None;
    }

    void PauseScreen::Update()
    {
		mouse_x = WINDOW_INFORMATION::GetMousePos().x;
		mouse_y = WINDOW_INFORMATION::GetMousePos().y;

		if (!POPUPMESSAGE->isExist())
		{
			if (ChangeColorIfClicked(volume_up, Volume_up,{ 255, 255, 255, 100 }))
				AUDIO_MANAGER->volumeUp();
			if (ChangeColorIfClicked(volume_down, Volume_down, { 255, 255, 255, 100 }))
				AUDIO_MANAGER->volumeDown();			   
	        if (IsObjectClicked(check_box, Count, false) || IsObjectClicked(fullscreen, Full_Screen))
	            ToggleFullScreen();

	        if (is_in_game)
	        {
				if (IsObjectClicked(exit, Exit))
				{
					*is_paused = false;
					Quit();
				}

				if (IsObjectClicked(level_select, Level_Select))
				{
					background->sprite->SetColor({ 0, 0, 0, 100 });

					POPUPMESSAGE->Init();
					pop_type = LevelSelect_Button;
				}

				if (IsObjectClicked(replay, Replay))
				{
					background->sprite->SetColor({ 0, 0, 0, 100 });

					POPUPMESSAGE->Init();
					pop_type = Replay_Button;
				}
				else
					is_replay = false;

	        }

		}
		else if(is_in_game)
		{
			bool yes;
			if (POPUPMESSAGE->IsClicked(mouse_x, mouse_y, yes))
			{

				if (yes)
				{
					if (pop_type == LevelSelect_Button)
					{
						*is_paused = false;
						Quit();
						Close();
					}
					else if (pop_type == Replay_Button)
					{
						is_replay = true;
						Quit();
						Close();
					}

					pop_type = None;
				}
				else
				{
					POPUPMESSAGE->Delete();
					background->sprite->SetColor({ 255, 255, 255, 0 });
				}
			}

			if(Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE))
				background->sprite->SetColor({ 255, 255, 255, 0 });
		}
    }

    void PauseScreen::ToggleFullScreen()
    {
        if (*is_fullscreen)
            *is_fullscreen = false;
        else
            *is_fullscreen = true;

		if (*is_fullscreen)
		{
			check_box->sprite->SetTexture(T(Picture::CheckBox_True));
		}
		else
		{
			check_box->sprite->SetTexture(T(Picture::CheckBox_False));
		}

		GRAPHICS->is_toggled_fullscreen = true;
    }

    bool PauseScreen::GetFullScreen() const
    {
		return *is_fullscreen;
    }

	bool PauseScreen::GetReplay() const
	{
		return is_replay;
	}

	void PauseScreen::SetFullScreen(bool *fullscreen_)
    {
        is_fullscreen = fullscreen_;

		if(check_box && check_box->sprite)
		{
			if (*is_fullscreen)
				check_box->sprite->SetTexture(T(Picture::CheckBox_True));
			else
				check_box->sprite->SetTexture(T(Picture::CheckBox_False));
		}

		GRAPHICS->is_toggled_fullscreen = true;
    }

    bool PauseScreen::GoLevelSelect() const
    {
		return go_level_select;
    }

	glm::vec2 PauseScreen::GetObjectSize(type t) const
	{
		switch (t)
		{
		case Volume_up: return original_scale::volume_up;
		case Volume_down: return original_scale::volume_down;
		case Full_Screen: return original_scale::full_screen;
		case Exit: return original_scale::exit;
		case Level_Select: return original_scale::level_select;
		case Replay: return original_scale::replay;
		default: return {50, 50};
		}
	}

	bool PauseScreen::IsCollideWithMouse(Object* object, type t, bool scale_size)
    {
		const glm::vec3 position = object->transform->GetTranslation();
		const glm::vec2 size = object->transform->GetScale();

		const float min_x = position.x - size.x / 2.f;
		if (mouse_x < min_x)
		{
			object->transform->SetScale(GetObjectSize(t));
			return false;
		}

		const float max_x = position.x + size.x / 2.f;
		if(max_x < mouse_x)
		{
			object->transform->SetScale(GetObjectSize(t));
			return false;
		}

		const float min_y = position.y - size.y / 2.f;
		if(mouse_y < min_y)
		{
			object->transform->SetScale(GetObjectSize(t));
			return false;
		}

		const float  max_y = position.y + size.y / 2.f;
		if(max_y < mouse_y)
		{
			object->transform->SetScale(GetObjectSize(t));
			return false;
		}

		if (scale_size)
		{
			constexpr glm::vec2 plus_size = { 10, 10 };
			object->transform->SetScale(GetObjectSize(t) + plus_size);
		}
		return true;
    }

    bool PauseScreen::IsObjectClicked(Object* object, type t, bool scale_size)
    {
		if (IsCollideWithMouse(object, t, scale_size) && Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
			return true;
		else
			return false;
    }

    bool PauseScreen::ChangeColorIfClicked(Object* object, type t, Color change, Color original)
    {
		if (IsObjectClicked(object, t))
		{
			object->sprite->SetColor(change);
			return true;
		}
		else
		{
			object->sprite->SetColor(original);
			return false;
		}
    }

    void PauseScreen::Close()
    {
		go_level_select = true;
    }

    void PauseScreen::MakeObject(Object *& object, glm::vec3 position, glm::vec2 size, Picture p, const std::string &name)
    {
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName(name);
		object->AddComponent(new Transform());
		object->AddComponent(new Sprite());
		object->Init();

		if(p != Picture::Count)
			object->sprite->SetTexture(T(p));
		object->sprite->isHud = true;
		object->transform->SetScale(size);
		object->transform->SetTranslation(position);
		GRAPHICS->AddSprite(object->sprite);
    }

    void PauseScreen::Quit()
    {
		GRAPHICS->DeleteSprite(option->sprite);
        OBJECT_FACTORY->Destroy(option);

		GRAPHICS->DeleteSprite(audio_icon->sprite);
        OBJECT_FACTORY->Destroy(audio_icon);

		GRAPHICS->DeleteSprite(volume_up->sprite);
        OBJECT_FACTORY->Destroy(volume_up);

		GRAPHICS->DeleteSprite(volume_down->sprite);
        OBJECT_FACTORY->Destroy(volume_down);

		GRAPHICS->DeleteSprite(fullscreen->sprite);
        OBJECT_FACTORY->Destroy(fullscreen);

		GRAPHICS->DeleteSprite(check_box->sprite);
        OBJECT_FACTORY->Destroy(check_box);

		OBJECT_FACTORY->Destroy(background);
		GRAPHICS->DeleteSprite(background->sprite);

        if (is_in_game)
        {
			GRAPHICS->DeleteSprite(exit->sprite);
            OBJECT_FACTORY->Destroy(exit);

			GRAPHICS->DeleteSprite(level_select->sprite);
            OBJECT_FACTORY->Destroy(level_select);
        

			GRAPHICS->DeleteSprite(replay->sprite);
			OBJECT_FACTORY->Destroy(replay);
        }
    }
}
