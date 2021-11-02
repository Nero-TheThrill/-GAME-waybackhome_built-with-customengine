/*
*  File Name : LevelUpdateCollection.cpp
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jina Hyun
*  Brief: level update functions
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "LevelUpdateCollection.h"
#include <thread>
#include "PopupMessage.h"

namespace BLUE
{
	bool play_once[12] = { true, false, false, false, false, false, false, false, false, false, false, false };
	bool goingnext[11] = { false, false, false, false, false,false, false, false, false, false,false };

    static unsigned int dt = 0;

    void LevelCollection::MakeObject(Object*& object, glm::vec2 size, glm::vec3 position, Picture picture, bool is_hud, const std::string& name)
    {
		object = OBJECT_FACTORY->CreateEmptyObject();
		object->SetName(name);
		object->AddComponent(new Transform());
		object->AddComponent(new Sprite());
		object->Init();

		object->transform->SetScale(size);
		object->transform->SetTranslation(position);
		object->sprite->SetTexture(T(picture));
		if (is_hud)
			object->sprite->isHud = true;
		GRAPHICS->AddSprite(object->sprite);
    }

    void LevelCollection::InitDialogue()
    {
		switch (levelinfo)
		{
		case LV_TUTORIAL1:
			DIALOGUE->Init(dialogue_name::dialogue_1);
			break;
		case LV_TUTORIAL2:
			DIALOGUE->Init(dialogue_name::d2);
			break;
		case LV_TUTORIAL3:
			DIALOGUE->Init(dialogue_name::d3);
			break;
		case LV_TUTORIAL4:
			DIALOGUE->Init(dialogue_name::d4);
			break;
		case LV_2:
			DIALOGUE->Init(dialogue_name::d5);
			break;
		case LV_1:
			DIALOGUE->Init(dialogue_name::d6);
			break;
		}
    }

	void LevelCollection::InitBubble()
	{
		MakeObject(bubble, { 200, 200 }, { 0, 0, 300 }, Picture::Effect_Fade, false, "bubble");

		is_bubble_exist = true;
		iven_used_at_least_once = false;

		switch (levelinfo)
		{
		case LV_TUTORIAL1:
			bubble->sprite->SetColor({ 255, 255, 255, 255 });
			bubble->sprite->SetTexture(T(Picture::Bubble_WASD));

			MakeObject(x, { 264, 164 }, { -480, 255, 810 }, Picture::Button_X, true, "button_x");
			break;
		case LV_TUTORIAL2:
			bubble->sprite->SetColor({ 255, 255, 255, 255 });
			bubble->sprite->SetTexture(T(Picture::Bubble_Mouse_Left));

			MakeObject(x, { 264, 164 }, { -480, 255, 810 }, Picture::Button_X, true, "button_x");
			break;
		case LV_TUTORIAL3:
			bubble->sprite->SetColor({ 255, 255, 255, 255 });
			bubble->sprite->SetTexture(T(Picture::Bubble_Mouse_Wheel));
			break;
		default:
			bubble->sprite->SetColor({ 255, 255, 255, 0 });
			is_bubble_exist = false;
			break;
		}
	}

	void LevelCollection::UpdateBubble()
	{
		if(is_bubble_exist && player)
		{
			constexpr float plus= 150.f;
			const glm::vec3 player_pos = player->transform->GetTranslation();

			bubble->transform->SetPositionX(player_pos.x);
			bubble->transform->SetPositionY(player_pos.y + plus);

			switch (levelinfo)
			{
			case LV_TUTORIAL1:
			{
				if (320.f < player_pos.x && player_pos.x < 330.f)
					bubble->sprite->SetTexture(T(Picture::Bubble_WASD));
				if (330.f < player_pos.x && player_pos.x < 340.f)
					bubble->sprite->SetTexture(T(Picture::Bubble_F));

				if (!PLAYER_CONTROLLER->CanUsingInventory)
					bubble->sprite->SetColor({ 255, 255, 255, 0 });
			}
			break;
			case LV_TUTORIAL2:
			{
				const bool can_use_iven = PLAYER_CONTROLLER->CanUsingInventory;

				if (iven_used_at_least_once && can_use_iven)
					bubble->sprite->SetColor({ 255, 255, 255, 0 });

				if (!iven_used_at_least_once && !can_use_iven)
				{
					bubble->sprite->SetColor({ 255, 255, 255, 150 });
					iven_used_at_least_once = true;
				}
			}
			break;
			}
		}
	}

	LevelCollection::LevelCollection():
		IsFuture(true),
		is_future_gun(true),
		camera(nullptr),
		player(nullptr),
		hud(nullptr),
		arrow(nullptr),
		background(nullptr),
		bubble(nullptr),
		x(nullptr),
		JSONWRITER(nullptr),
		JSONREADER(nullptr),
		IsPaused(false),
		ReplayOn(false),
		is_restarted(false),
		is_bubble_exist(false),
		iven_used_at_least_once(false),
		imgod(false),
		mouse_x(0),
		mouse_y(0)
    {
		option.Delete();
    }

    LevelCollection::~LevelCollection()
    {
		option.Delete();
		fade_effect.Delete();
		DIALOGUE->DeleteObject();
		SMOKE_EFFECT->Destroy();
		delete JSONWRITER;
		delete JSONREADER;

		camera = nullptr;
		player = nullptr;
		hud = nullptr;
		arrow = nullptr;
		background = nullptr;
		bubble = nullptr;
		x = nullptr;
		JSONWRITER = nullptr;
		JSONREADER = nullptr;

		GRAPHICS->DeleteAll();
		OBJECT_FACTORY->DestroyAllObjects();
    }

    void LevelCollection::InitLEVEL(std::string levelTXT, GameLevels linfo)
    {
        levelinfo = linfo;
        CURSOR_CONTROLLER->Init();
        JSONREADER = new rapidjson::JSONreader(ReadFromFile(levelTXT).c_str());
        AUDIO_MANAGER->PlaySound("BGM");
        JSONREADER->InitializeObject();
        
        player = PLAYER_CONTROLLER->Spawn();
		PLAYER_CONTROLLER->isClearTheGame = false;
		ghost_.Spawn(0, 0, 0);

		MakeObject(background, { 3000, 3000 }, { 0, 0, -999 }, Picture::Background_InGame, false, "background");
		MakeObject(hud, { 1280, 720 }, { 0, 0, 800 }, Picture::Hud, true, "hud");
    	MakeObject(arrow, { 179, 86 }, { -480, 255, 805 }, Picture::Hud_BulletState_Future, true,"bullet_state");
		
		option.Delete();
		option.Init({ 585, 305, 805 }, { 92, 94 }, T(Picture::Icon_Option));
		option.SetHud(true);

		replay.Delete();
		replay.Init({ 490, 315, 805 }, { 70,68 }, T(Picture::Icon_Replay_InGame));
		replay.SetHud(true);

    	is_future_gun = true;
		imgod = false;

		camera = GRAPHICS->GetCamera();
		camera->SetPosition({ 0, 0 });
    	lerp.Init(camera, player->transform);
		InitDialogue();
		InitBubble();

		if(!is_restarted)
			fade_effect.FadeEffectTurnOn(true, false, 60);    	
    	dt = 0;
    }

    void LevelCollection::CloseLEVEL(std::string levelTXT)
    {
		SMOKE_EFFECT->DestroyAll();
		option.Delete();
		replay.Delete();
        fade_effect.Delete();
        PLAYER_CONTROLLER->CanUsingInventory = true;
        DIALOGUE->DeleteObject();
		POPUPMESSAGE->Delete();
        AUDIO_MANAGER->StopSound();
		is_restarted = false;

#ifdef DEBUG
        JSONWRITER = new rapidjson::JSONwriter();
        JSONWRITER->ClearFile(levelTXT);
        delete JSONWRITER;
#endif

        POISONPLANT_MANAGER->Reset();
        OBJECT_CONTROLLER->Reset(levelTXT);
        FUTUREBULLET_CONTROLLER->Reset();
        PASTBULLET_CONTROLLER->Reset();
        POISONBULLET_CONTROLLER->Reset();
        GRAPHICS->DeleteAll();
        OBJECT_FACTORY->DestroyAllObjects();
        delete JSONREADER;

		camera = nullptr;
		player = nullptr;
		hud = nullptr;
		arrow = nullptr;
		background = nullptr;
		bubble = nullptr;
		JSONWRITER = nullptr;
		JSONREADER = nullptr;
		IsPaused = false;
		ReplayOn = false;
		mouse_x = 0;
		mouse_y = 0;

		imgod = false;
    }

    void LevelCollection::UpdateLEVEL(std::string levelTXT, GameLevels nextLevel)
    {
		mouse_x = static_cast<int>(WINDOW_INFORMATION::GetMousePos().x);
		mouse_y = static_cast<int>(WINDOW_INFORMATION::GetMousePos().y);

        if (!is_restarted && !fade_effect.is_effect_finished)
            fade_effect.Update();
        
    	if (dt < 30)
            dt++;
        else
            lerp.Update();

		if (!IsPaused)
		{
			// if there is a pop up message box
			if (POPUPMESSAGE->isExist())
			{
				bool yes;
				if (POPUPMESSAGE->IsClicked(mouse_x, mouse_y, yes))
				{
					// if yes button clicked.
					if (yes)
					{
		/*------------------------------Replay-------------------------------*/
						is_restarted = true;
						PLAYER_CONTROLLER->SetInventoryState(true);
						mousecontroller.resetPickState();
						POPUPMESSAGE->Delete();
						CloseLEVEL(levelTXT);
						InitLEVEL(levelTXT, levelinfo);
						return;
					}
					// if no button clicked.
					else
						POPUPMESSAGE->Delete();
				}
			}
			else
			{
				// if replay button is clicked, Make pop up box
				if (replay.IsButtonClicked(mouse_x, mouse_y))
					POPUPMESSAGE->Init();

				// Update to run the game
				Playing(levelTXT, nextLevel);
				UpdateBubble();
			}
        }
        else
        {
            if ((Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE) && !POPUPMESSAGE->isExist()) ||				
				option.IsButtonClicked(mouse_x, mouse_y))
            {
                PLAYER_CONTROLLER->reset();
                PAUSE_SCREEN->Resume(&IsPaused);
            }
            PAUSE_SCREEN->Update();

			if(PAUSE_SCREEN->GetReplay())
			{
				is_restarted = true;
				PLAYER_CONTROLLER->SetInventoryState(true);
				mousecontroller.resetPickState();
				CloseLEVEL(levelTXT);
				InitLEVEL(levelTXT, levelinfo);
				return;
			}

			if(PAUSE_SCREEN->GoLevelSelect())
			{
				CloseLEVEL(levelTXT);
				STATEMANAGER->ChangeLevel(LV_LEVELSELECT);
				return;
			}
        }
        CURSOR_CONTROLLER->Update();
    }


	void LevelCollection::Playing(std::string levelTXT, GameLevels nextLevel)
	{

		if (DIALOGUE->dialogue_on && fade_effect.is_effect_finished)
			DIALOGUE->Update();

		/*------------------------------Pause-------------------------------*/
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_ESCAPE)
			|| option.IsButtonClicked(mouse_x, mouse_y))
		{
			PAUSE_SCREEN->Pause(&IsPaused, true);
		}

		/*------------------------------Next Level---------------------------*/
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_PAGEUP))
		{
			CloseLEVEL(levelTXT);
			STATEMANAGER->ChangeLevel(nextLevel);
			return;
		}

		/*------------------------------Toggle God Mode-----------------------*/
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_PAGEDOWN))
		{
			imgod = !imgod;
			PLAYER_CONTROLLER->isDead = false;
		}

		/*------------------------------Clear---------------------------------*/
		if (PLAYER_CONTROLLER->isClearTheGame)
		{
			AUDIO_MANAGER->PlaySound("level_end");
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			play_once[level_data] = true;
			CloseLEVEL(levelTXT);
			if(nextLevel == LV_TUTORIAL2 || nextLevel == LV_TUTORIAL3 || nextLevel == LV_TUTORIAL4 || nextLevel == LV_CLEAR)
				STATEMANAGER->ChangeLevel(nextLevel);
			else
				STATEMANAGER->ChangeLevel(LV_LEVELSELECT);
			return;
		}

		/*------------------------------Die------------------------------------*/
		if (!imgod && PLAYER_CONTROLLER->isDead)
		{
			is_restarted = true;
			AUDIO_MANAGER->PlaySound("dead");
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			PLAYER_CONTROLLER->SetInventoryState(true);
			mousecontroller.resetPickState();
			PLAYER_CONTROLLER->isDead = false;
			CloseLEVEL(levelTXT);
			InitLEVEL(levelTXT, levelinfo);
			return;
		}

		/*------------------------------Using Item-------------------------------*/
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_F))
		{
			PLAYER_CONTROLLER->interaction();
			StoreInformation(INTERACT);
		}

    	UpdateFunctions();
	}


    void LevelCollection::MouseEvent()
    {
		/*------------------------------Picking----------------------------------*/
        if (Input::GetInstance().IsMousePressed(SDL_BUTTON_LEFT))
        {

            mousecontroller.picking();
			StoreInformation(MOUSERIGHTPRESSED);
        }

		/*------------------------------Shooting----------------------------------*/
        if (Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
        {
			if (!mousecontroller.GetPickState())
			{
				if (canUseGun){
					AUDIO_MANAGER->PlaySound("shootgun");

				if (is_future_gun)
					FUTUREBULLET_CONTROLLER->Init(*player);
				else
					PASTBULLET_CONTROLLER->Init(*player);

				StoreInformation(MOUSELEFTCLICK);
				}
				else
				{
					AUDIO_MANAGER->PlaySound("cannotshoot");
				}
            }
        }

		/*------------------------------Putting-------------------------------------*/
        if (Input::GetInstance().IsMouseReleased(SDL_BUTTON_LEFT))
        {
            mousecontroller.pick_done();
			StoreInformation(MOUSERIGHTUP);
        }

        mousecontroller.update(arrow->sprite, is_future_gun, IsFuture);
    }

    void LevelCollection::ChangeBulletState()
    {
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_1))
		{
			AUDIO_MANAGER->PlaySound("changebullet");
			is_future_gun = true;

			(arrow->sprite)->SetTexture(T(Picture::Hud_BulletState_Future));
		}
		if (Input::GetInstance().IsKeyTriggered(SDL_SCANCODE_2))
		{
			AUDIO_MANAGER->PlaySound("changebullet");
			is_future_gun = false;

			(arrow->sprite)->SetTexture(T(Picture::Hud_BulletState_Past));
		}
    }

    void LevelCollection::StoreInformation(InfoType info_type)
    {
		if (ReplayOn)
		{
			info.playerPos = PLAYER_CONTROLLER->GetTransform()->GetTranslation();
			info.mousePos = mousecontroller.getMousePos();
			info.playerRotate = PLAYER_CONTROLLER->GetTransform()->GetRotation();
			info.cameraPos = camera->GetPosition();
			info.IsGunFuture = is_future_gun;
			REPLAY_SYSTEM->storeInfo(info_type, info);
		}
    }

    void LevelCollection::UpdateFunctions()
    {
		ChangeBulletState();
		StoreInformation(MOVING);
		SMOKE_EFFECT->Update();
		FUTUREBULLET_CONTROLLER->Update();
		PASTBULLET_CONTROLLER->Update();
		POISONPLANT_MANAGER->Update();
		PLAYER_CONTROLLER->update();
		ghost_.update();
		MouseEvent();
    }

    void LevelCollection::SetReplayOn(bool shouldreplay)
    {
        ReplayOn = shouldreplay;
    }
}
