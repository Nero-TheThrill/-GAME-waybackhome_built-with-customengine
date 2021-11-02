/*
*  File Name : FadeEffect.h
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief:	Camera Effect(Fade In/Out)
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/
#include "FadeEffect.h"
#include "ObjectFactory.h"
#include "Object.h"
#include "Graphics.h"
#include "TexturePath.h"
#include <iostream>

namespace BLUE
{
    FadeEffect::FadeEffect() :
		is_effect_finished(true),
		doeffect(false),
		fadein(false), 
		fadeout(false),
		duration(false),
		current_alpha(255.f),
		time(0),
		image(nullptr)
    {
    }

    void FadeEffect::InitImage(bool fade_in, int time_)
    {
        duration = time_;
        intensity = 255.0f / static_cast<float>(time_);
		time = 0;
        if (image == nullptr)
        {
            image = OBJECT_FACTORY->CreateEmptyObject();
            image->SetName("fade image");
            image->AddComponent(new Transform());
            image->AddComponent(new Sprite());
            image->Init();
            image->transform->SetTranslation({ 0, 0, Depth::range.y });
            (image->transform)->SetScale({ 2000, 1500 });
            (image->sprite)->SetTexture(T(Picture::Effect_Fade));
			image->sprite->isHud = true;
            GRAPHICS->AddSprite(image->sprite);
        }

        if (fade_in)
		{
			current_alpha = 0.f;
            image->sprite->SetColor({ 0, 0, 0, 0 });
		}
        else
        {
			current_alpha = 255.f;
			image->sprite->SetColor({ 0, 0, 0, 255 });
        }
    }

    void FadeEffect::EffectOn(bool fade_in)
    {
       // static float current_alpha = static_cast<float>(image->sprite->GetMesh().GetColor(0).alpha);

        if (time++ < duration)
        {
            if (fade_in)
            {
                if (current_alpha + intensity > 255.0f)
                    current_alpha = 255.0f;
                else
                    current_alpha += intensity;
            }
            else
            {
                if (current_alpha - intensity < 0.0f)
                    current_alpha = 0.0f;
                else
                    current_alpha -= intensity;
            }

            image->sprite->SetColor({ 0, 0, 0, static_cast<unsigned char>(current_alpha) });
        }
        else
        {
            time = 0;
            doeffect = false;

            if (!fade_in && image != nullptr)
            {
				Delete();
               // OBJECT_FACTORY->Destroy(image);
            }
			is_effect_finished = true;
        }
    }

    void FadeEffect::FadeEffectTurnOn(bool turn_on, bool fade_in, int effect_duration)
    {
        doeffect = turn_on;
		if (turn_on)
		{
			is_effect_finished = false;
			InitImage(fade_in, effect_duration);

			if (fade_in)
			{
				fadein = true;
				fadeout = false;
			}
			else
			{
				fadein = false;
				fadeout = true;
			}
		}
		else
		{
			is_effect_finished = true;
			time = 0;
		}
    }

    void FadeEffect::Update()
    {
	//	std::cout << time << std::endl;

        if (!doeffect)
            return;

        if (fadein)
            EffectOn(true);
        else
            EffectOn(false);

    }

    void FadeEffect::Delete()
    {
		doeffect = false;
		time = 0;
		is_effect_finished = true;
		if(image)
		{
			GRAPHICS->DeleteSprite(image->sprite);
			OBJECT_FACTORY->Destroy(image);
			image = nullptr;
		}
    }
}
