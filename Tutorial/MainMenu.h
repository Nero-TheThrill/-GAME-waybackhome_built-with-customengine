/*
*  File Name : MainMenu.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: It contains game name, start button, option button, and end button.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelSystem.h"
#include "Camera.h"
#include "Object.h"
#include <glm/glm.hpp>

#include "Button.h"
namespace BLUE
{
	class MainMenu : public LevelSystem
	{
	public:
		MainMenu() {}
		void Init() override;
		void Update() override;
		void Close() override;
		~MainMenu() {}
	private:
		Object* background;
		int mouse_x = 0, mouse_y = 0;

		Button end_button;
		Button option_button;
		Button start_button;
	};
}
