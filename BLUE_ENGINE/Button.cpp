/*
*  File Name : Button.cpp
*  Primary Author : Hyun Jina
*  Secondary Author :
*  Brief: Class for button
*
*  Copyright (C) 2019 DigiPen Institute of Technology.
*/


#include "Button.h"
#include "ObjectFactory.h"
#include "Graphics.h"
#include "Audio.h"
#include "LevelUpdateCollection.h"
namespace BLUE
{
	Button::Button() :
		is_initialize(false),
		button(nullptr),
		position(0.f, 0.f, 0.f),
		size(0.f, 0.f),
		plus_size(10.f, 10.f),
		if_mouse_hover_scale_size(true)
	{
	}

	Button::~Button()
	{
		Delete();
	}

	void Button::Init(glm::vec3 location, glm::vec2 scale, const std::string& texture_name)
	{
		if(!is_initialize || button == nullptr || button->sprite == nullptr || button->transform == nullptr)
		{
			button = OBJECT_FACTORY->CreateEmptyObject();
			button->SetName("Button");
			button->AddComponent(new Transform());
			button->AddComponent(new Sprite());
			button->Init();

			button->transform->SetTranslation(location);
			button->transform->SetScale(scale);

			position = location;
			size = scale;

			if(texture_name != "")
				button->sprite->SetTexture(texture_name);

			GRAPHICS->AddSprite(button->sprite);
			is_initialize = true;
		}
	}

	bool Button::IsCollidingWithMouse(int mouse_x, int mouse_y) const
	{
		if (!is_initialize)
			return false;

		const float x_min = position.x - size.x / 2.f;
		if (mouse_x < x_min)
		{
			if (if_mouse_hover_scale_size && button->transform->GetScale() != size)
				button->transform->SetScale(size);

			return false;
		}

		const float x_max = position.x + size.x / 2.f;
		if (x_max < mouse_x)
		{
			if (if_mouse_hover_scale_size && button->transform->GetScale() != size)
				button->transform->SetScale(size);

			return false;
		}

		const float y_min = position.y - size.y / 2.f;
		if (mouse_y < y_min)
		{
			if (if_mouse_hover_scale_size && button->transform->GetScale() != size)
				button->transform->SetScale(size);

			return false;
		}

		const float y_max = position.y + size.y / 2.f;
		if (y_max < mouse_y)
		{
			if (if_mouse_hover_scale_size && button->transform->GetScale() != size)
				button->transform->SetScale(size);

			return false;
		}

		if(if_mouse_hover_scale_size)
			button->transform->SetScale(size + plus_size);
		return true;
	}

	bool Button::IsButtonClicked(int mouse_x, int mouse_y) const
	{
		if (IsCollidingWithMouse(mouse_x, mouse_y) && Input::GetInstance().IsMouseTriggered(SDL_BUTTON_LEFT))
		{
			return true;
		}
	
		return false;
	}

	bool Button::IfButtonClickedTurnSound(int mouse_x, int mouse_y, const std::string& sound_name) const
	{
		if(IsButtonClicked(mouse_x, mouse_y))
		{
			if(sound_name != "")
				AUDIO_MANAGER->PlaySound(sound_name);

			return true;
		}
		return false;
	}

	void Button::Delete()
	{
		if(is_initialize)
		{
			OBJECT_FACTORY->Destroy(button);
			GRAPHICS->DeleteSprite(button->sprite);
			button = nullptr;
		}
		is_initialize = false;
	}

	bool Button::SetZifMouseHover(int mouse_x, int mouse_y, float z, int i)
	{
		if (i >= 1 && i <= 12)
		{
			if (play_once[i-1] == false)
				return false;
		}

		if (!is_initialize)
			return false;
	
		const float current_z = button->transform->GetTranslation().z;


		if (IsCollidingWithMouse(mouse_x, mouse_y))
		{
			if (z != current_z)
				SetZ(z);
			return true;
		}
		else
		{
			if(position.z != current_z)
				SetZ(position.z);
			return false;
		}
	}

	void Button::SetZ(float z)
	{
		button->transform->SetPositionZ(z);
	}

	void Button::IfMouseHoverScaleSize(bool turn_on)
	{
		if_mouse_hover_scale_size = turn_on;
	}

	void Button::SetPlusSize(glm::vec2 plus)
	{
		plus_size = plus;
	}

	void Button::SetHud(bool on)
	{
		if (!is_initialize)
			return;
		button->sprite->isHud = on;
	}
}
