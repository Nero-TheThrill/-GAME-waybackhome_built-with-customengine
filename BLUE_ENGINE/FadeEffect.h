/*
*  File Name : FadeEffect.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:	Camera Effect(Fade In/Out)
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#pragma once
#include "Transform.hpp"

namespace BLUE
{
    struct FadeEffect
    {
        FadeEffect();
        void FadeEffectTurnOn(bool turn_on = true, bool fade_in = false, int effect_duration = 100);
        void Update();
		void Delete();
		bool is_effect_finished;
    private:
        void EffectOn(bool fade_in);
        void InitImage(bool fade_in = false, int time = 100);

        bool doeffect;
        bool fadein;
        bool fadeout;

        int duration;
        float intensity;

		float current_alpha;
		int time;
        Object * image;
    };
}