/*
*  File Name : SmokeEffects.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Make smoke effects when the object's state is changed.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#pragma once
#include "Object.h"

namespace BLUE
{
    namespace Smoke
    {
        static constexpr float remain_time = 1.0f;
    }

    class SmokeEffect
    {
    public:
        SmokeEffect();
        ~SmokeEffect();

        void Spawn(glm::vec3 position = { 0.0f, 0.0f, 0.0f }, glm::vec2 scale = { 100.0f, 100.0f });
        void Destroy();
        void Update();
		void DestroyAll();
    private:
        std::vector <Object*> objects;
        std::vector <Sprite*> sprites;
    };

    extern SmokeEffect* SMOKE_EFFECT;
}
