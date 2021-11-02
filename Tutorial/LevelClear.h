/*
*  File Name : LevelClear.h
*  Primary Author : Hyun Jina
*  Secondary Author : 
*  Brief: Clear name
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelSystem.h"
#include "Button.h"

namespace BLUE
{
	enum class Picture;

	class LevelClear : public LevelSystem
    {
    public:
		LevelClear();
        void Init() override;
        void Update() override;
        void Close() override;
        ~LevelClear();
    private:
		void MakeObject(Object*& object, glm::vec2 size, glm::vec3 position, Picture picture, const std::string & name);

		int mouse_x, mouse_y;
		float start_time, time;

		glm::vec2 plus_size;

		Object * background, *birds, *ship, *light, *ribbon, *text, *player;
		Transform *ship_t, *birds_t, *player_t;
    };
}
