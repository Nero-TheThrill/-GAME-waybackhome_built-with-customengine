/*
*  File Name : Resolution.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Functions for resolution

*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include <SDL.h>
#include <GL/glew.h>
#include "Resolution.h"
#include "Graphics.h"

namespace BLUE
{
	Resolution * RESOLUTION = nullptr;

	constexpr unsigned int HashCode(const char* str)
	{
		return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
	}

	glm::vec2 to_vector(Screen_Resolution resolution)
	{
		switch(resolution)
		{
		case Screen_Resolution::R_1920X1080:
			return { 1920.f, 1080.f };
		case Screen_Resolution::R_1680X1050:
			return { 1680.f, 1050.f };
		case Screen_Resolution::R_1600X900:
			return { 1600.f, 900.f };
		case Screen_Resolution::R_1280X720:
			return { 1280.f, 720.f };
		case Screen_Resolution::R_800X600:
			return { 800.f, 600.f };
		default:
			return { 1280.f, 720.f };
		}
	}

	std::string to_string(Screen_Resolution resolution)
	{
		switch (resolution)
		{
		case Screen_Resolution::R_1920X1080:
			return "R_1920X1080";
		case Screen_Resolution::R_1680X1050:
			return "R_1680X1050";
		case Screen_Resolution::R_1600X900:
			return "R_1600X900";
		case Screen_Resolution::R_1280X720:
			return "R_1280X720";
		case Screen_Resolution::R_800X600:
			return "R_800X600";
		default:
			return "R_1280X720";
		}
	}

	Screen_Resolution to_screen_resolution(const std::string& resolution)
	{
		switch (HashCode(resolution.c_str()))
		{
		case HashCode("R_1920X1080"):
			return Screen_Resolution::R_1920X1080;
		case HashCode("R_1680X1050"):
			return  Screen_Resolution::R_1680X1050;
		case HashCode("R_1600X900"):
			return Screen_Resolution::R_1600X900;
		case HashCode("R_1280X720"):
			return Screen_Resolution::R_1280X720;
		case HashCode("R_800X600"):
			return Screen_Resolution::R_800X600;
		default:
			return Screen_Resolution::R_1280X720;
		}
	}

	Resolution::Resolution() : curr(Screen_Resolution::R_1280X720), prev(curr)
	{
		RESOLUTION = this;
	}

	glm::vec2 Resolution::GetChangeRatio() const
	{
		return to_vector(curr) / to_vector(prev);
	}

	void Resolution::SetResolution(Screen_Resolution resolution)
	{
		prev = curr;
		curr = resolution;

		const glm::ivec2 size = to_vector(curr);

		SDL_SetWindowSize(SDL_GL_GetCurrentWindow(), size.x, size.y);
		glViewport(0, 0, size.x, size.y);
		GRAPHICS->SetWindowSize(size);
	}

	float Resolution::GetAspectRatio() const
	{
		const glm::vec2 resolution = to_vector(curr);
		return resolution.x / resolution.y;
	}

	Screen_Resolution Resolution::GetCurrentResolution() const
	{
		return curr;
	}
}
