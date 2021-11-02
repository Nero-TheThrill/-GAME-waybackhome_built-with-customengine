/*
*  File Name : Button.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Class for button
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"
#include "StateManager.h"

namespace BLUE
{
	class Button
	{
	public:
		Button();
		~Button();

		void Init(glm::vec3 location, glm::vec2 scale, const std::string & texture_name = "");
		
		bool IsCollidingWithMouse(int mouse_x, int mouse_y) const;
		bool IsButtonClicked(int mouse_x, int mouse_y) const;

		bool IfButtonClickedTurnSound(int mouse_x, int mouse_y, const std::string & sound_name = "") const;
		
		void Delete();

		bool SetZifMouseHover(int mouse_x, int mouse_y, float z, int i);

		void IfMouseHoverScaleSize(bool turn_on);
		void SetPlusSize(glm::vec2 plus);

		void SetHud(bool on);
	private:
		void SetZ(float z);

		bool is_initialize;

		Object * button;
		
		glm::vec3 position;
		glm::vec2 size;
		glm::vec2 plus_size;

		bool if_mouse_hover_scale_size;
	};
}

