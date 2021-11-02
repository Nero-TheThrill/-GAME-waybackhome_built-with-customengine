/*
*  File Name : Splash.h
*  Primary Author : Park Jinwon
*  Secondary Author : Hyun Jina
*  Brief: Splash digipen logo.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "LevelSystem.h"
#include "Object.h"
#include "Input.h"

namespace BLUE
{
    class Splash : public LevelSystem
    {
    public:
        Splash() {}
        void Init() override;
        void Update() override;
        void Close() override;
        ~Splash() {}
    private:
        Object* splash;
		Object* text;
		Input input;

		Object * animation;

		Sprite *splash_sprite;

		bool is_all_textures_loaded;
		bool first = true;

		bool go_next_level;
		bool fmod;
		float time;
    };
}