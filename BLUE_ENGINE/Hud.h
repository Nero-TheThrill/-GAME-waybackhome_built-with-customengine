/*
*  File Name : Hud.h
*  Primary Author : Hyun Jina
*  Secondary Author : 
*  Brief: save the information of hud.
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <glm/glm.hpp>

namespace BLUE
{
	struct HUD
	{
		bool initialized = false;
		glm::vec2 previous_resolution = { 1280, 720 };
		glm::vec2 current_resolution = previous_resolution;
		glm::vec2 ratio = { 1.f, 1.f };
	};
}