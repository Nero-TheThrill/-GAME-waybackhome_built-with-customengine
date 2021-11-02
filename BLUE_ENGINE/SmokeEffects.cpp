/*
*  File Name : SmokeEffects.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Make smoke effects when the object's state is changed.
*  
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/

#include "SmokeEffects.h"
#include "ObjectFactory.h"
#include "Graphics.h"
#include "TexturePath.h"

namespace BLUE
{
    SmokeEffect* SMOKE_EFFECT = nullptr;

    SmokeEffect::SmokeEffect()
    {
    }

    SmokeEffect::~SmokeEffect()
    {
    }

    void SmokeEffect::Spawn(glm::vec3 position, glm::vec2 scale)
    {
        Object * object = nullptr;
        object = OBJECT_FACTORY->CreateEmptyObject();
        object->AddComponent(new Transform());
        object->AddComponent(new Sprite());
        object->Init();
        objects.push_back(object);

        Sprite * sprite = nullptr;
        sprite = dynamic_cast<Sprite*>(object->GetComponent(ComponentType_SPRITE));
        sprite->SetTexture(T(Picture::Effect_Smoke));
        sprite->SetAnimation()->SetFrame(10);
        sprite->SetAnimation()->SetSpeed(50.0f);
        sprite->SetAnimation()->ActivateAnimation();
        sprites.push_back(sprite);

        Transform * transform = dynamic_cast<Transform*>(object->GetComponent(ComponentType_TRANSFORM));
        transform->SetTranslation({ position.x, position.y, position.z + 2.0f });
        transform->SetScale(scale * 1.5f);
    }

    void SmokeEffect::Destroy()
    {
        GRAPHICS->DeleteSprite(sprites.front());
        OBJECT_FACTORY->Destroy(objects.front());
        objects.erase(objects.begin());
        sprites.erase(sprites.begin());
    }

    void SmokeEffect::Update()
    {
        if (!objects.empty())
        {
            static float time = 0.0f;
            time += sprites.front()->SetAnimation()->GetTimer();
            if (time > Smoke::remain_time)
            {
                time = 0.0f;
                Destroy();
            }
        }

    }

    void SmokeEffect::DestroyAll()
	{
		int size = static_cast<int>(sprites.size());
		for (int i = 0; i<size; i++)
		{
			GRAPHICS->DeleteSprite(sprites.front());
			OBJECT_FACTORY->Destroy(objects.front());
			objects.erase(objects.begin());
			sprites.erase(sprites.begin());
		}
    }
}
