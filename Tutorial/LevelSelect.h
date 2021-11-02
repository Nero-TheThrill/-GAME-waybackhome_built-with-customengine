/*
*  File Name : LevelSelect.h
*  Primary Author : Choi Jinwoo
*  Secondary Author : Jina Hyun, Jinwon Park
*  Brief: level select screen
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelSystem.h"
#include "Object.h"
#include "Button.h"
namespace BLUE
{
    class LevelSelect : public LevelSystem
    {
    public:
        LevelSelect() {}
        void Init() override;
        void Update() override;
        void Close() override;
        ~LevelSelect() {}
    private:
		void UpdatePlayer();
		bool GoLevel(Button &button, GameLevels level, const std::string sound = "click_mouse");
		void ClickEvent();
		void HoverEvent();
		int FindLockedLevelNum() const;
		void UnlockNextLevel();
		void OpenAllLevels();
		void MakeObject(Object *&object, glm::vec2 size, glm::vec3 pos, const std::string & texture, const std::string & name);

		bool is_hovered;
        Object* background;
		Object* x_1;
		Object* x_2;
		Object* x_3;
		Object* x_4;
		Object* x_5;
		Object* x_6;
		Object* x_7;
		Object* x_8;
		Object* x_9;
		Object* x_10;
		Object* x_11;
        int mouse_x = 0, mouse_y = 0;

		std::vector< Button> button;
        Object * wall;
		Object * player = nullptr;
		bool first = true;
		float start_time = 0.f, time = 0.f;
    };
}