/*
*  File Name : Credit.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: to show developers.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelSystem.h"
#include "Object.h"
#include "Button.h"
#include "Camera.h"

namespace BLUE
{
	enum class Picture;

	class Credit : public LevelSystem
	{
	public:
		Credit();
		void Init() override;
		void Update() override;
		void Close() override;
		~Credit();
	private:
		Camera * camera;
		void MakeObject(Object *& object, glm::vec2 size, glm::vec3 position, Picture picture, const std::string & name);
		Object * background;

		Transform* credit_transform;
		Button main_menu;
		int mouse_x, mouse_y;
	};
}

