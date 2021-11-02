/*
*  File Name : Resolution.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Functions for resolution

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include <glm/glm.hpp>
#include <string>

namespace BLUE
{
	enum class Screen_Resolution
	{
		R_1920X1080,
		R_1680X1050,
		R_1600X900,
		R_1280X720,
		R_800X600,
		Count
	};

	glm::vec2 to_vector(Screen_Resolution resolution);
	std::string to_string(Screen_Resolution resolution);
	Screen_Resolution to_screen_resolution(const std::string& resolution);

	struct Resolution
	{
	public:
		Resolution();
		glm::vec2 GetChangeRatio() const;
		void SetResolution(Screen_Resolution resolution);
		float GetAspectRatio() const;
		Screen_Resolution GetCurrentResolution() const;

	private:
		Screen_Resolution curr;
		Screen_Resolution prev;
	};
	extern Resolution * RESOLUTION;
}
