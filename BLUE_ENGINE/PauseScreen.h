/*
*  File Name : PauseScreen.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Hyun Jina
*  Brief: Class for pause screen.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"
#include "Input.h"
#include "LevelSelect.h"

namespace BLUE
{
	enum class Picture;

	class PauseScreen
    {
    public:
        PauseScreen();
        ~PauseScreen();

        void Pause(bool* ispaused, bool isingame);
        void Resume(bool* ispaused);
        void Update();
        void ToggleFullScreen();
		bool GetFullScreen() const;
		bool GetReplay() const;
        void SetFullScreen(bool *fullscreen);
		bool GoLevelSelect() const;
    private:
		enum type
		{
			Volume_up,
			Volume_down,
			Full_Screen,
			Exit,
			Level_Select,
			Replay,
			Count
		};

		enum PopUpType
		{
			LevelSelect_Button,
			Replay_Button,
			None
		};

		glm::vec2 GetObjectSize(type t) const;

		bool IsCollideWithMouse(Object * object, type t, bool scale_size = true);
		bool IsObjectClicked(Object * object, type t, bool scale_size = true);
		bool ChangeColorIfClicked(Object * object, type t, Color change, Color original = Color{255, 255, 255, 255});

		void Close();
		void MakeObject(Object *&object, glm::vec3 position, glm::vec2 size, Picture p, const std::string &name = "object");

        void Init();
        void Quit();

        int mouse_x, mouse_y;
		Object* option, *volume_up, *volume_down, *audio_icon, *fullscreen, *check_box, *exit, *level_select, *background, *replay;
        bool* is_fullscreen;
        bool is_in_game;
		bool* is_paused;
		bool go_level_select;
		bool is_replay;

		PopUpType pop_type;
    };
    extern PauseScreen* PAUSE_SCREEN;
}


